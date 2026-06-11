#!/usr/bin/env python3
from __future__ import annotations

import subprocess
import threading
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Set

import rclpy
import yaml
from rclpy.node import Node
from tf2_ros import Buffer, TransformException, TransformListener

from gearbox_sim.srv import SetAttachment

_GZ_SET_POSE_SVC = "/world/assembly_world/set_pose"


@dataclass
class AttachmentState:
    robot_name: str
    tool_frame: str
    part_name: str
    part_frame: str
    part_link: str


def _gz_set_pose_bg(model_name: str, x: float, y: float, z: float,
                    qx: float = 0.0, qy: float = 0.0,
                    qz: float = 0.0, qw: float = 1.0) -> None:
    """Call gz service to move a model; runs in a daemon thread (non-blocking)."""
    req = (
        f'name: "{model_name}" '
        f'position: {{x: {x}, y: {y}, z: {z}}} '
        f'orientation: {{x: {qx}, y: {qy}, z: {qz}, w: {qw}}}'
    )
    subprocess.run(
        ["gz", "service", "-s", _GZ_SET_POSE_SVC,
         "--reqtype", "gz.msgs.Pose",
         "--reptype", "gz.msgs.Boolean",
         "--timeout", "800",
         "--req", req],
        capture_output=True,
    )


class GraspAttacher(Node):
    def __init__(self):
        super().__init__("grasp_attacher")
        default_config = (
            Path(__file__).resolve().parents[1] / "config" / "assembly_cell.yaml"
        )
        self.declare_parameter("config_file", str(default_config))
        self.declare_parameter("sync_entity_poses", False)

        config_file = self.get_parameter("config_file").get_parameter_value().string_value
        with Path(config_file).open("r", encoding="utf-8") as stream:
            self.config = yaml.safe_load(stream)

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self, spin_thread=True)
        self.attachments: Dict[str, AttachmentState] = {}
        # parts currently being moved (deduplicate in-flight gz calls)
        self._in_flight: Set[str] = set()
        self._thread_pool = ThreadPoolExecutor(max_workers=4)

        self.service = self.create_service(
            SetAttachment,
            self.config["services"]["attachment_service"],
            self._handle_attachment,
        )
        self.sync_entity_poses = (
            self.get_parameter("sync_entity_poses").get_parameter_value().bool_value
        )
        if self.sync_entity_poses:
            self.create_timer(0.05, self._sync_attached_entities)
            self.create_timer(0.15, self._sync_all_part_frames)

    def _handle_attachment(
        self,
        request: SetAttachment.Request,
        response: SetAttachment.Response,
    ):
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

    def _move_model(self, model_name: str, x: float, y: float, z: float,
                    qx: float = 0.0, qy: float = 0.0,
                    qz: float = 0.0, qw: float = 1.0) -> None:
        """Submit a task to move model_name; skips if already in-flight."""
        if model_name in self._in_flight:
            return
        self._in_flight.add(model_name)

        def _run():
            try:
                _gz_set_pose_bg(model_name, x, y, z, qx, qy, qz, qw)
            finally:
                self._in_flight.discard(model_name)

        self._thread_pool.submit(_run)

    def _sync_attached_entities(self):
        """Continuously move attached parts to follow the robot TCP (20 Hz)."""
        part_links = self.config.get("part_links", {})
        for attachment in list(self.attachments.values()):
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

            model_name = part_links.get(attachment.part_name, attachment.part_name)
            t = transform.transform
            self._move_model(
                model_name,
                t.translation.x, t.translation.y, t.translation.z,
                t.rotation.x, t.rotation.y, t.rotation.z, t.rotation.w,
            )

    def _sync_all_part_frames(self):
        """Move all unattached parts to their current TF frame positions (6.7 Hz)."""
        part_links = self.config.get("part_links", {})
        for part_name, model_name in part_links.items():
            if part_name in self.attachments:
                continue
            try:
                transform = self.tf_buffer.lookup_transform(
                    "world",
                    f"{part_name}_current_frame",
                    rclpy.time.Time(),
                    timeout=rclpy.duration.Duration(seconds=0.0),
                )
            except Exception:
                continue

            t = transform.transform
            self._move_model(
                model_name,
                t.translation.x, t.translation.y, t.translation.z,
                t.rotation.x, t.rotation.y, t.rotation.z, t.rotation.w,
            )


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
