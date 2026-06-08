#!/usr/bin/env python3
import csv
import os
import threading
import time
from pathlib import Path
from typing import List

import rclpy
from builtin_interfaces.msg import Duration
from geometry_msgs.msg import Wrench
from rclpy.callback_groups import MutuallyExclusiveCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint

from gearbox_sim.srv import RunPressCycle

_CSV_HEADER = [
    "timestamp_s", "recipe", "target_frame", "stroke_m",
    "peak_fz_n", "mean_fz_n", "sample_count",
]


class PressController(Node):
    def __init__(self):
        super().__init__("press_controller")
        self.declare_parameter("trajectory_topic", "/press/joint_trajectory")
        self.declare_parameter("joint_name", "press_ram_joint")
        self.declare_parameter("ft_topic", "/ur5e_press/ft_sensor")
        self.declare_parameter("demo_mode", True)
        self.declare_parameter("require_safety_interlock", False)
        self.declare_parameter("safety_interlock_closed", True)
        self.declare_parameter("fixture_ready", True)
        self.declare_parameter("require_ft_samples", False)
        self.declare_parameter(
            "csv_path",
            str(Path(os.environ.get("ROS_LOG_DIR", "/tmp")) / "press_ft_log.csv"),
        )

        self.publisher = self.create_publisher(
            JointTrajectory,
            self.get_parameter("trajectory_topic").get_parameter_value().string_value,
            10,
        )
        self.srv = self.create_service(
            RunPressCycle, "/press/run_cycle", self._handle_cycle
        )
        # FT subscriber — samples buffered during the capture window
        self._ft_samples: List[float] = []
        self._ft_capturing: bool = False
        self._ft_lock = threading.Lock()
        ft_topic = self.get_parameter("ft_topic").get_parameter_value().string_value
        # Own callback group so FT samples keep arriving while _handle_cycle
        # blocks on time.sleep() in the service callback (needs MultiThreadedExecutor).
        self._ft_group = MutuallyExclusiveCallbackGroup()
        self._ft_sub = self.create_subscription(
            Wrench, ft_topic, self._ft_callback, 20,
            callback_group=self._ft_group,
        )

        # CSV log — append-mode so successive runs accumulate
        csv_path = Path(
            self.get_parameter("csv_path").get_parameter_value().string_value
        )
        write_header = not csv_path.exists()
        self._csv_file = open(csv_path, "a", newline="", encoding="utf-8")  # noqa: SIM115
        self._csv_writer = csv.writer(self._csv_file)
        if write_header:
            self._csv_writer.writerow(_CSV_HEADER)
            self._csv_file.flush()
        self.get_logger().info(f"Press FT log: {csv_path}")
        if self._demo_mode:
            self.get_logger().warn(
                "press_controller demo_mode=true: press cycles may report success "
                "without certified safety input or F/T evidence."
            )
        else:
            self.get_logger().info(
                "press_controller demo_mode=false: safety interlock, fixture "
                "ready and F/T samples are required."
            )

    @property
    def _demo_mode(self) -> bool:
        return self.get_parameter("demo_mode").get_parameter_value().bool_value

    def _ft_callback(self, msg: Wrench) -> None:
        # list.append is GIL-safe; the lock guards only the start/end
        # of the capture window, not every sample.
        if self._ft_capturing:
            self._ft_samples.append(msg.force.z)

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
            f"Press cycle: recipe={request.recipe_name} "
            f"target={request.target_frame} stroke={request.stroke_m:.4f}"
        )

        demo_mode = self._demo_mode
        require_interlock = (
            (not demo_mode)
            or self.get_parameter("require_safety_interlock")
            .get_parameter_value()
            .bool_value
        )
        interlock_closed = (
            self.get_parameter("safety_interlock_closed").get_parameter_value().bool_value
        )
        fixture_ready = (
            self.get_parameter("fixture_ready").get_parameter_value().bool_value
        )
        if require_interlock and (not interlock_closed or not fixture_ready):
            response.success = False
            response.message = (
                "Press cycle blocked: safety interlock is open or fixture is not ready"
            )
            self.get_logger().error(response.message)
            return response

        # Open FT capture window before publishing so no samples are missed
        with self._ft_lock:
            self._ft_samples = []
        self._ft_capturing = True

        # Stroke: idle->down at t=0.5 s, hold until t=1.2 s, retract by t=2.2 s
        self._publish(joint_name, [0.0, request.stroke_m, 0.0], [0.5, 1.2, 2.2])
        time.sleep(2.2 + request.dwell_sec)

        # Close capture window
        self._ft_capturing = False
        with self._ft_lock:
            samples = list(self._ft_samples)

        if samples:
            # force.z is negative while ram pushes down (reaction on sensor)
            peak_fz = min(samples)   # most-negative = highest contact force
            mean_fz = sum(samples) / len(samples)
            self.get_logger().info(
                f"Press FT: recipe={request.recipe_name}  "
                f"peak_Fz={peak_fz:.1f} N  mean_Fz={mean_fz:.1f} N  "
                f"samples={len(samples)}"
            )
        else:
            peak_fz = 0.0
            mean_fz = 0.0
            self.get_logger().warn(
                "Press FT: no samples received — "
                "check that /ur5e_press/ft_sensor is publishing"
            )

        self._csv_writer.writerow([
            f"{time.time():.3f}", request.recipe_name, request.target_frame,
            f"{request.stroke_m:.4f}", f"{peak_fz:.2f}", f"{mean_fz:.2f}",
            len(samples),
        ])
        self._csv_file.flush()

        require_ft_samples = (
            (not demo_mode)
            or self.get_parameter("require_ft_samples").get_parameter_value().bool_value
        )
        if require_ft_samples and not samples:
            response.success = False
            response.message = "Press cycle failed: no F/T samples captured"
            return response

        response.success = True
        response.message = (
            f"Completed press recipe {request.recipe_name}  peak_Fz={peak_fz:.1f} N"
        )
        return response

    def destroy_node(self) -> None:
        self._csv_file.close()
        super().destroy_node()


def main():
    rclpy.init()
    node = PressController()
    executor = MultiThreadedExecutor()
    executor.add_node(node)
    try:
        executor.spin()
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
