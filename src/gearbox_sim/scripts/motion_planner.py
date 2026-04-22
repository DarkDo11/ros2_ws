#!/usr/bin/env python3
from __future__ import annotations

import math
import time
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional, Sequence, Tuple

import rclpy
import yaml
from builtin_interfaces.msg import Duration
from geometry_msgs.msg import Pose, PoseStamped
from rclpy.duration import Duration as RclpyDuration
from rclpy.node import Node
from rclpy.time import Time
from sensor_msgs.msg import JointState
from tf2_geometry_msgs import do_transform_pose
from tf2_ros import Buffer, TransformException, TransformListener
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint


def _try_import_moveit():
    try:
        from moveit_msgs.msg import RobotState
        from moveit_msgs.srv import GetCartesianPath, GetPositionIK

        return {
            "RobotState": RobotState,
            "GetCartesianPath": GetCartesianPath,
            "GetPositionIK": GetPositionIK,
        }
    except Exception:
        return None


class PlanningFailure(RuntimeError):
    pass


def duration_from_seconds(value: float) -> Duration:
    sec = int(value)
    nanosec = int((value - sec) * 1e9)
    return Duration(sec=sec, nanosec=nanosec)


@dataclass
class RobotConfig:
    name: str
    planning_group: str
    trajectory_topic: str
    tool_frame: str
    reference_frame: str
    joint_names: List[str]
    home_joint_positions: List[float]
    approach_height_m: float
    insertion_depth_m: float


class MotionPlannerFacade:
    def __init__(self, node: Node, config_file: str, dry_run: bool = False):
        self.node = node
        self.dry_run = dry_run
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self.node, spin_thread=True)
        self.moveit = _try_import_moveit()
        self._moveit_clients = {}

        with Path(config_file).open("r", encoding="utf-8") as stream:
            cfg = yaml.safe_load(stream)

        self.robot_configs: Dict[str, RobotConfig] = {}
        self.traj_publishers = {}
        for name, data in cfg["robots"].items():
            self.robot_configs[name] = RobotConfig(
                name=name,
                planning_group=data["planning_group"],
                trajectory_topic=data["trajectory_topic"],
                tool_frame=data["tool_frame"],
                reference_frame=data.get("reference_frame", "world"),
                joint_names=list(data["joint_names"]),
                home_joint_positions=list(
                    data.get("home_joint_positions", [0.0] * len(data["joint_names"]))
                ),
                approach_height_m=float(data["approach_height_m"]),
                insertion_depth_m=float(data["insertion_depth_m"]),
            )
            self.traj_publishers[name] = self.node.create_publisher(
                JointTrajectory,
                data["trajectory_topic"],
                10,
            )

        if self.moveit is None:
            self.node.get_logger().warn(
                "MoveIt2 Python interfaces are unavailable. Motion planner will run in dry-run mode."
            )
            self.dry_run = True

    def _wait_for_future(self, future, timeout_sec: float, description: str):
        deadline = time.monotonic() + timeout_sec
        while rclpy.ok() and not future.done():
            if time.monotonic() >= deadline:
                raise PlanningFailure(f"{description} timed out after {timeout_sec:.2f}s")
            time.sleep(0.01)

        if future.cancelled():
            raise PlanningFailure(f"{description} was cancelled")
        if future.exception() is not None:
            raise PlanningFailure(f"{description} failed: {future.exception()}") from future.exception()
        return future.result()

    def _ensure_moveit_clients(self):
        if self.moveit is None or self._moveit_clients:
            return

        get_ik = self.moveit["GetPositionIK"]
        get_cart = self.moveit["GetCartesianPath"]
        self._moveit_clients["ik"] = self.node.create_client(get_ik, "/compute_ik")
        self._moveit_clients["cartesian"] = self.node.create_client(get_cart, "/compute_cartesian_path")

    def _lookup_transform(self, target_frame: str, source_frame: str, timeout_sec: float = 1.0):
        try:
            return self.tf_buffer.lookup_transform(
                target_frame,
                source_frame,
                Time(),
                timeout=RclpyDuration(seconds=timeout_sec),
            )
        except TransformException as exc:
            raise PlanningFailure(f"TF lookup failed: {target_frame} <- {source_frame}: {exc}") from exc

    def _transform_pose(
        self,
        pose_stamped: PoseStamped,
        target_frame: str,
        timeout_sec: float = 1.0,
    ) -> PoseStamped:
        transform = self._lookup_transform(target_frame, pose_stamped.header.frame_id, timeout_sec=timeout_sec)
        transformed_pose = do_transform_pose(pose_stamped.pose, transform)
        transformed = PoseStamped()
        transformed.header.frame_id = target_frame
        transformed.header.stamp = self.node.get_clock().now().to_msg()
        transformed.pose = transformed_pose
        return transformed

    def _pose_in_frame(
        self,
        source_frame: str,
        reference_frame: str,
        xyz: Tuple[float, float, float],
        quat: Tuple[float, float, float, float] = (0.0, 0.0, 0.0, 1.0),
        timeout_sec: float = 1.0,
    ) -> PoseStamped:
        local_pose = PoseStamped()
        local_pose.header.frame_id = source_frame
        local_pose.header.stamp = self.node.get_clock().now().to_msg()
        local_pose.pose.position.x = float(xyz[0])
        local_pose.pose.position.y = float(xyz[1])
        local_pose.pose.position.z = float(xyz[2])
        local_pose.pose.orientation.x = float(quat[0])
        local_pose.pose.orientation.y = float(quat[1])
        local_pose.pose.orientation.z = float(quat[2])
        local_pose.pose.orientation.w = float(quat[3])
        return self._transform_pose(local_pose, reference_frame, timeout_sec=timeout_sec)

    def _log_pose(self, label: str, pose_stamped: PoseStamped):
        pose = pose_stamped.pose
        self.node.get_logger().info(
            (
                f"{label}: frame={pose_stamped.header.frame_id} "
                f"xyz=({pose.position.x:.5f}, {pose.position.y:.5f}, {pose.position.z:.5f}) "
                f"quat=({pose.orientation.x:.5f}, {pose.orientation.y:.5f}, "
                f"{pose.orientation.z:.5f}, {pose.orientation.w:.5f})"
            )
        )

    def lookup_pose(
        self,
        frame: str,
        reference_frame: str = "world",
        timeout_sec: float = 1.0,
    ) -> Pose:
        return self._pose_in_frame(
            source_frame=frame,
            reference_frame=reference_frame,
            xyz=(0.0, 0.0, 0.0),
            timeout_sec=timeout_sec,
        ).pose

    def compute_ik(
        self,
        robot_name: str,
        target_pose: PoseStamped,
        timeout_sec: float = 0.5,
    ):
        self._log_pose(f"{robot_name}: IK target", target_pose)
        if self.dry_run:
            self.node.get_logger().info(f"[dry-run] compute_ik for {robot_name}")
            return None

        self._ensure_moveit_clients()
        ik_client = self._moveit_clients["ik"]
        if not ik_client.wait_for_service(timeout_sec=timeout_sec):
            self.node.get_logger().warn("MoveIt2 /compute_ik is not available; switching planner to dry-run.")
            self.dry_run = True
            return None

        request = self.moveit["GetPositionIK"].Request()
        request.ik_request.group_name = self.robot_configs[robot_name].planning_group
        request.ik_request.ik_link_name = self.robot_configs[robot_name].tool_frame
        request.ik_request.pose_stamped = target_pose
        request.ik_request.timeout = duration_from_seconds(timeout_sec)

        future = ik_client.call_async(request)
        result = self._wait_for_future(
            future,
            timeout_sec=timeout_sec + 0.5,
            description=f"MoveIt2 IK request for {robot_name}",
        )
        if result is None:
            raise PlanningFailure("MoveIt2 IK request timed out")
        error_code = getattr(result.error_code, "val", 1)
        if error_code != 1:
            raise PlanningFailure(f"IK failed for {robot_name} with MoveIt error code {error_code}")
        return result

    def plan_cartesian_path(
        self,
        robot_name: str,
        waypoints: Sequence[PoseStamped],
        max_step: float = 0.002,
        jump_threshold: float = 0.0,
        timeout_sec: float = 2.0,
    ):
        for index, waypoint in enumerate(waypoints, start=1):
            self._log_pose(f"{robot_name}: cartesian waypoint {index}", waypoint)

        if self.dry_run:
            self.node.get_logger().info(
                f"[dry-run] plan_cartesian_path for {robot_name} with {len(waypoints)} waypoints"
            )
            return None

        self._ensure_moveit_clients()
        cart_client = self._moveit_clients["cartesian"]
        if not cart_client.wait_for_service(timeout_sec=timeout_sec):
            self.node.get_logger().warn(
                "MoveIt2 /compute_cartesian_path is not available; switching planner to dry-run."
            )
            self.dry_run = True
            return None

        cfg = self.robot_configs[robot_name]
        request = self.moveit["GetCartesianPath"].Request()
        request.header.frame_id = cfg.reference_frame
        request.header.stamp = self.node.get_clock().now().to_msg()
        request.group_name = cfg.planning_group
        request.link_name = cfg.tool_frame
        request.max_step = max_step
        request.jump_threshold = jump_threshold
        request.avoid_collisions = True
        request.waypoints = [waypoint.pose for waypoint in waypoints]
        request.start_state = self.moveit["RobotState"]()
        request.start_state.joint_state = JointState()

        future = cart_client.call_async(request)
        result = self._wait_for_future(
            future,
            timeout_sec=timeout_sec + 0.5,
            description=f"MoveIt2 cartesian path request for {robot_name}",
        )
        if result is None:
            raise PlanningFailure("MoveIt2 cartesian path request timed out")
        fraction = float(getattr(result, "fraction", 0.0))
        if fraction < 0.999:
            raise PlanningFailure(
                f"Cartesian path for {robot_name} is incomplete: fraction={fraction:.3f}"
            )

        error_code = getattr(getattr(result, "error_code", None), "val", 1)
        if error_code != 1:
            raise PlanningFailure(
                f"Cartesian path for {robot_name} failed with MoveIt error code {error_code}"
            )
        return result

    def execute_joint_trajectory(
        self,
        robot_name: str,
        joint_names: Sequence[str],
        points: Sequence[JointTrajectoryPoint],
    ) -> None:
        if self.dry_run:
            total = 0.0
            if points:
                last = points[-1].time_from_start
                total = float(last.sec) + float(last.nanosec) * 1e-9
            self.node.get_logger().info(
                f"[dry-run] execute_joint_trajectory on {robot_name}, points={len(points)}, duration={total:.2f}s"
            )
            time.sleep(min(max(total, 0.2), 1.0))
            return

        msg = JointTrajectory()
        msg.header.stamp = self.node.get_clock().now().to_msg()
        msg.joint_names = list(joint_names)
        msg.points = list(points)
        self.traj_publishers[robot_name].publish(msg)

        if points:
            last = points[-1].time_from_start
            total = float(last.sec) + float(last.nanosec) * 1e-9
            time.sleep(max(total, 0.1))

    def execute_moveit_trajectory(self, robot_name: str, result) -> None:
        if result is None:
            return
        trajectory = (
            result.solution.joint_trajectory
            if hasattr(result, "solution")
            else result.trajectory.joint_trajectory
        )
        self.execute_joint_trajectory(robot_name, trajectory.joint_names, trajectory.points)

    def move_to_safe_pose(self, robot_name: str, duration_sec: float = 2.5) -> None:
        cfg = self.robot_configs[robot_name]
        self.node.get_logger().info(
            f"{robot_name}: moving to safe pose {cfg.home_joint_positions}"
        )
        point = JointTrajectoryPoint()
        point.positions = list(cfg.home_joint_positions)
        point.time_from_start = duration_from_seconds(duration_sec)
        self.execute_joint_trajectory(robot_name, cfg.joint_names, [point])

    def _generate_local_z_waypoints(
        self,
        robot_name: str,
        target_frame: str,
        z_start: float,
        z_end: float,
        steps: int,
        approach_bias_xy: Tuple[float, float],
    ) -> List[PoseStamped]:
        cfg = self.robot_configs[robot_name]
        step_count = max(2, int(steps))
        waypoints: List[PoseStamped] = []
        for index in range(step_count + 1):
            alpha = index / float(step_count)
            local_z = z_start + (z_end - z_start) * alpha
            waypoint = self._pose_in_frame(
                source_frame=target_frame,
                reference_frame=cfg.reference_frame,
                xyz=(approach_bias_xy[0], approach_bias_xy[1], local_z),
            )
            waypoints.append(waypoint)
        return waypoints

    def _execute_local_z_cartesian(
        self,
        robot_name: str,
        target_frame: str,
        z_start: float,
        z_end: float,
        steps: int,
        approach_bias_xy: Tuple[float, float] = (0.0, 0.0),
        timeout_sec: float = 2.0,
    ) -> None:
        waypoints = self._generate_local_z_waypoints(
            robot_name=robot_name,
            target_frame=target_frame,
            z_start=z_start,
            z_end=z_end,
            steps=steps,
            approach_bias_xy=approach_bias_xy,
        )

        self.compute_ik(robot_name, waypoints[0], timeout_sec=0.5)
        self.compute_ik(robot_name, waypoints[-1], timeout_sec=0.5)
        result = self.plan_cartesian_path(
            robot_name,
            waypoints,
            max_step=max(0.001, abs(z_end - z_start) / max(steps * 2, 6)),
            timeout_sec=timeout_sec,
        )
        self.execute_moveit_trajectory(robot_name, result)

    def execute_frame_motion(
        self,
        robot_name: str,
        target_frame: str,
        approach_height_m: Optional[float] = None,
        insertion_depth_m: Optional[float] = None,
        approach_bias_xy: Tuple[float, float] = (0.0, 0.0),
    ) -> None:
        cfg = self.robot_configs[robot_name]
        z_start = cfg.approach_height_m if approach_height_m is None else float(approach_height_m)
        z_end = cfg.insertion_depth_m if insertion_depth_m is None else float(insertion_depth_m)
        travel = abs(z_end - z_start)
        steps = max(4, int(math.ceil(travel / 0.005)))
        self._execute_local_z_cartesian(
            robot_name=robot_name,
            target_frame=target_frame,
            z_start=z_start,
            z_end=z_end,
            steps=steps,
            approach_bias_xy=approach_bias_xy,
            timeout_sec=2.5,
        )

    def execute_precision_insertion(
        self,
        robot_name: str,
        target_frame: str,
        z_offset: float,
        steps: int,
        approach_bias_xy: Tuple[float, float] = (0.0, 0.0),
    ) -> None:
        self.node.get_logger().info(
            f"{robot_name}: precision insertion into {target_frame} "
            f"from local z={z_offset:.4f} with steps={steps}"
        )
        self._execute_local_z_cartesian(
            robot_name=robot_name,
            target_frame=target_frame,
            z_start=float(z_offset),
            z_end=0.0,
            steps=max(3, int(steps)),
            approach_bias_xy=approach_bias_xy,
            timeout_sec=3.0,
        )

    def execute_precision_departure(
        self,
        robot_name: str,
        target_frame: str,
        z_offset: float,
        steps: int,
        approach_bias_xy: Tuple[float, float] = (0.0, 0.0),
    ) -> None:
        self.node.get_logger().info(
            f"{robot_name}: precision departure from {target_frame} "
            f"to local z={z_offset:.4f} with steps={steps}"
        )
        self._execute_local_z_cartesian(
            robot_name=robot_name,
            target_frame=target_frame,
            z_start=0.0,
            z_end=float(z_offset),
            steps=max(3, int(steps)),
            approach_bias_xy=approach_bias_xy,
            timeout_sec=3.0,
        )

    def execute_pick_and_place(
        self,
        robot_name: str,
        source_frame: str,
        target_frame: str,
        approach_height_m: Optional[float] = None,
        insertion_depth_m: Optional[float] = None,
        approach_bias_xy: Tuple[float, float] = (0.0, 0.0),
    ) -> None:
        self.node.get_logger().info(
            f"{robot_name}: planning transfer {source_frame} -> {target_frame}"
        )
        self.execute_frame_motion(
            robot_name,
            source_frame,
            approach_height_m=approach_height_m,
            insertion_depth_m=insertion_depth_m,
            approach_bias_xy=approach_bias_xy,
        )
        self.execute_frame_motion(
            robot_name,
            target_frame,
            approach_height_m=approach_height_m,
            insertion_depth_m=insertion_depth_m,
            approach_bias_xy=approach_bias_xy,
        )


class MotionPlannerNode(Node):
    def __init__(self):
        super().__init__("motion_planner")
        default_config = (
            Path(__file__).resolve().parents[1] / "config" / "assembly_cell.yaml"
        )
        self.declare_parameter("config_file", str(default_config))
        self.declare_parameter("inspect_frame", "")
        self.declare_parameter("dry_run", True)

        config_file = self.get_parameter("config_file").get_parameter_value().string_value
        dry_run = self.get_parameter("dry_run").get_parameter_value().bool_value
        self.planner = MotionPlannerFacade(self, config_file=config_file, dry_run=dry_run)

        self.inspect_frame = self.get_parameter("inspect_frame").get_parameter_value().string_value
        if self.inspect_frame:
            self.timer = self.create_timer(1.0, self._inspect_frame_cb)

    def _inspect_frame_cb(self):
        try:
            pose = self.planner.lookup_pose(self.inspect_frame)
        except Exception as exc:
            self.get_logger().warn(str(exc))
            return
        self.get_logger().info(
            (
                "frame=%s xyz=(%.4f, %.4f, %.4f) quat=(%.4f, %.4f, %.4f, %.4f)"
                % (
                    self.inspect_frame,
                    pose.position.x,
                    pose.position.y,
                    pose.position.z,
                    pose.orientation.x,
                    pose.orientation.y,
                    pose.orientation.z,
                    pose.orientation.w,
                )
            )
        )


def main():
    rclpy.init()
    node = MotionPlannerNode()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
