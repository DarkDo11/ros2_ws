#!/usr/bin/env python3
from __future__ import annotations

import time
import threading
from dataclasses import dataclass
from pathlib import Path
from typing import Callable, Dict, Tuple

import rclpy
import yaml
from geometry_msgs.msg import TransformStamped
from rclpy.action import ActionClient
from rclpy.node import Node
from tf2_ros import TransformBroadcaster

from gearbox_sim.action import RunScrewdriver
from gearbox_sim.srv import RunPressCycle, SetAttachment
from motion_planner import MotionPlannerFacade, PlanningFailure


@dataclass
class PartState:
    parent_frame: str
    link_name: str
    xyz: Tuple[float, float, float] = (0.0, 0.0, 0.0)
    quat: Tuple[float, float, float, float] = (0.0, 0.0, 0.0, 1.0)


class AssemblyStateMachine(Node):
    def __init__(self):
        super().__init__("assembly_state_machine")
        default_config = (
            Path(__file__).resolve().parents[1] / "config" / "assembly_cell.yaml"
        )
        self.declare_parameter("config_file", str(default_config))
        self.declare_parameter("dry_run", True)
        self.declare_parameter("start_delay_sec", 5.0)

        self.config_file = self.get_parameter("config_file").get_parameter_value().string_value
        self.dry_run = self.get_parameter("dry_run").get_parameter_value().bool_value

        with Path(self.config_file).open("r", encoding="utf-8") as stream:
            self.config = yaml.safe_load(stream)

        self.motion = MotionPlannerFacade(self, self.config_file, dry_run=self.dry_run)
        self.press_client = self.create_client(
            RunPressCycle,
            self.config["services"]["press_service"],
        )
        self.attachment_client = self.create_client(
            SetAttachment,
            self.config["services"]["attachment_service"],
        )
        self.screwdriver_client = ActionClient(
            self,
            RunScrewdriver,
            self.config["services"]["screwdriver_action"],
        )

        self.tf_broadcaster = TransformBroadcaster(self)
        self.part_states: Dict[str, PartState] = {}
        part_links = self.config.get("part_links", {})
        for part_name, source_frame in self.config["parts"].items():
            self.part_states[part_name] = PartState(
                parent_frame=source_frame,
                link_name=part_links.get(part_name, part_name),
            )

        self.frame_timer = self.create_timer(0.1, self._publish_part_frames)

        start_delay = self.get_parameter("start_delay_sec").get_parameter_value().double_value
        self.create_timer(start_delay, self._start_once)
        self._started = False

    def _wait_for_future(self, future, timeout_sec: float, description: str):
        deadline = time.monotonic() + timeout_sec
        while rclpy.ok() and not future.done():
            if time.monotonic() >= deadline:
                raise RuntimeError(f"{description} timed out after {timeout_sec:.2f}s")
            time.sleep(0.01)

        if future.cancelled():
            raise RuntimeError(f"{description} was cancelled")
        if future.exception() is not None:
            raise RuntimeError(f"{description} failed: {future.exception()}") from future.exception()
        return future.result()

    def _start_once(self):
        if self._started:
            return
        self._started = True
        worker = threading.Thread(target=self._run_sequence, daemon=True)
        worker.start()

    def _publish_part_frames(self):
        stamp = self.get_clock().now().to_msg()
        for part_name, state in self.part_states.items():
            msg = TransformStamped()
            msg.header.stamp = stamp
            msg.header.frame_id = state.parent_frame
            msg.child_frame_id = f"{part_name}_current_frame"
            msg.transform.translation.x = state.xyz[0]
            msg.transform.translation.y = state.xyz[1]
            msg.transform.translation.z = state.xyz[2]
            msg.transform.rotation.x = state.quat[0]
            msg.transform.rotation.y = state.quat[1]
            msg.transform.rotation.z = state.quat[2]
            msg.transform.rotation.w = state.quat[3]
            self.tf_broadcaster.sendTransform(msg)

    def _set_part_frame(self, part_name: str, parent_frame: str):
        state = self.part_states[part_name]
        self.part_states[part_name] = PartState(
            parent_frame=parent_frame,
            link_name=state.link_name,
            xyz=state.xyz,
            quat=state.quat,
        )

    def _run_motion_with_retries(
        self,
        robot_name: str,
        description: str,
        operation: Callable[[Tuple[float, float]], None],
    ):
        biases = [
            (0.0, 0.0),
            (0.0025, 0.0),
            (-0.0025, 0.0),
            (0.0, 0.0025),
            (0.0, -0.0025),
        ]
        last_error = None
        for attempt_index, bias in enumerate(biases, start=1):
            try:
                self.get_logger().info(
                    f"{description}: attempt={attempt_index} bias_xy=({bias[0]:.4f}, {bias[1]:.4f})"
                )
                operation(bias)
                return
            except Exception as exc:
                last_error = exc
                self.get_logger().warn(
                    f"{description}: attempt={attempt_index} failed: {exc}"
                )
                try:
                    self.motion.move_to_safe_pose(robot_name)
                except Exception as recovery_exc:
                    self.get_logger().warn(
                        f"{description}: safe-pose recovery failed: {recovery_exc}"
                    )
        raise PlanningFailure(f"{description} failed after retries: {last_error}")

    def _set_attachment(self, robot_name: str, part_name: str, attach: bool):
        state = self.part_states[part_name]
        request = SetAttachment.Request()
        request.robot_name = robot_name
        request.tool_frame = self.motion.robot_configs[robot_name].tool_frame
        request.part_name = part_name
        request.part_frame = f"{part_name}_current_frame"
        request.part_link = state.link_name
        request.attach = attach

        if not self.attachment_client.wait_for_service(timeout_sec=5.0):
            raise RuntimeError("Attachment service is unavailable")
        future = self.attachment_client.call_async(request)
        response = self._wait_for_future(
            future,
            timeout_sec=5.0,
            description=f"attachment service call for {part_name}",
        )
        if response is None or not response.success:
            raise RuntimeError(
                f"Attachment request failed for {part_name}: "
                f"{response.message if response else 'no response'}"
            )

    def _pick_part(self, robot_name: str, part_name: str):
        source_frame = f"{part_name}_current_frame"
        cfg = self.motion.robot_configs[robot_name]

        def operation(bias_xy: Tuple[float, float]):
            self.motion.execute_frame_motion(
                robot_name=robot_name,
                target_frame=source_frame,
                approach_height_m=cfg.approach_height_m,
                insertion_depth_m=cfg.insertion_depth_m,
                approach_bias_xy=bias_xy,
            )
            self._set_attachment(robot_name, part_name, attach=True)
            self.motion.execute_precision_departure(
                robot_name=robot_name,
                target_frame=source_frame,
                z_offset=cfg.approach_height_m,
                steps=6,
                approach_bias_xy=bias_xy,
            )
            self._set_part_frame(part_name, cfg.tool_frame)

        self._run_motion_with_retries(
            robot_name=robot_name,
            description=f"{robot_name}: pick {part_name} from {source_frame}",
            operation=operation,
        )

    def _place_part(self, robot_name: str, part_name: str, target_frame: str, precise: bool = False):
        cfg = self.motion.robot_configs[robot_name]

        def operation(bias_xy: Tuple[float, float]):
            if precise:
                self.motion.execute_precision_insertion(
                    robot_name=robot_name,
                    target_frame=target_frame,
                    z_offset=cfg.approach_height_m,
                    steps=8,
                    approach_bias_xy=bias_xy,
                )
            else:
                self.motion.execute_frame_motion(
                    robot_name=robot_name,
                    target_frame=target_frame,
                    approach_height_m=cfg.approach_height_m,
                    insertion_depth_m=cfg.insertion_depth_m,
                    approach_bias_xy=bias_xy,
                )

        self._run_motion_with_retries(
            robot_name=robot_name,
            description=f"{robot_name}: place {part_name} into {target_frame}",
            operation=operation,
        )
        self._set_attachment(robot_name, part_name, attach=False)
        self._set_part_frame(part_name, target_frame)
        try:
            self.motion.execute_precision_departure(
                robot_name=robot_name,
                target_frame=target_frame,
                z_offset=cfg.approach_height_m,
                steps=6,
            )
        except Exception as exc:
            self.get_logger().warn(
                f"{robot_name}: departure after placing {part_name} failed: {exc}"
            )
            self.motion.move_to_safe_pose(robot_name)

    def _move_part(self, robot_name: str, part_name: str, target_frame: str, precise: bool = False):
        self._pick_part(robot_name, part_name)
        self._place_part(robot_name, part_name, target_frame, precise=precise)

    def _run_press_cycle(self, recipe_name: str, target_frame: str):
        request = RunPressCycle.Request()
        request.recipe_name = recipe_name
        request.target_frame = target_frame
        request.approach_height_m = 0.06
        request.stroke_m = 0.035
        request.dwell_sec = 0.8

        if not self.press_client.wait_for_service(timeout_sec=5.0):
            raise RuntimeError("Press service is unavailable")
        future = self.press_client.call_async(request)
        response = self._wait_for_future(
            future,
            timeout_sec=10.0,
            description=f"press cycle {recipe_name}",
        )
        if response is None or not response.success:
            raise RuntimeError("Press cycle failed")

    def _run_screw(self, screw_frame: str):
        if not self.screwdriver_client.wait_for_server(timeout_sec=5.0):
            raise RuntimeError("Screwdriver action server is unavailable")

        goal = RunScrewdriver.Goal()
        goal.screw_frame = screw_frame
        goal.approach_height_m = 0.04
        goal.descend_depth_m = 0.020
        goal.spin_rps = 6.0
        goal.duration_sec = 1.5
        goal.feed_from_autofeeder = True

        send_future = self.screwdriver_client.send_goal_async(goal)
        goal_handle = self._wait_for_future(
            send_future,
            timeout_sec=5.0,
            description=f"screwdriver goal dispatch for {screw_frame}",
        )
        if goal_handle is None or not goal_handle.accepted:
            raise RuntimeError(f"Screwdriver goal rejected for {screw_frame}")

        result_future = goal_handle.get_result_async()
        result = self._wait_for_future(
            result_future,
            timeout_sec=10.0,
            description=f"screwdriver result for {screw_frame}",
        )
        if result is None or not result.result.success:
            raise RuntimeError(f"Screwdriver failed for {screw_frame}")

    def _run_sequence(self):
        try:
            self.get_logger().info("Assembly sequence started")

            self._move_part("ur5e_press", "lower_housing", "press_lower_housing_frame", precise=True)
            self._move_part("ur5e_press", "main_bearing", "press_main_bearing_frame", precise=True)
            self._run_press_cycle("lower_housing_main_bearing", "press_lower_housing_frame")
            self._set_part_frame("main_bearing", "press_lower_housing_frame")
            self._move_part("ur5e_press", "lower_housing", "buffer_lower_housing_frame", precise=False)
            self._set_part_frame("main_bearing", "buffer_lower_housing_frame")

            self._move_part("ur5e_press", "cover", "press_cover_frame", precise=True)
            self._move_part("ur5e_press", "small_bearing", "press_small_bearing_frame", precise=True)
            self._run_press_cycle("cover_small_bearing", "press_cover_frame")
            self._set_part_frame("small_bearing", "press_cover_frame")
            self._move_part("ur5e_press", "cover", "buffer_cover_frame", precise=False)
            self._set_part_frame("small_bearing", "buffer_cover_frame")

            self._move_part("ur5e_press", "housing", "press_housing_frame", precise=True)
            self._move_part("ur5e_press", "ring_gear", "press_ring_gear_frame", precise=True)
            self._run_press_cycle("housing_ring_gear", "press_housing_frame")
            self._set_part_frame("ring_gear", "press_housing_frame")
            self._move_part("ur5e_press", "housing", "buffer_housing_frame", precise=False)
            self._set_part_frame("ring_gear", "buffer_housing_frame")

            self._move_part("ur5e_assembly", "lower_housing", "assembly_lower_housing_frame", precise=True)
            self._set_part_frame("main_bearing", "assembly_lower_housing_frame")

            self._move_part("ur5e_assembly", "planet_1", "assembly_planet_1_frame", precise=True)
            self._move_part("ur5e_assembly", "planet_2", "assembly_planet_2_frame", precise=True)
            self._move_part("ur5e_assembly", "planet_3", "assembly_planet_3_frame", precise=True)
            self._move_part("ur5e_assembly", "sun_gear", "assembly_sun_frame", precise=True)
            self._move_part("ur5e_assembly", "carrier", "assembly_carrier_frame", precise=True)

            self._move_part("ur5e_assembly", "housing", "assembly_housing_frame", precise=True)
            self._set_part_frame("ring_gear", "assembly_housing_frame")
            self._move_part("ur5e_assembly", "cover", "assembly_cover_frame", precise=True)
            self._set_part_frame("small_bearing", "assembly_cover_frame")

            for screw_frame in self.config["assembly"]["screw_frames"]:
                self._run_screw(screw_frame)

            self._move_part("ur5e_assembly", "lower_housing", self.config["assembly"]["output_frame"], precise=False)
            self._set_part_frame("housing", self.config["assembly"]["output_frame"])
            self._set_part_frame("cover", self.config["assembly"]["output_frame"])
            self._set_part_frame("ring_gear", self.config["assembly"]["output_frame"])
            self._set_part_frame("carrier", self.config["assembly"]["output_frame"])
            self._set_part_frame("sun_gear", self.config["assembly"]["output_frame"])
            self._set_part_frame("planet_1", self.config["assembly"]["output_frame"])
            self._set_part_frame("planet_2", self.config["assembly"]["output_frame"])
            self._set_part_frame("planet_3", self.config["assembly"]["output_frame"])

            self.get_logger().info("Assembly sequence completed")
        except Exception as exc:
            self.get_logger().error(f"Assembly sequence failed: {exc}")


def main():
    rclpy.init()
    node = AssemblyStateMachine()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
