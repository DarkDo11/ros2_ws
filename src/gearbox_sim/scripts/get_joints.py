#!/usr/bin/env python3
import sys

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState


UR5E_JOINT_NAMES = [
    "shoulder_pan_joint",
    "shoulder_lift_joint",
    "elbow_joint",
    "wrist_1_joint",
    "wrist_2_joint",
    "wrist_3_joint",
]


class JointPrinter(Node):
    def __init__(self):
        super().__init__("get_joints")

        self.declare_parameter("joint_state_topic", "/ur5e/joint_states_gz")
        self.current_joint_positions = {}
        self.done = False
        self.create_subscription(
            JointState,
            self.get_parameter("joint_state_topic").value,
            self._joint_state_cb,
            50,
        )

    def _joint_state_cb(self, msg: JointState):
        for name, pos in zip(msg.name, msg.position):
            if name in UR5E_JOINT_NAMES:
                self.current_joint_positions[name] = float(pos)

        if not all(name in self.current_joint_positions for name in UR5E_JOINT_NAMES):
            return

        joints = [self.current_joint_positions[name] for name in UR5E_JOINT_NAMES]
        print("[" + ", ".join(f"{value:.6f}" for value in joints) + "]", flush=True)
        self.done = True


def main(args=None):
    rclpy.init(args=args)
    node = JointPrinter()

    try:
        while rclpy.ok() and not node.done:
            rclpy.spin_once(node, timeout_sec=0.1)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()

    return 0


if __name__ == "__main__":
    sys.exit(main())
