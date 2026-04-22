#!/usr/bin/env python3
import sys

import rclpy
from builtin_interfaces.msg import Duration
from rclpy.node import Node
from sensor_msgs.msg import JointState
from trajectory_msgs.msg import JointTrajectory
from trajectory_msgs.msg import JointTrajectoryPoint


class JointGuiTeleop(Node):
    def __init__(self):
        super().__init__("joint_gui_teleop")

        self.declare_parameter(
            "joint_names",
            [
                "shoulder_pan_joint",
                "shoulder_lift_joint",
                "elbow_joint",
                "wrist_1_joint",
                "wrist_2_joint",
                "wrist_3_joint",
            ],
        )
        self.declare_parameter("desired_joint_states_topic", "/joint_states")
        self.declare_parameter("trajectory_topic", "/ur5e/joint_trajectory")
        self.declare_parameter("command_duration_sec", 0.15)

        self.joint_names = list(self.get_parameter("joint_names").value)
        self.command_duration_sec = float(self.get_parameter("command_duration_sec").value)
        self.last_positions = None

        self.traj_pub = self.create_publisher(
            JointTrajectory,
            self.get_parameter("trajectory_topic").value,
            10,
        )
        self.create_subscription(
            JointState,
            self.get_parameter("desired_joint_states_topic").value,
            self._joint_state_cb,
            50,
        )

        self.get_logger().info(
            "Listening for GUI joint targets on %s"
            % self.get_parameter("desired_joint_states_topic").value
        )

    def _joint_state_cb(self, msg: JointState):
        positions_by_name = {
            name: float(position) for name, position in zip(msg.name, msg.position)
        }

        if not all(name in positions_by_name for name in self.joint_names):
            return

        positions = tuple(positions_by_name[name] for name in self.joint_names)
        if positions == self.last_positions:
            return

        self.last_positions = positions

        traj = JointTrajectory()
        traj.header.stamp = self.get_clock().now().to_msg()
        traj.joint_names = self.joint_names

        point = JointTrajectoryPoint()
        point.positions = list(positions)
        point.time_from_start = Duration(
            sec=int(self.command_duration_sec),
            nanosec=int((self.command_duration_sec % 1.0) * 1e9),
        )
        traj.points = [point]
        self.traj_pub.publish(traj)


def main(args=None):
    rclpy.init(args=args)
    node = JointGuiTeleop()

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
