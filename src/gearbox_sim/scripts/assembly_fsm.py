#!/usr/bin/env python3
from __future__ import annotations

import json
import threading
import time
from dataclasses import dataclass
from pathlib import Path
from typing import Callable, Dict, Iterable, List, Optional, Tuple

import subprocess as _sp

import rclpy
import yaml
from geometry_msgs.msg import TransformStamped
from rclpy.action import ActionClient
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray, String
from tf2_ros import Buffer, TransformBroadcaster, TransformListener

try:
    from yasmin import Blackboard, State, StateMachine
    from yasmin_ros import set_ros_loggers
    from yasmin_viewer import YasminViewerPub
except ImportError as exc:
    raise ImportError(
        "assembly_fsm.py requires YASMIN. Install the ROS 2 packages "
        "yasmin, yasmin_ros and yasmin_viewer, or build "
        "https://github.com/uleroboticsgroup/yasmin in this workspace."
    ) from exc

from gearbox_sim.action import RunScrewdriver
from gearbox_sim.srv import RunPressCycle, SetAttachment
from motion_planner import MotionPlannerFacade


OK = "ok"
FAILED = "failed"
SUCCEEDED = "succeeded"
ABORTED = "aborted"

BIAS_SEQUENCE: List[Tuple[float, float]] = [
    (0.0, 0.0),
    (0.0025, 0.0),
    (-0.0025, 0.0),
    (0.0, 0.0025),
    (0.0, -0.0025),
]


def bb_get(blackboard: Blackboard, key: str, default=None):
    try:
        return blackboard[key]
    except KeyError:
        return default


@dataclass
class PartState:
    parent_frame: str
    link_name: str
    xyz: Tuple[float, float, float] = (0.0, 0.0, 0.0)
    quat: Tuple[float, float, float, float] = (0.0, 0.0, 0.0, 1.0)


@dataclass
class FtState:
    force_mag_n: float
    torque_mag_nm: float
    stamp_monotonic: float


class LoggedState(State):
    def __init__(
        self,
        node: "AssemblyFsmNode",
        state_name: str,
        outcomes: Iterable[str],
    ) -> None:
        super().__init__(outcomes=list(outcomes))
        self.node = node
        self.state_name = state_name
        self.transition_targets: Dict[str, str] = {}

    def _enter(self) -> None:
        self.node.get_logger().info(f"FSM enter: {self.state_name}")

    def _leave(self, outcome: str) -> str:
        target = self.transition_targets.get(outcome, "<final>")
        self.node.get_logger().info(
            f"FSM transition: {self.state_name} --{outcome}--> {target}"
        )
        return outcome


class DelayState(LoggedState):
    def __init__(self, node: "AssemblyFsmNode", start_delay_sec: float) -> None:
        super().__init__(node, "IDLE", [OK, FAILED])
        self.start_delay_sec = start_delay_sec

    def execute(self, blackboard: Blackboard) -> str:
        self._enter()
        blackboard["recovery_attempts"] = {}
        blackboard["last_error"] = ""
        blackboard["resume_state"] = ""
        blackboard["recovery_robot"] = ""
        self.node.get_logger().info(
            f"Assembly FSM will start after {self.start_delay_sec:.2f}s"
        )
        time.sleep(max(0.0, self.start_delay_sec))
        return self._leave(OK)


class TerminalState(LoggedState):
    def __init__(
        self,
        node: "AssemblyFsmNode",
        state_name: str,
        outcome: str,
        message: str,
    ) -> None:
        super().__init__(node, state_name, [outcome])
        self.outcome = outcome
        self.message = message

    def execute(self, blackboard: Blackboard) -> str:
        self._enter()
        if self.outcome == SUCCEEDED:
            self.node.get_logger().info(self.message)
        else:
            last_error = bb_get(blackboard, "last_error", "")
            if last_error:
                self.node.get_logger().error(f"{self.message}: {last_error}")
            else:
                self.node.get_logger().error(self.message)
        return self._leave(self.outcome)


class HomingState(LoggedState):
    def __init__(self, node: "AssemblyFsmNode") -> None:
        super().__init__(node, "HOMING", [OK, FAILED])

    def execute(self, blackboard: Blackboard) -> str:
        self._enter()
        try:
            for robot_name in self.node.motion.robot_configs:
                blackboard["recovery_robot"] = robot_name
                self.node.motion.move_to_safe_pose(robot_name)
            blackboard["recovery_robot"] = ""
            return self._leave(OK)
        except Exception as exc:
            blackboard["resume_state"] = self.state_name
            blackboard["last_error"] = f"{self.state_name}: {exc}"
            return self._leave(FAILED)


class CallbackState(LoggedState):
    def __init__(
        self,
        node: "AssemblyFsmNode",
        state_name: str,
        callback: Callable[[Blackboard], None],
    ) -> None:
        super().__init__(node, state_name, [OK, FAILED])
        self.callback = callback

    def execute(self, blackboard: Blackboard) -> str:
        self._enter()
        try:
            self.callback(blackboard)
            return self._leave(OK)
        except Exception as exc:
            blackboard["resume_state"] = self.state_name
            blackboard["last_error"] = f"{self.state_name}: {exc}"
            return self._leave(FAILED)


class OperationState(LoggedState):
    def __init__(
        self,
        node: "AssemblyFsmNode",
        state_name: str,
        robot_name: Optional[str],
        operation: Callable[[Blackboard, Tuple[float, float]], None],
    ) -> None:
        super().__init__(node, state_name, [OK, FAILED])
        self.robot_name = robot_name
        self.operation = operation

    def execute(self, blackboard: Blackboard) -> str:
        self._enter()
        attempts = bb_get(blackboard, "recovery_attempts", {})
        attempt_index = int(attempts.get(self.state_name, 0))
        bias = BIAS_SEQUENCE[min(attempt_index, len(BIAS_SEQUENCE) - 1)]
        try:
            self.node.get_logger().info(
                f"{self.state_name}: attempt={attempt_index + 1} "
                f"bias_xy=({bias[0]:.4f}, {bias[1]:.4f})"
            )
            self.operation(blackboard, bias)
            attempts.pop(self.state_name, None)
            blackboard["recovery_attempts"] = attempts
            blackboard["resume_state"] = ""
            blackboard["recovery_robot"] = ""
            return self._leave(OK)
        except Exception as exc:
            blackboard["resume_state"] = self.state_name
            blackboard["recovery_robot"] = self.robot_name or ""
            blackboard["last_error"] = f"{self.state_name}: {exc}"
            return self._leave(FAILED)


class ErrorRecoveryState(LoggedState):
    def __init__(
        self,
        node: "AssemblyFsmNode",
        state_name: str,
        resumable_states: Iterable[str],
    ) -> None:
        outcomes = list(resumable_states) + [FAILED]
        super().__init__(node, state_name, outcomes)
        self.resumable_states = set(resumable_states)

    def execute(self, blackboard: Blackboard) -> str:
        self._enter()
        resume_state = bb_get(blackboard, "resume_state", "")
        robot_name = bb_get(blackboard, "recovery_robot", "")
        attempts = bb_get(blackboard, "recovery_attempts", {})
        current_attempt = int(attempts.get(resume_state, 0))

        self.node.get_logger().warn(
            f"ERROR_RECOVERY: source={resume_state or '<none>'} "
            f"attempt={current_attempt + 1}/{len(BIAS_SEQUENCE)} "
            f"error={bb_get(blackboard, 'last_error', '')}"
        )

        if robot_name:
            try:
                self.node.motion.move_to_safe_pose(robot_name)
            except Exception as recovery_exc:
                self.node.get_logger().warn(
                    f"ERROR_RECOVERY: safe-pose recovery failed for "
                    f"{robot_name}: {recovery_exc}"
                )

        if resume_state not in self.resumable_states:
            return self._leave(FAILED)

        next_attempt = current_attempt + 1
        attempts[resume_state] = next_attempt
        blackboard["recovery_attempts"] = attempts
        if next_attempt >= len(BIAS_SEQUENCE):
            return self._leave(FAILED)

        return self._leave(resume_state)


class AssemblyFsmNode(Node):
    def __init__(self) -> None:
        super().__init__("assembly_fsm")
        default_config = (
            Path(__file__).resolve().parents[1] / "config" / "assembly_cell.yaml"
        )
        self.declare_parameter("config_file", str(default_config))
        self.declare_parameter("dry_run", True)
        self.declare_parameter("start_delay_sec", 5.0)
        self.declare_parameter("visual_unload_demo", True)
        self.declare_parameter("require_vision_status", False)
        self.declare_parameter("vision_status_topic", "/vision/part_status")
        self.declare_parameter("vision_status_timeout_sec", 2.0)
        self.declare_parameter("ft_logic_enabled", True)
        self.declare_parameter("require_ft_samples", False)
        self.declare_parameter("ft_status_timeout_sec", 2.0)
        self.declare_parameter("max_contact_force_n", 40.0)
        self.declare_parameter("max_contact_torque_nm", 6.0)

        self.config_file = (
            self.get_parameter("config_file").get_parameter_value().string_value
        )
        self.dry_run = self.get_parameter("dry_run").get_parameter_value().bool_value
        self.start_delay_sec = (
            self.get_parameter("start_delay_sec").get_parameter_value().double_value
        )
        self.visual_unload_demo = (
            self.get_parameter("visual_unload_demo").get_parameter_value().bool_value
        )
        self.require_vision_status = (
            self.get_parameter("require_vision_status").get_parameter_value().bool_value
        )
        self.vision_status_timeout_sec = (
            self.get_parameter("vision_status_timeout_sec")
            .get_parameter_value()
            .double_value
        )
        self.ft_logic_enabled = (
            self.get_parameter("ft_logic_enabled").get_parameter_value().bool_value
        )
        self.require_ft_samples = (
            self.get_parameter("require_ft_samples").get_parameter_value().bool_value
        )
        self.ft_status_timeout_sec = (
            self.get_parameter("ft_status_timeout_sec").get_parameter_value().double_value
        )
        self.max_contact_force_n = (
            self.get_parameter("max_contact_force_n").get_parameter_value().double_value
        )
        self.max_contact_torque_nm = (
            self.get_parameter("max_contact_torque_nm")
            .get_parameter_value()
            .double_value
        )

        with Path(self.config_file).open("r", encoding="utf-8") as stream:
            self.config = yaml.safe_load(stream)

        if self.visual_unload_demo:
            self.get_logger().warn(
                "visual_unload_demo=true: final unload uses a prebuilt "
                "assembled_gearbox model and hides loose part models."
            )
        else:
            self.get_logger().warn(
                "visual_unload_demo=false: visual unload is disabled; the FSM "
                "will fail if it reaches the demo-only unload sequence."
            )

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
        self.vision_statuses: Dict[str, Tuple[float, Dict[str, object]]] = {}
        self.ft_states: Dict[str, FtState] = {}
        self._missing_ft_warned: set = set()
        self.create_subscription(
            String,
            self.get_parameter("vision_status_topic").get_parameter_value().string_value,
            self._vision_status_cb,
            20,
        )
        for robot_name in self.config.get("robots", {}):
            self.create_subscription(
                Float64MultiArray,
                f"/{robot_name}/ft_summary",
                self._make_ft_summary_cb(robot_name),
                20,
            )

        self.tf_broadcaster = TransformBroadcaster(self)
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        self.part_states: Dict[str, PartState] = {}
        part_links = self.config.get("part_links", {})
        for part_name, source_frame in self.config["parts"].items():
            self.part_states[part_name] = PartState(
                parent_frame=source_frame,
                link_name=part_links.get(part_name, part_name),
            )

        self.create_timer(0.1, self._publish_part_frames)
        # Publish initial TF frames immediately so grasp_attacher can find them
        # from the first sync attempt, without waiting for the first timer tick.
        self._publish_part_frames()
        self.sm = self._build_fsm()
        self.viewer_pub = self._start_viewer_publisher()

        self._started = False
        self.create_timer(0.1, self._start_once)

    def _vision_status_cb(self, msg: String) -> None:
        try:
            status = json.loads(msg.data)
        except json.JSONDecodeError as exc:
            self.get_logger().warn(f"Invalid vision status JSON: {exc}")
            return
        part_name = status.get("part_name")
        if not isinstance(part_name, str) or not part_name:
            self.get_logger().warn("Vision status missing part_name")
            return
        self.vision_statuses[part_name] = (time.monotonic(), status)

    def _make_ft_summary_cb(self, robot_name: str):
        def _cb(msg: Float64MultiArray) -> None:
            if len(msg.data) < 8:
                self.get_logger().warn(
                    f"{robot_name}: invalid ft_summary length={len(msg.data)}"
                )
                return
            self.ft_states[robot_name] = FtState(
                force_mag_n=float(msg.data[3]),
                torque_mag_nm=float(msg.data[7]),
                stamp_monotonic=time.monotonic(),
            )

        return _cb

    def _ensure_vision_ready(self, part_name: str, operation: str) -> None:
        if not self.require_vision_status:
            return

        entry = self.vision_statuses.get(part_name)
        if entry is None:
            raise RuntimeError(
                f"{operation}: no vision status received for {part_name}"
            )

        stamp_monotonic, status = entry
        age = time.monotonic() - stamp_monotonic
        if age > self.vision_status_timeout_sec:
            raise RuntimeError(
                f"{operation}: stale vision status for {part_name}, age={age:.2f}s"
            )
        if not bool(status.get("accepted", False)):
            raise RuntimeError(
                f"{operation}: vision rejected {part_name}: "
                f"{status.get('message', 'no reason')}"
            )

        self.get_logger().info(
            f"{operation}: vision accepted {part_name} "
            f"at {status.get('detected_frame', '<unknown>')}"
        )

    def _check_ft_ok(self, robot_name: Optional[str], operation: str) -> None:
        if not self.ft_logic_enabled or not robot_name:
            return

        state = self.ft_states.get(robot_name)
        if state is None:
            if self.require_ft_samples:
                raise RuntimeError(f"{operation}: no F/T summary for {robot_name}")
            if robot_name not in self._missing_ft_warned:
                self.get_logger().warn(
                    f"{operation}: no F/T summary for {robot_name}; "
                    "continuing because require_ft_samples=false"
                )
                self._missing_ft_warned.add(robot_name)
            return

        age = time.monotonic() - state.stamp_monotonic
        if age > self.ft_status_timeout_sec:
            if self.require_ft_samples:
                raise RuntimeError(
                    f"{operation}: stale F/T summary for {robot_name}, age={age:.2f}s"
                )
            return

        if state.force_mag_n > self.max_contact_force_n:
            raise RuntimeError(
                f"{operation}: F/T force limit exceeded for {robot_name}: "
                f"{state.force_mag_n:.2f} N > {self.max_contact_force_n:.2f} N"
            )
        if state.torque_mag_nm > self.max_contact_torque_nm:
            raise RuntimeError(
                f"{operation}: F/T torque limit exceeded for {robot_name}: "
                f"{state.torque_mag_nm:.2f} Nm > {self.max_contact_torque_nm:.2f} Nm"
            )

    def _make_state_machine(
        self,
        name: str,
        outcomes: Iterable[str],
        handle_sigint: bool = False,
    ) -> StateMachine:
        try:
            sm = StateMachine(outcomes=list(outcomes), handle_sigint=handle_sigint)
        except TypeError:
            try:
                sm = StateMachine(outcomes=list(outcomes))
            except TypeError:
                sm = StateMachine(list(outcomes))
        if hasattr(sm, "set_name"):
            sm.set_name(name)
        return sm

    def _add_state(
        self,
        sm: StateMachine,
        name: str,
        state: State,
        transitions: Dict[str, str],
    ) -> None:
        if isinstance(state, LoggedState):
            state.transition_targets = dict(transitions)
        sm.add_state(name, state, transitions=transitions)

    def _set_start_state(self, sm: StateMachine, state_name: str) -> None:
        if hasattr(sm, "set_start_state"):
            sm.set_start_state(state_name)

    def _start_viewer_publisher(self):
        try:
            return YasminViewerPub(self.sm, "GEARBOX_ASSEMBLY_FSM", node=self)
        except TypeError:
            try:
                return YasminViewerPub(self.sm, "GEARBOX_ASSEMBLY_FSM")
            except TypeError:
                try:
                    return YasminViewerPub("GEARBOX_ASSEMBLY_FSM", self.sm, node=self)
                except TypeError:
                    return YasminViewerPub("GEARBOX_ASSEMBLY_FSM", self.sm)

    def _start_once(self) -> None:
        if self._started:
            return
        self._started = True
        worker = threading.Thread(target=self._execute_fsm, daemon=True)
        worker.start()

    def _execute_fsm(self) -> None:
        blackboard = Blackboard()
        try:
            outcome = self.sm(blackboard)
            self.get_logger().info(f"Assembly FSM finished with outcome={outcome}")
        except Exception as exc:
            self.get_logger().error(f"Assembly FSM execution failed: {exc}")

    def _wait_for_future(self, future, timeout_sec: float, description: str):
        deadline = time.monotonic() + timeout_sec
        while rclpy.ok() and not future.done():
            if time.monotonic() >= deadline:
                raise RuntimeError(f"{description} timed out after {timeout_sec:.2f}s")
            time.sleep(0.01)

        if future.cancelled():
            raise RuntimeError(f"{description} was cancelled")
        if future.exception() is not None:
            raise RuntimeError(
                f"{description} failed: {future.exception()}"
            ) from future.exception()
        return future.result()

    def _publish_part_frames(self) -> None:
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

    def _set_part_frame(self, part_name: str, parent_frame: str) -> None:
        state = self.part_states[part_name]
        self.part_states[part_name] = PartState(
            parent_frame=parent_frame,
            link_name=state.link_name,
            xyz=state.xyz,
            quat=state.quat,
        )

    def _remove_gz_model(self, model_name: str) -> None:
        """Delete a Gazebo model outright (non-blocking fire-and-forget)."""
        req = f'name: "{model_name}" type: MODEL'
        _sp.Popen(
            [
                "gz", "service",
                "-s", "/world/assembly_world/remove",
                "--reqtype", "gz.msgs.Entity",
                "--reptype", "gz.msgs.Boolean",
                "--timeout", "1500",
                "--req", req,
            ],
            stdout=_sp.DEVNULL,
            stderr=_sp.DEVNULL,
        )

    def _hide_part(self, part_name: str) -> None:
        """Remove a loose part for good.

        Deleting the model is the only fully reliable hide: a removed entity
        cannot be left as debris and cannot be dragged back by grasp_attacher's
        pose sync (its set_pose calls simply no-op on a missing model).  The TF
        frame is also re-anchored deep underground so any in-flight sync targets
        empty space rather than a table.
        """
        state = self.part_states[part_name]
        self.part_states[part_name] = PartState(
            parent_frame="world",
            link_name=state.link_name,
            xyz=(0.0, 0.0, -10.0),
            quat=state.quat,
        )
        model_name = self.config.get("part_links", {}).get(part_name, part_name)
        self._remove_gz_model(model_name)

    def _set_attachment(self, robot_name: str, part_name: str, attach: bool) -> None:
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

    def _pick_part(
        self,
        robot_name: str,
        part_name: str,
        bias_xy: Tuple[float, float],
    ) -> None:
        source_frame = f"{part_name}_current_frame"
        cfg = self.motion.robot_configs[robot_name]
        self._ensure_vision_ready(part_name, f"pick {part_name}")
        self._check_ft_ok(robot_name, f"before picking {part_name}")
        self.motion.execute_frame_motion(
            robot_name=robot_name,
            target_frame=source_frame,
            approach_height_m=cfg.approach_height_m,
            insertion_depth_m=cfg.insertion_depth_m,
            approach_bias_xy=bias_xy,
        )
        self._check_ft_ok(robot_name, f"after approach to {part_name}")
        self._set_attachment(robot_name, part_name, attach=True)
        self.motion.execute_precision_departure(
            robot_name=robot_name,
            target_frame=source_frame,
            z_offset=cfg.approach_height_m,
            steps=6,
            approach_bias_xy=bias_xy,
        )
        self._check_ft_ok(robot_name, f"after picking {part_name}")
        self._set_part_frame(part_name, cfg.tool_frame)

    def _place_part(
        self,
        robot_name: str,
        part_name: str,
        target_frame: str,
        bias_xy: Tuple[float, float],
        precise: bool = False,
    ) -> None:
        cfg = self.motion.robot_configs[robot_name]
        self._check_ft_ok(robot_name, f"before placing {part_name}")
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

        self._check_ft_ok(robot_name, f"after placing {part_name}")
        self._set_attachment(robot_name, part_name, attach=False)
        self._set_part_frame(part_name, target_frame)
        try:
            self.motion.execute_precision_departure(
                robot_name=robot_name,
                target_frame=target_frame,
                z_offset=cfg.approach_height_m,
                steps=6,
            )
            self._check_ft_ok(robot_name, f"after departing {part_name}")
        except Exception as exc:
            self.get_logger().warn(
                f"{robot_name}: departure after placing {part_name} failed: {exc}"
            )
            self.motion.move_to_safe_pose(robot_name)

    def _run_press_cycle(self, recipe_name: str, target_frame: str) -> None:
        request = RunPressCycle.Request()
        request.recipe_name = recipe_name
        request.target_frame = target_frame
        request.approach_height_m = 0.06
        request.stroke_m = 0.035
        request.dwell_sec = 0.8

        self._check_ft_ok("ur5e_press", f"before press cycle {recipe_name}")
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
        self._check_ft_ok("ur5e_press", f"after press cycle {recipe_name}")

    def _run_screw(
        self,
        screw_frame: str,
        bias_xy: Tuple[float, float] = (0.0, 0.0),
    ) -> None:
        if not self.screwdriver_client.wait_for_server(timeout_sec=5.0):
            raise RuntimeError("Screwdriver action server is unavailable")

        robot_name = "ur3e_screw"
        goal = RunScrewdriver.Goal()
        goal.screw_frame = screw_frame
        goal.approach_height_m = 0.04
        goal.descend_depth_m = 0.020
        goal.spin_rps = 6.0
        goal.duration_sec = 1.5
        goal.feed_from_autofeeder = True

        self._check_ft_ok(robot_name, f"before screw cycle {screw_frame}")
        self.motion.execute_frame_motion(
            robot_name=robot_name,
            target_frame=screw_frame,
            approach_height_m=goal.approach_height_m,
            insertion_depth_m=goal.descend_depth_m,
            approach_bias_xy=bias_xy,
        )
        self._check_ft_ok(robot_name, f"after screw approach {screw_frame}")

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
        self._check_ft_ok(robot_name, f"after screw cycle {screw_frame}")

        self.motion.execute_precision_departure(
            robot_name=robot_name,
            target_frame=screw_frame,
            z_offset=goal.approach_height_m,
            steps=6,
            approach_bias_xy=bias_xy,
        )
        self._check_ft_ok(robot_name, f"after screw departure {screw_frame}")

    def _move_gz_model(self, model_name: str, x: float, y: float, z: float) -> None:
        """Teleport a Gazebo model to the given world position (non-blocking fire-and-forget)."""
        req = (
            f'name: "{model_name}" '
            f'position: {{x: {x}, y: {y}, z: {z}}} '
            f'orientation: {{x: 0, y: 0, z: 0, w: 1}}'
        )
        _sp.Popen(
            [
                "gz", "service",
                "-s", "/world/assembly_world/set_pose",
                "--reqtype", "gz.msgs.Pose",
                "--reptype", "gz.msgs.Boolean",
                "--timeout", "1500",
                "--req", req,
            ],
            stdout=_sp.DEVNULL,
            stderr=_sp.DEVNULL,
        )

    def _pick_state(self, state_name: str, robot_name: str, part_name: str) -> OperationState:
        return OperationState(
            self,
            state_name,
            robot_name,
            lambda _bb, bias: self._pick_part(robot_name, part_name, bias),
        )

    def _place_state(
        self,
        state_name: str,
        robot_name: str,
        part_name: str,
        target_frame: str,
        precise: bool,
    ) -> OperationState:
        return OperationState(
            self,
            state_name,
            robot_name,
            lambda _bb, bias: self._place_part(
                robot_name,
                part_name,
                target_frame,
                bias,
                precise=precise,
            ),
        )

    def _press_state(
        self,
        state_name: str,
        recipe_name: str,
        target_frame: str,
    ) -> OperationState:
        return OperationState(
            self,
            state_name,
            None,
            lambda _bb, _bias: self._run_press_cycle(recipe_name, target_frame),
        )

    def _screw_state(self, state_name: str, screw_frame: str) -> OperationState:
        return OperationState(
            self,
            state_name,
            "ur3e_screw",
            lambda _bb, bias: self._run_screw(screw_frame, bias),
        )

    def _update_frame_state(
        self,
        state_name: str,
        updates: Iterable[Tuple[str, str]],
    ) -> CallbackState:
        def update_frames(_blackboard: Blackboard) -> None:
            for part_name, parent_frame in updates:
                self._set_part_frame(part_name, parent_frame)

        return CallbackState(self, state_name, update_frames)

    def _build_linear_subfsm(
        self,
        name: str,
        states: List[Tuple[str, State]],
    ) -> StateMachine:
        sm = self._make_state_machine(name, [OK, FAILED])
        operation_state_names = [
            state_name
            for state_name, state in states
            if isinstance(state, OperationState)
        ]

        for index, (state_name, state) in enumerate(states):
            next_target = states[index + 1][0] if index + 1 < len(states) else OK
            self._add_state(
                sm,
                state_name,
                state,
                {
                    OK: next_target,
                    FAILED: f"{name}_ERROR_RECOVERY",
                },
            )

        recovery = ErrorRecoveryState(
            self,
            f"{name}/ERROR_RECOVERY",
            operation_state_names,
        )
        recovery_transitions = {state_name: state_name for state_name in operation_state_names}
        recovery_transitions[FAILED] = FAILED
        self._add_state(sm, f"{name}_ERROR_RECOVERY", recovery, recovery_transitions)
        self._set_start_state(sm, states[0][0])
        return sm

    def _build_press_subfsm(self) -> StateMachine:
        states: List[Tuple[str, State]] = []
        pairs = [
            {
                "base": "lower_housing",
                "insert": "main_bearing",
                "base_press_frame": "press_lower_housing_frame",
                "insert_press_frame": "press_main_bearing_frame",
                "recipe": "lower_housing_main_bearing",
                "buffer_frame": "buffer_lower_housing_frame",
            },
            {
                "base": "cover",
                "insert": "small_bearing",
                "base_press_frame": "press_cover_frame",
                "insert_press_frame": "press_small_bearing_frame",
                "recipe": "cover_small_bearing",
                "buffer_frame": "buffer_cover_frame",
            },
            {
                "base": "housing",
                "insert": "ring_gear",
                "base_press_frame": "press_housing_frame",
                "insert_press_frame": "press_ring_gear_frame",
                "recipe": "housing_ring_gear",
                "buffer_frame": "buffer_housing_frame",
            },
        ]

        for pair in pairs:
            base = pair["base"]
            insert = pair["insert"]
            base_upper = base.upper()
            insert_upper = insert.upper()
            base_press = pair["base_press_frame"]
            insert_press = pair["insert_press_frame"]
            buffer_frame = pair["buffer_frame"]

            states.extend(
                [
                    (
                        f"PICK_{base_upper}_FOR_PRESS",
                        self._pick_state(
                            f"PRESS_SUBFSM/PICK_{base_upper}_FOR_PRESS",
                            "ur5e_press",
                            base,
                        ),
                    ),
                    (
                        f"PLACE_{base_upper}_IN_PRESS",
                        self._place_state(
                            f"PRESS_SUBFSM/PLACE_{base_upper}_IN_PRESS",
                            "ur5e_press",
                            base,
                            base_press,
                            precise=True,
                        ),
                    ),
                    (
                        f"PICK_{insert_upper}",
                        self._pick_state(
                            f"PRESS_SUBFSM/PICK_{insert_upper}",
                            "ur5e_press",
                            insert,
                        ),
                    ),
                    (
                        f"PLACE_{insert_upper}_IN_PRESS",
                        self._place_state(
                            f"PRESS_SUBFSM/PLACE_{insert_upper}_IN_PRESS",
                            "ur5e_press",
                            insert,
                            insert_press,
                            precise=True,
                        ),
                    ),
                    (
                        f"PRESS_{base_upper}_{insert_upper}",
                        self._press_state(
                            f"PRESS_SUBFSM/PRESS_{base_upper}_{insert_upper}",
                            pair["recipe"],
                            base_press,
                        ),
                    ),
                    (
                        f"UPDATE_{insert_upper}_ON_PRESS",
                        self._update_frame_state(
                            f"PRESS_SUBFSM/UPDATE_{insert_upper}_ON_PRESS",
                            [(insert, base_press)],
                        ),
                    ),
                    (
                        f"PICK_{base_upper}_FROM_PRESS",
                        self._pick_state(
                            f"PRESS_SUBFSM/PICK_{base_upper}_FROM_PRESS",
                            "ur5e_press",
                            base,
                        ),
                    ),
                    (
                        f"PLACE_{base_upper}_IN_BUFFER",
                        self._place_state(
                            f"PRESS_SUBFSM/PLACE_{base_upper}_IN_BUFFER",
                            "ur5e_press",
                            base,
                            buffer_frame,
                            precise=False,
                        ),
                    ),
                    (
                        f"UPDATE_{insert_upper}_ON_BUFFER",
                        self._update_frame_state(
                            f"PRESS_SUBFSM/UPDATE_{insert_upper}_ON_BUFFER",
                            [(insert, buffer_frame)],
                        ),
                    ),
                ]
            )

        return self._build_linear_subfsm("PRESS_SUBFSM", states)

    def _build_assembly_subfsm(self) -> StateMachine:
        assembly_parts = [
            ("planet_1", "assembly_planet_1_frame"),
            ("planet_2", "assembly_planet_2_frame"),
            ("planet_3", "assembly_planet_3_frame"),
            ("sun_gear", "assembly_sun_frame"),
            ("carrier", "assembly_carrier_frame"),
        ]

        states: List[Tuple[str, State]] = [
            (
                "PICK_LOWER_HOUSING_FROM_BUFFER",
                self._pick_state(
                    "ASSEMBLY_SUBFSM/PICK_LOWER_HOUSING_FROM_BUFFER",
                    "ur5e_assembly",
                    "lower_housing",
                ),
            ),
            (
                "PLACE_LOWER_HOUSING_AT_ASSEMBLY",
                self._place_state(
                    "ASSEMBLY_SUBFSM/PLACE_LOWER_HOUSING_AT_ASSEMBLY",
                    "ur5e_assembly",
                    "lower_housing",
                    "assembly_lower_housing_frame",
                    precise=True,
                ),
            ),
            (
                "UPDATE_MAIN_BEARING_AT_ASSEMBLY",
                self._update_frame_state(
                    "ASSEMBLY_SUBFSM/UPDATE_MAIN_BEARING_AT_ASSEMBLY",
                    [("main_bearing", "assembly_lower_housing_frame")],
                ),
            ),
        ]

        for part_name, target_frame in assembly_parts:
            part_upper = part_name.upper()
            states.extend(
                [
                    (
                        f"PICK_{part_upper}",
                        self._pick_state(
                            f"ASSEMBLY_SUBFSM/PICK_{part_upper}",
                            "ur5e_assembly",
                            part_name,
                        ),
                    ),
                    (
                        f"PLACE_{part_upper}",
                        self._place_state(
                            f"ASSEMBLY_SUBFSM/PLACE_{part_upper}",
                            "ur5e_assembly",
                            part_name,
                            target_frame,
                            precise=True,
                        ),
                    ),
                ]
            )

        states.extend(
            [
                (
                    "PICK_HOUSING_FROM_BUFFER",
                    self._pick_state(
                        "ASSEMBLY_SUBFSM/PICK_HOUSING_FROM_BUFFER",
                        "ur5e_assembly",
                        "housing",
                    ),
                ),
                (
                    "PLACE_HOUSING_AT_ASSEMBLY",
                    self._place_state(
                        "ASSEMBLY_SUBFSM/PLACE_HOUSING_AT_ASSEMBLY",
                        "ur5e_assembly",
                        "housing",
                        "assembly_housing_frame",
                        precise=True,
                    ),
                ),
                (
                    "UPDATE_RING_GEAR_AT_ASSEMBLY",
                    self._update_frame_state(
                        "ASSEMBLY_SUBFSM/UPDATE_RING_GEAR_AT_ASSEMBLY",
                        [("ring_gear", "assembly_housing_frame")],
                    ),
                ),
                (
                    "PICK_COVER_FROM_BUFFER",
                    self._pick_state(
                        "ASSEMBLY_SUBFSM/PICK_COVER_FROM_BUFFER",
                        "ur5e_assembly",
                        "cover",
                    ),
                ),
                (
                    "PLACE_COVER_AT_ASSEMBLY",
                    self._place_state(
                        "ASSEMBLY_SUBFSM/PLACE_COVER_AT_ASSEMBLY",
                        "ur5e_assembly",
                        "cover",
                        "assembly_cover_frame",
                        precise=True,
                    ),
                ),
                (
                    "UPDATE_SMALL_BEARING_AT_ASSEMBLY",
                    self._update_frame_state(
                        "ASSEMBLY_SUBFSM/UPDATE_SMALL_BEARING_AT_ASSEMBLY",
                        [("small_bearing", "assembly_cover_frame")],
                    ),
                ),
            ]
        )

        return self._build_linear_subfsm("ASSEMBLY_SUBFSM", states)

    def _build_screw_subfsm(self) -> StateMachine:
        states: List[Tuple[str, State]] = []
        for index, screw_frame in enumerate(self.config["assembly"]["screw_frames"], start=1):
            states.append(
                (
                    f"RUN_SCREW_{index}",
                    self._screw_state(
                        f"SCREW_SUBFSM/RUN_SCREW_{index}",
                        screw_frame,
                    ),
                )
            )
        return self._build_linear_subfsm("SCREW_SUBFSM", states)

    _LOOSE_PARTS = [
        "lower_housing", "main_bearing", "cover", "small_bearing",
        "housing", "ring_gear", "planet_1", "planet_2", "planet_3",
        "sun_gear", "carrier",
    ]

    def _hide_all_loose_parts(
        self,
        _blackboard: Blackboard,
        _bias_xy: Tuple[float, float],
    ) -> None:
        """Remove every loose part from the world.

        _hide_part re-anchors the TF frame underground AND removes the
        Gazebo model, so nothing is left as debris. Two passes with a
        short sleep win any Gazebo sync race.
        """
        if not self.visual_unload_demo:
            raise RuntimeError(
                "HIDE_PARTS is demo-only: no physical merged assembly model is "
                "available for strict unload"
            )

        self.get_logger().warn(
            "DEMO unload: hiding loose models before revealing assembled_gearbox"
        )
        for part_name in self._LOOSE_PARTS:
            self._hide_part(part_name)
        time.sleep(0.6)
        for part_name in self._LOOSE_PARTS:
            self._hide_part(part_name)
        time.sleep(0.8)
        self.get_logger().info("HIDE_PARTS: all loose parts removed")

    def _pick_assembled_gearbox(
        self,
        _blackboard: Blackboard,
        bias_xy: Tuple[float, float],
    ) -> None:
        """Reveal the assembled_gearbox at the assembly station then pick it.

        The model is static=true so _move_gz_model (gz set_pose) places it
        precisely. We register it in part_states so grasp_attacher tracks it,
        attach it to the ur5e_assembly tool frame, and lift.
        """
        if not self.visual_unload_demo:
            raise RuntimeError(
                "PICK_ASSEMBLED is demo-only: assembled_gearbox visual handoff "
                "is disabled"
            )

        asm_x = self.config.get("assembly", {}).get("assembled_x", 0.66)
        asm_y = self.config.get("assembly", {}).get("assembled_y", 0.39)
        asm_z = self.config.get("assembly", {}).get("assembled_z", 0.83)

        # Teleport the static model to its assembly-station position.
        self._move_gz_model("assembled_gearbox", asm_x, asm_y, asm_z)
        time.sleep(1.0)
        self._move_gz_model("assembled_gearbox", asm_x, asm_y, asm_z)
        time.sleep(1.5)
        self.get_logger().info(
            f"PICK_ASSEMBLED: revealed assembled_gearbox at "
            f"({asm_x:.2f}, {asm_y:.2f}, {asm_z:.2f})"
        )

        # Register in part_states anchored to the static grasp TF frame.
        part_links = self.config.get("part_links", {})
        self.part_states["assembled_gearbox"] = PartState(
            parent_frame="assembled_gearbox_grasp_frame",
            link_name=part_links.get("assembled_gearbox", "assembled_gearbox"),
            xyz=(0.0, 0.0, 0.0),
            quat=(0.0, 0.0, 0.0, 1.0),
        )

        robot_name = "ur5e_assembly"
        cfg = self.motion.robot_configs[robot_name]
        self.motion.execute_frame_motion(
            robot_name=robot_name,
            target_frame="assembled_gearbox_grasp_frame",
            approach_height_m=cfg.approach_height_m,
            insertion_depth_m=cfg.insertion_depth_m,
            approach_bias_xy=bias_xy,
        )
        self._set_attachment(robot_name, "assembled_gearbox", attach=True)
        self.motion.execute_precision_departure(
            robot_name=robot_name,
            target_frame="assembled_gearbox_grasp_frame",
            z_offset=cfg.approach_height_m,
            steps=6,
            approach_bias_xy=bias_xy,
        )
        # Track the gearbox to the tool frame during the carry.
        self._set_part_frame("assembled_gearbox", cfg.tool_frame)

    def _place_assembled_at_output(
        self,
        _blackboard: Blackboard,
        bias_xy: Tuple[float, float],
    ) -> None:
        """Place the assembled gearbox on the output tray and detach."""
        if not self.visual_unload_demo:
            raise RuntimeError(
                "PLACE_AT_OUTPUT is demo-only: assembled_gearbox visual handoff "
                "is disabled"
            )

        robot_name = "ur5e_assembly"
        cfg = self.motion.robot_configs[robot_name]
        output_frame = self.config.get("assembly", {}).get(
            "output_frame", "output_tray_drop_frame"
        )

        self.motion.execute_precision_insertion(
            robot_name=robot_name,
            target_frame=output_frame,
            z_offset=cfg.approach_height_m,
            steps=8,
            approach_bias_xy=bias_xy,
        )
        self._set_attachment(robot_name, "assembled_gearbox", attach=False)
        # Anchor the TF frame to the drop frame so the model stays put.
        self._set_part_frame("assembled_gearbox", output_frame)
        # Teleport the static Gazebo model to the tray (output_xyz base Z 0.84).
        self._move_gz_model("assembled_gearbox", 0.20, -0.19, 0.84)
        try:
            self.motion.execute_precision_departure(
                robot_name=robot_name,
                target_frame=output_frame,
                z_offset=cfg.approach_height_m,
                steps=6,
                approach_bias_xy=bias_xy,
            )
        except Exception as exc:  # noqa: BLE001
            self.get_logger().warn(
                f"PLACE_AT_OUTPUT: departure raised (non-fatal): {exc}"
            )
        self.get_logger().info(
            f"PLACE_AT_OUTPUT: assembled gearbox placed on output tray "
            f"via {output_frame}"
        )

    def _build_fsm(self) -> StateMachine:
        sm = self._make_state_machine(
            "GEARBOX_ASSEMBLY_FSM",
            [SUCCEEDED, ABORTED],
            handle_sigint=True,
        )

        self._add_state(
            sm,
            "IDLE",
            DelayState(self, self.start_delay_sec),
            {OK: "HOMING", FAILED: "ABORT"},
        )
        self._add_state(
            sm,
            "HOMING",
            HomingState(self),
            {OK: "PRESS_SUBFSM", FAILED: "ERROR_RECOVERY"},
        )
        self._add_state(
            sm,
            "PRESS_SUBFSM",
            self._build_press_subfsm(),
            {OK: "ASSEMBLY_SUBFSM", FAILED: "ERROR_RECOVERY"},
        )
        self._add_state(
            sm,
            "ASSEMBLY_SUBFSM",
            self._build_assembly_subfsm(),
            {OK: "SCREW_SUBFSM", FAILED: "ERROR_RECOVERY"},
        )
        self._add_state(
            sm,
            "SCREW_SUBFSM",
            self._build_screw_subfsm(),
            {OK: "HIDE_PARTS", FAILED: "ERROR_RECOVERY"},
        )
        # --- UNLOAD sequence: hide loose parts, then pick-and-place the gearbox ---
        self._add_state(
            sm,
            "HIDE_PARTS",
            OperationState(
                self,
                "HIDE_PARTS",
                None,
                self._hide_all_loose_parts,
            ),
            {OK: "PICK_ASSEMBLED", FAILED: "ERROR_RECOVERY"},
        )
        self._add_state(
            sm,
            "PICK_ASSEMBLED",
            OperationState(
                self,
                "PICK_ASSEMBLED",
                "ur5e_assembly",
                self._pick_assembled_gearbox,
            ),
            {OK: "PLACE_AT_OUTPUT", FAILED: "ERROR_RECOVERY"},
        )
        self._add_state(
            sm,
            "PLACE_AT_OUTPUT",
            OperationState(
                self,
                "PLACE_AT_OUTPUT",
                "ur5e_assembly",
                self._place_assembled_at_output,
            ),
            {OK: "DONE", FAILED: "ERROR_RECOVERY"},
        )

        top_recovery = ErrorRecoveryState(
            self,
            "ERROR_RECOVERY",
            ["HOMING", "HIDE_PARTS", "PICK_ASSEMBLED", "PLACE_AT_OUTPUT"],
        )
        self._add_state(
            sm,
            "ERROR_RECOVERY",
            top_recovery,
            {
                "HOMING": "HOMING",
                "HIDE_PARTS": "HIDE_PARTS",
                "PICK_ASSEMBLED": "PICK_ASSEMBLED",
                "PLACE_AT_OUTPUT": "PLACE_AT_OUTPUT",
                FAILED: "ABORT",
            },
        )
        self._add_state(
            sm,
            "DONE",
            TerminalState(self, "DONE", SUCCEEDED, "Assembly FSM completed"),
            {SUCCEEDED: SUCCEEDED},
        )
        self._add_state(
            sm,
            "ABORT",
            TerminalState(self, "ABORT", ABORTED, "Assembly FSM aborted"),
            {ABORTED: ABORTED},
        )
        self._set_start_state(sm, "IDLE")
        return sm


def main() -> None:
    rclpy.init()
    set_ros_loggers()
    node = AssemblyFsmNode()
    try:
        rclpy.spin(node)
    finally:
        if hasattr(node.viewer_pub, "cleanup"):
            node.viewer_pub.cleanup()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
