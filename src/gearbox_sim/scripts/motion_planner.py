#!/usr/bin/env python3
from __future__ import annotations

import math
import time
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional, Sequence, Tuple

import numpy as np
import rclpy
import yaml

try:
    import ur_kinematics as _urk
except ImportError:  # installed as a module alongside this script
    from gearbox_sim import ur_kinematics as _urk  # type: ignore
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
    ur_type: str = "ur5e"
    base_frame: str = ""
    tcp_in_tool0: Tuple[float, float, float] = (0.0, 0.0, 0.0)


class MotionPlannerFacade:
    def __init__(self, node: Node, config_file: str, dry_run: bool = False):
        self.node = node
        self.dry_run = dry_run
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self.node, spin_thread=True)
        self.moveit = _try_import_moveit()
        self._moveit_clients = {}
        self._latest_joint_state: Optional[JointState] = None
        self.node.create_subscription(JointState, "/joint_states", self._joint_state_cb, 10)

        with Path(config_file).open("r", encoding="utf-8") as stream:
            cfg = yaml.safe_load(stream)

        self.robot_configs: Dict[str, RobotConfig] = {}
        self.traj_publishers = {}
        # Cache of (T_world_base, T_tool0_tcp) per arm, filled lazily from TF.
        self._kin_cache: Dict[str, tuple] = {}
        for name, data in cfg["robots"].items():
            joint_names = list(data["joint_names"])
            # ur_type from the joint prefix: ur3e_* arms use the shorter links.
            ur_type = "ur3e" if "ur3e" in name else "ur5e"
            # The IK solves to tool0; tcp_frame hangs off tool0 by a fixed Z.
            # ur5e gripper TCP = 0.182 (tool_plate) +0.012 +0.009 ft ≈ 0.203 below
            # tool0 along the tool axis; ur3e screwdriver TCP differs. Pull from
            # config if present, else use the gripper default.
            tcp_z = float(data.get("tcp_offset_from_tool0_m", 0.203))
            self.robot_configs[name] = RobotConfig(
                name=name,
                planning_group=data["planning_group"],
                trajectory_topic=data["trajectory_topic"],
                tool_frame=data["tool_frame"],
                reference_frame=data.get("reference_frame", "world"),
                joint_names=joint_names,
                home_joint_positions=list(
                    data.get("home_joint_positions", [0.0] * len(joint_names))
                ),
                approach_height_m=float(data["approach_height_m"]),
                insertion_depth_m=float(data["insertion_depth_m"]),
                ur_type=ur_type,
                base_frame=data.get("base_frame", f"{name}_base_link"),
                tcp_in_tool0=(0.0, 0.0, tcp_z),
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

    def _joint_state_cb(self, msg: JointState) -> None:
        if self._latest_joint_state is None:
            self._latest_joint_state = msg
        else:
            combined = JointState()
            combined.header = msg.header
            existing = dict(zip(self._latest_joint_state.name, zip(
                self._latest_joint_state.position,
                self._latest_joint_state.velocity,
                self._latest_joint_state.effort,
            )))
            for i, name in enumerate(msg.name):
                pos = msg.position[i] if i < len(msg.position) else 0.0
                vel = msg.velocity[i] if i < len(msg.velocity) else 0.0
                eff = msg.effort[i] if i < len(msg.effort) else 0.0
                existing[name] = (pos, vel, eff)
            for name, (pos, vel, eff) in existing.items():
                combined.name.append(name)
                combined.position.append(pos)
                combined.velocity.append(vel)
                combined.effort.append(eff)
            self._latest_joint_state = combined

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
        # Seed IK from the robot's home configuration for deterministic results.
        if self._latest_joint_state is not None:
            request.ik_request.robot_state = self.moveit["RobotState"]()
            request.ik_request.robot_state.joint_state = self._latest_joint_state

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
        ik_seed=None,
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
        request.avoid_collisions = False
        request.waypoints = [waypoint.pose for waypoint in waypoints]
        request.start_state = self.moveit["RobotState"]()
        if ik_seed is not None and hasattr(ik_seed, "solution"):
            request.start_state = ik_seed.solution
        elif self._latest_joint_state is not None:
            request.start_state.joint_state = self._latest_joint_state
        else:
            request.start_state.is_diff = True

        future = cart_client.call_async(request)
        result = self._wait_for_future(
            future,
            timeout_sec=timeout_sec + 0.5,
            description=f"MoveIt2 cartesian path request for {robot_name}",
        )
        if result is None:
            raise PlanningFailure("MoveIt2 cartesian path request timed out")
        fraction = float(getattr(result, "fraction", 0.0))
        if fraction < 0.75:
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
        total = 0.0
        if points:
            last = points[-1].time_from_start
            total = float(last.sec) + float(last.nanosec) * 1e-9

        if self.dry_run:
            self.node.get_logger().info(
                f"[dry-run] execute_joint_trajectory on {robot_name}, points={len(points)}, duration={total:.2f}s"
            )
            if points and robot_name in self.traj_publishers:
                msg = JointTrajectory()
                msg.header.stamp = self.node.get_clock().now().to_msg()
                msg.joint_names = list(joint_names)
                msg.points = list(points)
                self.traj_publishers[robot_name].publish(msg)
            time.sleep(min(max(total, 0.2), 2.5))
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

    def _execute_fake_reach(self, robot_name: str, duration: float = 1.5) -> None:
        """Publish a reach-and-return trajectory for visual feedback in dry_run mode."""
        cfg = self.robot_configs[robot_name]
        if robot_name not in self.traj_publishers:
            time.sleep(duration)
            return

        home = list(cfg.home_joint_positions)
        reach = list(home)
        if len(reach) >= 4:
            reach[1] = home[1] - 0.45  # shoulder_lift: extend arm forward/down
            reach[2] = home[2] - 0.55  # elbow: extend more
            reach[3] = home[3] + 0.55  # wrist_1: compensate for approach angle

        msg = JointTrajectory()
        msg.header.stamp = self.node.get_clock().now().to_msg()
        msg.joint_names = list(cfg.joint_names)

        p_reach = JointTrajectoryPoint()
        p_reach.positions = reach
        p_reach.time_from_start = duration_from_seconds(duration * 0.5)

        p_return = JointTrajectoryPoint()
        p_return.positions = home
        p_return.time_from_start = duration_from_seconds(duration)

        msg.points = [p_reach, p_return]
        self.traj_publishers[robot_name].publish(msg)
        time.sleep(duration + 0.1)

    def execute_moveit_trajectory(self, robot_name: str, result) -> None:
        if result is None:
            if self.dry_run:
                self._execute_fake_reach(robot_name)
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

    def _quat_to_matrix(self, qx: float, qy: float, qz: float, qw: float) -> np.ndarray:
        n = math.sqrt(qx * qx + qy * qy + qz * qz + qw * qw)
        if n < 1e-12:
            return np.eye(3)
        qx, qy, qz, qw = qx / n, qy / n, qz / n, qw / n
        return np.array([
            [1 - 2 * (qy * qy + qz * qz), 2 * (qx * qy - qz * qw), 2 * (qx * qz + qy * qw)],
            [2 * (qx * qy + qz * qw), 1 - 2 * (qx * qx + qz * qz), 2 * (qy * qz - qx * qw)],
            [2 * (qx * qz - qy * qw), 2 * (qy * qz + qx * qw), 1 - 2 * (qx * qx + qy * qy)],
        ])

    def _transform_to_matrix(self, transform) -> np.ndarray:
        t = transform.transform.translation
        r = transform.transform.rotation
        m = np.eye(4)
        m[:3, :3] = self._quat_to_matrix(r.x, r.y, r.z, r.w)
        m[:3, 3] = [t.x, t.y, t.z]
        return m

    def _get_kin(self, robot_name: str):
        """Return (T_world_base, T_tool0_tcp) for this arm, cached from TF.

        The IK solves base_link -> tool0; callers give a world-frame tcp_frame
        pose, so we need both the static world->base mount and the fixed
        tool0->tcp offset to convert into a base-frame tool0 target.
        """
        if robot_name in self._kin_cache:
            return self._kin_cache[robot_name]
        cfg = self.robot_configs[robot_name]
        base = self._lookup_transform("world", cfg.base_frame, timeout_sec=3.0)
        tool0_tcp = self._lookup_transform(
            f"{robot_name}_tool0", cfg.tool_frame, timeout_sec=3.0
        )
        pair = (self._transform_to_matrix(base), self._transform_to_matrix(tool0_tcp))
        self._kin_cache[robot_name] = pair
        return pair

    def _solve_ik_for_pose(self, robot_name: str, pose: PoseStamped, seed):
        """World-frame tcp_frame PoseStamped -> joint solution via validated IK."""
        cfg = self.robot_configs[robot_name]
        t_world_base, t_tool0_tcp = self._get_kin(robot_name)
        # world -> tcp target
        p = pose.pose
        w_tcp = np.eye(4)
        w_tcp[:3, :3] = self._quat_to_matrix(
            p.orientation.x, p.orientation.y, p.orientation.z, p.orientation.w
        )
        w_tcp[:3, 3] = [p.position.x, p.position.y, p.position.z]
        # world -> tool0 = (world -> tcp) @ inv(tool0 -> tcp)
        w_tool0 = w_tcp @ np.linalg.inv(t_tool0_tcp)
        base_tool0 = np.linalg.inv(t_world_base) @ w_tool0
        # rot_weight=0.6: honour the (now-correct, gripper-down) tool orientation
        # while still tolerating a few degrees of tilt near full extension.
        # tol=3mm position: visually exact and robust with the chained seed.
        sol, ok = _urk.ik(
            cfg.ur_type, base_tool0, seed, max_iters=200, tol=3e-3, rot_weight=0.6
        )
        # Defence-in-depth: reject any solution whose tool0 Z-axis points UP in
        # world (gripper coming from under the table). The orientation target is
        # already gripper-down, but a flipped branch can still satisfy position;
        # this guarantees we never return an under-table reach.
        tool_z_world = (t_world_base[:3, :3] @ _urk.fk(cfg.ur_type, sol)[:3, 2])[2]
        if tool_z_world > 0.0:
            ok = False
        return sol, ok

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
            # Orientation: flip π about the frame's X so the GRIPPER points DOWN.
            # The tool0->tcp transform itself flips Z (rpy=[π,0,π/2]); pick/place
            # frames already have Z down (rpy="π 0 0"). Feeding identity here made
            # the *tool0* target point UP, so IK reached every point with the
            # wrist flipped 180° — the "approach from under the table" bug. The
            # extra π-about-X cancels the tcp flip so tool0 Z = world −Z (down).
            waypoint = self._pose_in_frame(
                source_frame=target_frame,
                reference_frame=cfg.reference_frame,
                xyz=(approach_bias_xy[0], approach_bias_xy[1], local_z),
                quat=(1.0, 0.0, 0.0, 0.0),
            )
            waypoints.append(waypoint)
        return waypoints

    def _current_joints(self, robot_name: str) -> List[float]:
        """Current joint positions for this arm, falling back to home config."""
        cfg = self.robot_configs[robot_name]
        if self._latest_joint_state is not None:
            lookup = dict(
                zip(self._latest_joint_state.name, self._latest_joint_state.position)
            )
            vals = [lookup.get(j) for j in cfg.joint_names]
            if all(v is not None for v in vals):
                return [float(v) for v in vals]
        return list(cfg.home_joint_positions)

    def _world_pose(self, xyz, quat) -> PoseStamped:
        """Build a world-frame PoseStamped (consumed directly by _solve_ik_for_pose)."""
        ps = PoseStamped()
        ps.header.frame_id = "world"
        ps.header.stamp = self.node.get_clock().now().to_msg()
        ps.pose.position.x = float(xyz[0])
        ps.pose.position.y = float(xyz[1])
        ps.pose.position.z = float(xyz[2])
        ps.pose.orientation.x = float(quat[0])
        ps.pose.orientation.y = float(quat[1])
        ps.pose.orientation.z = float(quat[2])
        ps.pose.orientation.w = float(quat[3])
        return ps

    def _transit_waypoints(self, robot_name: str, first_descent_wp: PoseStamped) -> List[PoseStamped]:
        """Up-and-over via-points so the gripper + held part travel ABOVE table
        and pallet height instead of sweeping laterally through obstacles.

        Returns [] for near-vertical moves (e.g. a precision departure) where the
        current TCP is already roughly above the target — no transit needed.
        """
        cfg = self.robot_configs[robot_name]
        t_world_base, t_tool0_tcp = self._get_kin(robot_name)
        cur = self._current_joints(robot_name)
        cur_tcp = t_world_base @ _urk.fk(cfg.ur_type, cur) @ t_tool0_tcp
        cx, cy, cz = cur_tcp[:3, 3]
        tx = first_descent_wp.pose.position.x
        ty = first_descent_wp.pose.position.y
        tz = first_descent_wp.pose.position.z
        lateral = math.hypot(tx - cx, ty - cy)
        if lateral < 0.15:
            return []
        # Transit height: above pallet tops (~0.90) and table tops (~0.83), but
        # within reach. base_z + 0.30 ≈ 1.09 clears surfaces; keep it at least a
        # touch above both the current TCP and the approach point so the path is
        # strictly lift -> traverse -> descend (never dips down mid-transit).
        base_z = float(t_world_base[2, 3])
        transit_z = max(base_z + 0.30, cz + 0.02, tz + 0.04)
        o = first_descent_wp.pose.orientation
        quat = (o.x, o.y, o.z, o.w)
        return [
            self._world_pose((cx, cy, transit_z), quat),  # lift straight up
            self._world_pose((tx, ty, transit_z), quat),  # traverse above target
        ]

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
        cfg = self.robot_configs[robot_name]
        waypoints = self._generate_local_z_waypoints(
            robot_name=robot_name,
            target_frame=target_frame,
            z_start=z_start,
            z_end=z_end,
            steps=steps,
            approach_bias_xy=approach_bias_xy,
        )

        # Prepend an up-and-over transit so the gripper (and any held part) lifts
        # clear of pallet/table height, traverses laterally above all obstacles,
        # then descends vertically onto the approach point — instead of sweeping
        # diagonally through pedestals, press columns or other parts.
        try:
            transit = self._transit_waypoints(robot_name, waypoints[0])
        except PlanningFailure:
            transit = []

        # Solve IK for every waypoint, chaining the seed so the joint path stays
        # continuous (no wrist flips). The TCP physically traverses the Cartesian
        # path, so any grasped part — tracked live by grasp_attacher — follows the
        # tool instead of teleporting.
        try:
            seed = self._current_joints(robot_name)
            joint_path: List[List[float]] = []
            # Transit via-points are optional clearance hops: if one fails IK
            # (e.g. an unreachable lift height), DROP it rather than executing a
            # far-off mid-air pose — the descent below still runs correctly.
            for wp in transit:
                sol, ok = self._solve_ik_for_pose(robot_name, wp, seed)
                if ok:
                    joint_path.append(sol)
                    seed = sol
            # Descent/approach waypoints are the real targets: keep best effort.
            for wp in waypoints:
                sol, ok = self._solve_ik_for_pose(robot_name, wp, seed)
                if not ok:
                    self.node.get_logger().warn(
                        f"{robot_name}: IK did not fully converge for a waypoint "
                        f"on {target_frame}; using best effort."
                    )
                joint_path.append(sol)
                seed = sol
        except PlanningFailure as exc:
            self.node.get_logger().warn(
                f"{robot_name}: kinematic path build failed ({exc}); fake reach."
            )
            self._execute_fake_reach(robot_name)
            return

        # Time-parameterise: constant cadence per segment, clamped for visibility.
        seg_time = max(0.25, float(timeout_sec) / max(1, len(joint_path) - 1))
        points: List[JointTrajectoryPoint] = []
        for i, q in enumerate(joint_path):
            pt = JointTrajectoryPoint()
            pt.positions = [float(v) for v in q]
            pt.time_from_start = duration_from_seconds(seg_time * (i + 1))
            points.append(pt)
        self.execute_joint_trajectory(robot_name, cfg.joint_names, points)

    def execute_frame_motion(
        self,
        robot_name: str,
        target_frame: str,
        approach_height_m: Optional[float] = None,
        insertion_depth_m: Optional[float] = None,
        approach_bias_xy: Tuple[float, float] = (0.0, 0.0),
    ) -> None:
        cfg = self.robot_configs[robot_name]
        # Pick/place frames have rpy="π 0 0" (Z axis pointing down in world).
        # Positive local z moves in the −world_Z direction (into the pallet/surface).
        # Negate both heights so that approach comes from ABOVE the frame (world Z+)
        # and insertion stops just at the part surface.
        z_start = -(cfg.approach_height_m if approach_height_m is None else float(approach_height_m))
        z_end = -(cfg.insertion_depth_m if insertion_depth_m is None else float(insertion_depth_m))
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
        # Negate z_offset: frames have Z pointing down, so +z goes into surface.
        # We approach from above (negative local z) and end at frame origin (z=0).
        z_start = -float(z_offset)
        self.node.get_logger().info(
            f"{robot_name}: precision insertion into {target_frame} "
            f"from local z={z_start:.4f} with steps={steps}"
        )
        self._execute_local_z_cartesian(
            robot_name=robot_name,
            target_frame=target_frame,
            z_start=z_start,
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
        # Negate z_offset: depart upward (away from surface) = negative local z.
        z_end = -float(z_offset)
        self.node.get_logger().info(
            f"{robot_name}: precision departure from {target_frame} "
            f"to local z={z_end:.4f} with steps={steps}"
        )
        self._execute_local_z_cartesian(
            robot_name=robot_name,
            target_frame=target_frame,
            z_start=0.0,
            z_end=z_end,
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
