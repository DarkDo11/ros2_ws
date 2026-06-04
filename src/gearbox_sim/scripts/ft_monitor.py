#!/usr/bin/env python3
"""Force-torque monitor for the gearbox assembly cell.

Subscribes to the three FT sensor topics that the ros_gz_bridge already
publishes and produces:
  - INFO-level log lines whenever |force| or |torque| crosses a threshold
    (rising edge only, to avoid log spam)
  - Per-arm summary topics: /<arm>/ft_summary  [Float64MultiArray]
    layout: [force_x, force_y, force_z, |force|, torque_x, torque_y, torque_z, |torque|]
"""
from __future__ import annotations

import math
from dataclasses import dataclass, field
from typing import Dict

import rclpy
from geometry_msgs.msg import Wrench
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray

_DEFAULT_FORCE_THRESHOLD_N = 5.0
_DEFAULT_TORQUE_THRESHOLD_NM = 1.0


@dataclass
class _ArmState:
    name: str
    force_above: bool = False
    torque_above: bool = False
    publisher: object = field(default=None, repr=False)


class FTMonitor(Node):
    """Monitor node for all three arm force-torque sensors."""

    _ARMS = ["ur5e_press", "ur5e_assembly", "ur3e_screw"]

    def __init__(self):
        super().__init__("ft_monitor")

        self.declare_parameter("force_threshold_n", _DEFAULT_FORCE_THRESHOLD_N)
        self.declare_parameter("torque_threshold_nm", _DEFAULT_TORQUE_THRESHOLD_NM)

        self._force_thr: float = (
            self.get_parameter("force_threshold_n").get_parameter_value().double_value
        )
        self._torque_thr: float = (
            self.get_parameter("torque_threshold_nm").get_parameter_value().double_value
        )

        self._states: Dict[str, _ArmState] = {}
        for arm in self._ARMS:
            state = _ArmState(name=arm)
            state.publisher = self.create_publisher(
                Float64MultiArray, f"/{arm}/ft_summary", 10
            )
            self._states[arm] = state
            self.create_subscription(
                Wrench,
                f"/{arm}/ft_sensor",
                lambda msg, a=arm: self._cb(a, msg),
                10,
            )

        self.get_logger().info(
            f"ft_monitor started — force_thr={self._force_thr:.2f} N  "
            f"torque_thr={self._torque_thr:.2f} N·m"
        )

    def _cb(self, arm: str, msg: Wrench) -> None:
        f = msg.force
        t = msg.torque
        f_mag = math.sqrt(f.x**2 + f.y**2 + f.z**2)
        t_mag = math.sqrt(t.x**2 + t.y**2 + t.z**2)

        state = self._states[arm]
        f_above = f_mag >= self._force_thr
        t_above = t_mag >= self._torque_thr

        if f_above and not state.force_above:
            self.get_logger().info(
                f"[{arm}] FORCE threshold crossed: |F|={f_mag:.3f} N "
                f"(fx={f.x:.3f} fy={f.y:.3f} fz={f.z:.3f})"
            )
        elif not f_above and state.force_above:
            self.get_logger().info(
                f"[{arm}] force returned below threshold: |F|={f_mag:.3f} N"
            )

        if t_above and not state.torque_above:
            self.get_logger().info(
                f"[{arm}] TORQUE threshold crossed: |T|={t_mag:.3f} N·m "
                f"(tx={t.x:.3f} ty={t.y:.3f} tz={t.z:.3f})"
            )
        elif not t_above and state.torque_above:
            self.get_logger().info(
                f"[{arm}] torque returned below threshold: |T|={t_mag:.3f} N·m"
            )

        state.force_above = f_above
        state.torque_above = t_above

        summary = Float64MultiArray()
        summary.data = [f.x, f.y, f.z, f_mag, t.x, t.y, t.z, t_mag]
        state.publisher.publish(summary)


def main():
    rclpy.init()
    node = FTMonitor()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
