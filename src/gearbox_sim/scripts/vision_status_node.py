#!/usr/bin/env python3
from __future__ import annotations

import json
from pathlib import Path
from typing import Dict

import rclpy
import yaml
from ament_index_python.packages import PackageNotFoundError, get_package_share_directory
from geometry_msgs.msg import PoseStamped, TransformStamped
from rclpy.duration import Duration
from rclpy.node import Node
from std_msgs.msg import String
from tf2_ros import Buffer, TransformBroadcaster, TransformException, TransformListener


def _default_config_path() -> str:
    try:
        return str(Path(get_package_share_directory("gearbox_sim")) / "config" / "assembly_cell.yaml")
    except PackageNotFoundError:
        return str(Path(__file__).resolve().parents[1] / "config" / "assembly_cell.yaml")


class VisionStatusNode(Node):
    """Minimal perception surrogate for the assembly FSM.

    This node does not run image processing. It turns current part TF frames
    into perception-shaped outputs: part pose topics, detected TF frames, and a
    compact JSON status topic that can gate FSM transitions.
    """

    def __init__(self) -> None:
        super().__init__("vision_status_node")
        self.declare_parameter("config_file", _default_config_path())
        self.declare_parameter("reference_frame", "world")
        self.declare_parameter("status_topic", "/vision/part_status")
        self.declare_parameter("publish_rate_hz", 2.0)
        self.declare_parameter("lookup_timeout_sec", 0.05)
        self.declare_parameter("demo_mode", True)

        self.config_file = self.get_parameter("config_file").get_parameter_value().string_value
        self.reference_frame = (
            self.get_parameter("reference_frame").get_parameter_value().string_value
        )
        self.lookup_timeout_sec = (
            self.get_parameter("lookup_timeout_sec").get_parameter_value().double_value
        )
        publish_rate_hz = max(
            0.1,
            self.get_parameter("publish_rate_hz").get_parameter_value().double_value,
        )

        with Path(self.config_file).open("r", encoding="utf-8") as stream:
            self.config = yaml.safe_load(stream)

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self, spin_thread=True)
        self.tf_broadcaster = TransformBroadcaster(self)
        self.status_pub = self.create_publisher(
            String,
            self.get_parameter("status_topic").get_parameter_value().string_value,
            10,
        )
        self.pose_pubs: Dict[str, object] = {
            part_name: self.create_publisher(
                PoseStamped,
                f"/vision/part_pose/{part_name}",
                10,
            )
            for part_name in self.config.get("parts", {})
        }

        if self.get_parameter("demo_mode").get_parameter_value().bool_value:
            self.get_logger().warn(
                "vision_status_node demo_mode=true: statuses are generated from "
                "current part TF frames, not image detection."
            )

        self.create_timer(1.0 / publish_rate_hz, self._publish_statuses)

    def _publish_statuses(self) -> None:
        for part_name in self.config.get("parts", {}):
            self._publish_part_status(part_name)

    def _publish_part_status(self, part_name: str) -> None:
        source_frame = f"{part_name}_current_frame"
        nominal_frame = self.config.get("parts", {}).get(part_name, "")
        detected_frame = f"vision_{part_name}_pose_frame"
        stamp = self.get_clock().now().to_msg()
        status = {
            "part_name": part_name,
            "type_id": part_name,
            "source_frame": source_frame,
            "nominal_frame": nominal_frame,
            "detected_frame": detected_frame,
            "accepted": False,
            "installing": False,
            "teeth_aligned": False,
            "done": False,
        }

        try:
            transform = self.tf_buffer.lookup_transform(
                self.reference_frame,
                source_frame,
                rclpy.time.Time(),
                timeout=Duration(seconds=self.lookup_timeout_sec),
            )
        except TransformException as exc:
            status["message"] = str(exc)
            self._publish_status(status)
            return

        z = float(transform.transform.translation.z)
        if z < -1.0:
            status["message"] = (
                f"{source_frame} is outside the visible workspace "
                f"(z={z:.3f}); rejecting"
            )
            self._publish_status(status)
            return

        status["accepted"] = True
        status["teeth_aligned"] = True
        status["message"] = "pose accepted from current part TF"

        detected_tf = TransformStamped()
        detected_tf.header.stamp = stamp
        detected_tf.header.frame_id = self.reference_frame
        detected_tf.child_frame_id = detected_frame
        detected_tf.transform = transform.transform
        self.tf_broadcaster.sendTransform(detected_tf)

        pose = PoseStamped()
        pose.header.stamp = stamp
        pose.header.frame_id = self.reference_frame
        pose.pose.position.x = transform.transform.translation.x
        pose.pose.position.y = transform.transform.translation.y
        pose.pose.position.z = transform.transform.translation.z
        pose.pose.orientation = transform.transform.rotation
        self.pose_pubs[part_name].publish(pose)
        self._publish_status(status)

    def _publish_status(self, status: Dict[str, object]) -> None:
        status["stamp_sec"] = (
            self.get_clock().now().nanoseconds / 1_000_000_000
        )
        msg = String()
        msg.data = json.dumps(status, sort_keys=True)
        self.status_pub.publish(msg)


def main() -> None:
    rclpy.init()
    node = VisionStatusNode()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
