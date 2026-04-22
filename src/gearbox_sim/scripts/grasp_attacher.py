#!/usr/bin/env python3
from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Optional

import rclpy
import yaml
from geometry_msgs.msg import Pose
from rclpy.node import Node
from ros_gz_interfaces.msg import Entity
from ros_gz_interfaces.srv import SetEntityPose
from tf2_ros import Buffer, TransformException, TransformListener

from gearbox_sim.srv import SetAttachment


@dataclass
class AttachmentState:
    robot_name: str
    tool_frame: str
    part_name: str
    part_frame: str
    part_link: str


class GraspAttacher(Node):
    def __init__(self):
        super().__init__("grasp_attacher")
        default_config = (
            Path(__file__).resolve().parents[1] / "config" / "assembly_cell.yaml"
        )
        self.declare_parameter("config_file", str(default_config))
        self.declare_parameter("set_pose_service", "/world/assembly_world/set_pose")
        self.declare_parameter("entity_prefix", "gearbox_assembly_cell::")
        self.declare_parameter("sync_entity_poses", False)

        config_file = self.get_parameter("config_file").get_parameter_value().string_value
        with Path(config_file).open("r", encoding="utf-8") as stream:
            self.config = yaml.safe_load(stream)

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self, spin_thread=True)
        self.attachments: Dict[str, AttachmentState] = {}

        self.service = self.create_service(
            SetAttachment,
            self.config["services"]["attachment_service"],
            self._handle_attachment,
        )
        self.sync_entity_poses = (
            self.get_parameter("sync_entity_poses").get_parameter_value().bool_value
        )
        self.entity_prefix = (
            self.get_parameter("entity_prefix").get_parameter_value().string_value
        )
        self.set_pose_client: Optional[rclpy.client.Client] = None
        if self.sync_entity_poses:
            service_name = (
                self.get_parameter("set_pose_service").get_parameter_value().string_value
            )
            self.set_pose_client = self.create_client(SetEntityPose, service_name)
            self.create_timer(0.05, self._sync_attached_entities)

    def _handle_attachment(self, request: SetAttachment.Request, response: SetAttachment.Response):
        if request.attach:
            self.attachments[request.part_name] = AttachmentState(
                robot_name=request.robot_name,
                tool_frame=request.tool_frame,
                part_name=request.part_name,
                part_frame=request.part_frame,
                part_link=request.part_link,
            )
            response.success = True
            response.message = (
                f"Logical fixed joint engaged: {request.tool_frame} -> {request.part_link}"
            )
            self.get_logger().info(response.message)
            return response

        self.attachments.pop(request.part_name, None)
        response.success = True
        response.message = f"Logical fixed joint released for {request.part_link}"
        self.get_logger().info(response.message)
        return response

    def _sync_attached_entities(self):
        if self.set_pose_client is None:
            return
        if not self.set_pose_client.service_is_ready():
            self.set_pose_client.wait_for_service(timeout_sec=0.0)
            if not self.set_pose_client.service_is_ready():
                return

        for attachment in self.attachments.values():
            try:
                transform = self.tf_buffer.lookup_transform(
                    "world",
                    attachment.tool_frame,
                    rclpy.time.Time(),
                )
            except TransformException as exc:
                self.get_logger().warn(
                    f"Unable to sync attached part {attachment.part_name}: {exc}"
                )
                continue

            request = SetEntityPose.Request()
            request.entity = Entity(
                name=f"{self.entity_prefix}{attachment.part_link}",
                type=Entity.LINK,
            )
            request.pose = Pose()
            request.pose.position.x = transform.transform.translation.x
            request.pose.position.y = transform.transform.translation.y
            request.pose.position.z = transform.transform.translation.z
            request.pose.orientation = transform.transform.rotation
            self.set_pose_client.call_async(request)


def main():
    rclpy.init()
    node = GraspAttacher()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
