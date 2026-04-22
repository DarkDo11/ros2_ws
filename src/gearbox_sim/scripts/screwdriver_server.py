#!/usr/bin/env python3
import time

import rclpy
from builtin_interfaces.msg import Duration
from rclpy.action import ActionServer
from rclpy.node import Node
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint

from gearbox_sim.action import RunScrewdriver


class ScrewdriverServer(Node):
    def __init__(self):
        super().__init__("screwdriver_server")
        self.declare_parameter("trajectory_topic", "/ur3e_screw_tool/joint_trajectory")
        self.declare_parameter("slide_joint_name", "ur3e_screw_screwdriver_slide_joint")
        self.publisher = self.create_publisher(
            JointTrajectory,
            self.get_parameter("trajectory_topic").get_parameter_value().string_value,
            10,
        )
        self.server = ActionServer(
            self,
            RunScrewdriver,
            "/ur3e_screw/run_screwdriver",
            execute_callback=self._execute_goal,
        )

    def _publish_cycle(self, depth: float, duration_sec: float):
        msg = JointTrajectory()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.joint_names = [
            self.get_parameter("slide_joint_name").get_parameter_value().string_value
        ]

        down = JointTrajectoryPoint()
        down.positions = [depth]
        down.time_from_start = Duration(sec=int(duration_sec), nanosec=int((duration_sec % 1.0) * 1e9))
        up = JointTrajectoryPoint()
        up.positions = [0.0]
        up.time_from_start = Duration(sec=int(duration_sec * 2.0), nanosec=int(((duration_sec * 2.0) % 1.0) * 1e9))
        msg.points = [down, up]
        self.publisher.publish(msg)

    def _execute_goal(self, goal_handle):
        goal = goal_handle.request
        self.get_logger().info(
            f"Screw cycle at {goal.screw_frame}, depth={goal.descend_depth_m:.4f}, spin={goal.spin_rps:.2f} rps"
        )
        self._publish_cycle(goal.descend_depth_m, goal.duration_sec)

        feedback = RunScrewdriver.Feedback()
        feedback.phase = "descending"
        feedback.progress = 0.25
        goal_handle.publish_feedback(feedback)
        time.sleep(goal.duration_sec)

        feedback.phase = "tightening"
        feedback.progress = 0.75
        goal_handle.publish_feedback(feedback)
        time.sleep(goal.duration_sec)

        goal_handle.succeed()
        result = RunScrewdriver.Result()
        result.success = True
        result.message = f"Screw cycle completed at {goal.screw_frame}"
        return result


def main():
    rclpy.init()
    node = ScrewdriverServer()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
