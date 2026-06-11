#!/usr/bin/env python3
import sys

import rclpy
from builtin_interfaces.msg import Duration
from geometry_msgs.msg import Wrench
from rclpy.node import Node
from sensor_msgs.msg import JointState
from trajectory_msgs.msg import JointTrajectory
from trajectory_msgs.msg import JointTrajectoryPoint


JOINT_HOME = [0.0, -1.603, 1.509, 0.0, 0.0, 0.0]
JOINT_PRE_APPROACH = [-0.714, -1.936, 2.156, -2.004, -1.528, 0.0]
JOINT_APPROACH = [-0.736, -2.208, 2.395, -2.276, -1.539, 1.460]
JOINT_INSERT = [-0.740, -1.720, 2.445, -2.378, -1.539, 1.460]

UR5E_JOINT_NAMES = [
    "shoulder_pan_joint",
    "shoulder_lift_joint",
    "elbow_joint",
    "wrist_1_joint",
    "wrist_2_joint",
    "wrist_3_joint",
]


class AssemblyDemo(Node):
    def __init__(self):
        super().__init__("assembly_demo")

        self.declare_parameter("joint_names", UR5E_JOINT_NAMES)
        self.declare_parameter("trajectory_topic", "/ur5e/joint_trajectory")
        self.declare_parameter("joint_state_topic", "/ur5e/joint_states_gz")
        self.declare_parameter("wrench_topic", "/ur5e/ft_sensor")
        self.declare_parameter("start_delay_sec", 8.0)
        self.declare_parameter("insert_force_limit_z_n", 50.0)
        self.declare_parameter("joint_position_tolerance_rad", 0.03)
        self.declare_parameter("waypoint_timeout_margin_sec", 2.0)
        self.declare_parameter("home_duration_sec", 3.0)
        self.declare_parameter("pre_approach_duration_sec", 3.0)
        self.declare_parameter("approach_duration_sec", 8.0)
        self.declare_parameter("insert_duration_sec", 18.0)
        self.declare_parameter("retract_duration_sec", 3.0)
        self.declare_parameter("home_return_duration_sec", 3.0)
        self.declare_parameter("home_settle_sec", 1.5)
        self.declare_parameter("pre_approach_settle_sec", 0.7)
        self.declare_parameter("approach_settle_sec", 1.0)
        self.declare_parameter("insert_settle_sec", 0.5)
        self.declare_parameter("retract_settle_sec", 0.7)
        self.declare_parameter("home_return_settle_sec", 0.7)

        self.joint_names = list(self.get_parameter("joint_names").value)
        self.trajectory_topic = self.get_parameter("trajectory_topic").value
        self.force_limit_z_n = float(self.get_parameter("insert_force_limit_z_n").value)
        self.joint_position_tolerance_rad = float(
            self.get_parameter("joint_position_tolerance_rad").value
        )
        self.waypoint_timeout_margin_sec = float(
            self.get_parameter("waypoint_timeout_margin_sec").value
        )

        self._validate_waypoints()

        self.traj_pub = self.create_publisher(JointTrajectory, self.trajectory_topic, 10)
        self.create_subscription(
            JointState,
            self.get_parameter("joint_state_topic").value,
            self._joint_state_cb,
            50,
        )
        self.create_subscription(
            Wrench,
            self.get_parameter("wrench_topic").value,
            self._wrench_cb,
            100,
        )

        self.waypoints = [
            {
                "name": "HOME",
                "positions": JOINT_HOME,
                "duration_sec": float(self.get_parameter("home_duration_sec").value),
                "settle_sec": float(self.get_parameter("home_settle_sec").value),
            },
            {
                "name": "PRE_APPROACH",
                "positions": JOINT_PRE_APPROACH,
                "duration_sec": float(
                    self.get_parameter("pre_approach_duration_sec").value
                ),
                "settle_sec": float(
                    self.get_parameter("pre_approach_settle_sec").value
                ),
            },
            {
                "name": "APPROACH",
                "positions": JOINT_APPROACH,
                "duration_sec": float(self.get_parameter("approach_duration_sec").value),
                "settle_sec": float(self.get_parameter("approach_settle_sec").value),
            },
            {
                "name": "INSERT",
                "positions": JOINT_INSERT,
                "duration_sec": float(self.get_parameter("insert_duration_sec").value),
                "settle_sec": float(self.get_parameter("insert_settle_sec").value),
            },
            {
                "name": "RETRACT",
                "positions": JOINT_APPROACH,
                "duration_sec": float(self.get_parameter("retract_duration_sec").value),
                "settle_sec": float(self.get_parameter("retract_settle_sec").value),
            },
            {
                "name": "PRE_APPROACH_RETURN",
                "positions": JOINT_PRE_APPROACH,
                "duration_sec": float(
                    self.get_parameter("pre_approach_duration_sec").value
                ),
                "settle_sec": float(
                    self.get_parameter("pre_approach_settle_sec").value
                ),
            },
            {
                "name": "HOME_RETURN",
                "positions": JOINT_HOME,
                "duration_sec": float(
                    self.get_parameter("home_return_duration_sec").value
                ),
                "settle_sec": float(
                    self.get_parameter("home_return_settle_sec").value
                ),
            },
        ]

        self.current_waypoint_index = 0
        self.current_waypoint_name = None
        self.current_joint_positions = {}
        self.phase_timer = None
        self.settle_timer = None
        self.started = False
        self.retract_requested = False
        self.completed = False

        delay = float(self.get_parameter("start_delay_sec").value)
        self.start_timer = self.create_timer(delay, self._start_once)

    def _validate_waypoints(self):
        waypoint_specs = {
            "JOINT_HOME": JOINT_HOME,
            "JOINT_PRE_APPROACH": JOINT_PRE_APPROACH,
            "JOINT_APPROACH": JOINT_APPROACH,
            "JOINT_INSERT": JOINT_INSERT,
        }

        for name, positions in waypoint_specs.items():
            if len(positions) != 6:
                raise ValueError(
                    f"{name} must contain exactly 6 joint angles, got {len(positions)}."
                )

    def _start_once(self):
        if self.started:
            return

        self.started = True
        self.start_timer.cancel()
        self.get_logger().info("Starting pure joint-space assembly FSM")
        self._execute_current_waypoint()

    def _joint_state_cb(self, msg: JointState):
        for name, pos in zip(msg.name, msg.position):
            if name in self.joint_names:
                self.current_joint_positions[name] = float(pos)

        if not self.started or self.completed or self.current_waypoint_name is None:
            return

        if not all(name in self.current_joint_positions for name in self.joint_names):
            return

        waypoint = self.waypoints[self.current_waypoint_index]
        errors = [
            abs(self.current_joint_positions[name] - target)
            for name, target in zip(self.joint_names, waypoint["positions"])
        ]
        within_tolerance = all(
            error <= self.joint_position_tolerance_rad for error in errors
        )

        if not within_tolerance:
            if self.settle_timer is not None:
                self.settle_timer.cancel()
                self.settle_timer = None
            return

        if self.settle_timer is None:
            settle_sec = float(waypoint["settle_sec"])
            self.get_logger().info(
                "Waypoint %s reached within %.3f rad, settling for %.2f s"
                % (
                    self.current_waypoint_name,
                    self.joint_position_tolerance_rad,
                    settle_sec,
                )
            )
            self.settle_timer = self.create_timer(settle_sec, self._settle_current_waypoint)

    def _wrench_cb(self, msg: Wrench):
        if self.current_waypoint_name != "INSERT":
            return

        if self.retract_requested or self.completed:
            return

        fz = float(msg.force.z)
        if abs(fz) <= self.force_limit_z_n:
            return

        self.retract_requested = True
        self.get_logger().error(
            "INSERT force trip: |Fz|=%.2f N exceeded %.2f N, switching to RETRACT"
            % (abs(fz), self.force_limit_z_n)
        )

        self._cancel_waypoint_timers()

        self.current_waypoint_index = self._waypoint_index("RETRACT")
        self._execute_current_waypoint()

    def _publish_waypoint(self, waypoint):
        msg = JointTrajectory()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.joint_names = self.joint_names

        point = JointTrajectoryPoint()
        point.positions = list(waypoint["positions"])
        duration_sec = float(waypoint["duration_sec"])
        point.time_from_start = Duration(
            sec=int(duration_sec),
            nanosec=int((duration_sec % 1.0) * 1e9),
        )
        msg.points = [point]
        self.traj_pub.publish(msg)

    def _waypoint_index(self, target_name):
        for index, waypoint in enumerate(self.waypoints):
            if waypoint["name"] == target_name:
                return index
        raise ValueError(f"Waypoint {target_name} not found")

    def _execute_current_waypoint(self):
        waypoint = self.waypoints[self.current_waypoint_index]
        self.current_waypoint_name = waypoint["name"]

        self.get_logger().info(f"FSM -> {self.current_waypoint_name}")
        self._cancel_waypoint_timers()
        self._publish_waypoint(waypoint)

        timeout_sec = (
            float(waypoint["duration_sec"])
            + float(waypoint["settle_sec"])
            + self.waypoint_timeout_margin_sec
        )
        self.phase_timer = self.create_timer(timeout_sec, self._waypoint_timeout_cb)

    def _cancel_waypoint_timers(self):
        if self.phase_timer is not None:
            self.phase_timer.cancel()
            self.phase_timer = None

        if self.settle_timer is not None:
            self.settle_timer.cancel()
            self.settle_timer = None

    def _settle_current_waypoint(self):
        if self.settle_timer is not None:
            self.settle_timer.cancel()
            self.settle_timer = None
        self._finish_current_waypoint()

    def _waypoint_timeout_cb(self):
        waypoint = self.waypoints[self.current_waypoint_index]
        self.get_logger().warning(
            "Timeout while waiting for %s joint-state convergence, advancing anyway"
            % waypoint["name"]
        )
        self._finish_current_waypoint()

    def _finish_current_waypoint(self):
        self._cancel_waypoint_timers()

        finished_waypoint = self.waypoints[self.current_waypoint_index]["name"]

        if finished_waypoint == "HOME_RETURN":
            self.completed = True
            if self.retract_requested:
                self.get_logger().warning("Assembly stopped by force limit and returned home")
            else:
                self.get_logger().info("Assembly FSM complete")
            return

        self.current_waypoint_index += 1
        if self.current_waypoint_index >= len(self.waypoints):
            self.completed = True
            self.get_logger().info("Assembly FSM complete")
            return

        self._execute_current_waypoint()


def main(args=None):
    rclpy.init(args=args)
    node = AssemblyDemo()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        if node.context.ok():
            node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()

    return 0


if __name__ == "__main__":
    sys.exit(main())
