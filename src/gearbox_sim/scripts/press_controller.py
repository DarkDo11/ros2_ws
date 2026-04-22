#!/usr/bin/env python3
import time

import rclpy
from builtin_interfaces.msg import Duration
from rclpy.node import Node
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint

from gearbox_sim.srv import RunPressCycle


class PressController(Node):
    def __init__(self):
        super().__init__("press_controller")
        self.declare_parameter("trajectory_topic", "/press/joint_trajectory")
        self.declare_parameter("joint_name", "press_ram_joint")
        self.publisher = self.create_publisher(
            JointTrajectory,
            self.get_parameter("trajectory_topic").get_parameter_value().string_value,
            10,
        )
        self.srv = self.create_service(RunPressCycle, "/press/run_cycle", self._handle_cycle)

    def _publish(self, joint_name: str, positions, durations):
        msg = JointTrajectory()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.joint_names = [joint_name]
        for position, duration_sec in zip(positions, durations):
            point = JointTrajectoryPoint()
            point.positions = [position]
            sec = int(duration_sec)
            point.time_from_start = Duration(
                sec=sec,
                nanosec=int((duration_sec - sec) * 1e9),
            )
            msg.points.append(point)
        self.publisher.publish(msg)

    def _handle_cycle(self, request, response):
        joint_name = self.get_parameter("joint_name").get_parameter_value().string_value
        self.get_logger().info(
            f"Press cycle: recipe={request.recipe_name} target={request.target_frame} stroke={request.stroke_m:.4f}"
        )
        self._publish(joint_name, [0.0, request.stroke_m, 0.0], [0.5, 1.2, 2.2])
        time.sleep(2.2 + request.dwell_sec)
        response.success = True
        response.message = f"Completed press recipe {request.recipe_name}"
        return response


def main():
    rclpy.init()
    node = PressController()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
