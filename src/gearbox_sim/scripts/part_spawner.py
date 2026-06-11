#!/usr/bin/env python3
"""Spawn each gearbox part as a separate Gazebo model (kinematic, no gravity).

Each part is spawned as an independent model so that set_pose with type=MODEL
(type=2) works correctly, unlike fixed-joint links inside the main scene URDF.
"""
from __future__ import annotations

import subprocess
import time
from pathlib import Path

from ament_index_python.packages import PackageNotFoundError, get_package_share_directory
import rclpy
from rclpy.node import Node


# ---------------------------------------------------------------------------
# Part definitions
# ---------------------------------------------------------------------------
# Each entry: (model_name, stl_file, collision_type, collision_params,
#              r, g, b, x, y, z)
# collision_type: 'box' -> collision_params = 'sx sy sz'
#                 'cylinder' -> collision_params = {'r': float, 'l': float}
# ---------------------------------------------------------------------------
PARTS = [
    {
        "name": "lower_housing",
        "stl": "Front_box.STL",
        "collision": "box",
        "col_size": "0.050 0.050 0.030",
        "r": 0.22, "g": 0.24, "b": 0.28,
        "x": -1.26, "y": -0.24, "z": 0.96,
    },
    {
        "name": "main_bearing",
        "stl": "big_roller.STL",
        "collision": "cylinder",
        "col_radius": 0.020, "col_length": 0.014,
        "r": 0.78, "g": 0.80, "b": 0.82,
        "x": -1.26, "y": -0.30, "z": 0.97,
    },
    {
        "name": "cover",
        "stl": "Back_box.STL",
        "collision": "box",
        "col_size": "0.048 0.048 0.022",
        "r": 0.22, "g": 0.24, "b": 0.28,
        "x": -1.02, "y": -0.24, "z": 0.96,
    },
    {
        "name": "small_bearing",
        "stl": "Small_roller.STL",
        "collision": "cylinder",
        "col_radius": 0.015, "col_length": 0.010,
        "r": 0.78, "g": 0.80, "b": 0.82,
        "x": -1.02, "y": -0.30, "z": 0.97,
    },
    {
        "name": "housing",
        "stl": "Middle_box.STL",
        "collision": "box",
        "col_size": "0.056 0.056 0.040",
        "r": 0.22, "g": 0.24, "b": 0.28,
        "x": -0.78, "y": -0.24, "z": 0.96,
    },
    {
        "name": "ring_gear",
        "stl": "Spur_gear.STL",
        "collision": "cylinder",
        "col_radius": 0.021, "col_length": 0.010,
        "r": 0.10, "g": 0.23, "b": 0.75,
        "x": -0.78, "y": -0.30, "z": 0.97,
    },
    {
        "name": "planet_1",
        "stl": "satellite.STL",
        "collision": "cylinder",
        "col_radius": 0.008, "col_length": 0.010,
        "r": 0.84, "g": 0.67, "b": 0.18,
        "x": -0.16, "y": -0.10, "z": 0.95,
    },
    {
        "name": "planet_2",
        "stl": "satellite.STL",
        "collision": "cylinder",
        "col_radius": 0.008, "col_length": 0.010,
        "r": 0.84, "g": 0.67, "b": 0.18,
        "x": -0.16, "y": -0.15, "z": 0.95,
    },
    {
        "name": "planet_3",
        "stl": "satellite.STL",
        "collision": "cylinder",
        "col_radius": 0.008, "col_length": 0.010,
        "r": 0.84, "g": 0.67, "b": 0.18,
        "x": -0.16, "y": -0.20, "z": 0.95,
    },
    {
        "name": "sun_gear",
        "stl": "Sun_gear.STL",
        "collision": "cylinder",
        "col_radius": 0.010, "col_length": 0.018,
        "r": 0.25, "g": 0.56, "b": 0.29,
        "x": -0.085, "y": -0.12, "z": 0.95,
    },
    {
        "name": "carrier",
        "stl": "Vodilo.STL",
        "collision": "cylinder",
        "col_radius": 0.018, "col_length": 0.014,
        "r": 0.10, "g": 0.23, "b": 0.75,
        "x": -0.085, "y": -0.18, "z": 0.95,
    },
]

def _mesh_base() -> str:
    try:
        return str(Path(get_package_share_directory("gearbox_sim")) / "meshes" / "nema17")
    except PackageNotFoundError:
        return str(Path(__file__).resolve().parents[1] / "meshes" / "nema17")


MESH_BASE = _mesh_base()
CREATE_SERVICE = "/world/assembly_world/create"

def _build_collision(part: dict) -> str:
    if part["collision"] == "box":
        return f"<box><size>{part['col_size']}</size></box>"
    else:
        r = part["col_radius"]
        length = part["col_length"]
        return f"<cylinder><radius>{r}</radius><length>{length}</length></cylinder>"


def _build_visual_geom(part: dict) -> str:
    """Return the SDF <geometry> block for the visual element.

    Parts with ``stl=None`` use a primitive shape instead of a mesh.
    """
    if part.get("stl") is None:
        # Use the same primitive as the collision geometry for visual.
        if part["collision"] == "cylinder":
            r = part["col_radius"]
            length = part["col_length"]
            return f"<cylinder><radius>{r}</radius><length>{length}</length></cylinder>"
        else:
            return f"<box><size>{part['col_size']}</size></box>"
    stl = part["stl"]
    return (
        f'<mesh>'
        f'<uri>file://{MESH_BASE}/{stl}</uri>'
        f'<scale>0.001 0.001 0.001</scale>'
        f'</mesh>'
    )


def _build_sdf(part: dict) -> str:
    name = part["name"]
    r, g, b = part["r"], part["g"], part["b"]
    x, y, z = part["x"], part["y"], part["z"]
    collision_geom = _build_collision(part)
    visual_geom = _build_visual_geom(part)

    return (
        f'<sdf version="1.9">'
        f'<model name="{name}">'
        f'<static>false</static>'
        f'<link name="base_link">'
        f'<inertial>'
        f'<mass>0.1</mass>'
        f'<inertia><ixx>0.0001</ixx><ixy>0</ixy><ixz>0</ixz>'
        f'<iyy>0.0001</iyy><iyz>0</iyz><izz>0.0001</izz></inertia>'
        f'</inertial>'
        f'<gravity>false</gravity>'
        f'<visual name="vis">'
        f'<geometry>'
        f'{visual_geom}'
        f'</geometry>'
        f'<material>'
        f'<ambient>{r} {g} {b} 1.0</ambient>'
        f'<diffuse>{r} {g} {b} 1.0</diffuse>'
        f'</material>'
        f'</visual>'
        f'<collision name="col">'
        f'<geometry>{collision_geom}</geometry>'
        f'</collision>'
        f'</link>'
        f'<pose>{x} {y} {z} 0 0 0</pose>'
        f'</model>'
        f'</sdf>'
    )


def _spawn_sdf(node: Node, name: str, sdf: str) -> bool:
    # Escape backslashes and double-quotes for the gz service --req string
    sdf_escaped = sdf.replace("\\", "\\\\").replace('"', '\\"')

    req_str = f'sdf: "{sdf_escaped}"'

    cmd = [
        "gz", "service",
        "-s", CREATE_SERVICE,
        "--reqtype", "gz.msgs.EntityFactory",
        "--reptype", "gz.msgs.Boolean",
        "--timeout", "5000",
        "--req", req_str,
    ]

    node.get_logger().info(f"Spawning model: {name}")
    try:
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=10)
        if result.returncode == 0:
            node.get_logger().info(f"Spawned {name}: {result.stdout.strip()}")
            return True
        else:
            node.get_logger().error(
                f"Failed to spawn {name}: {result.stderr.strip()}"
            )
            return False
    except subprocess.TimeoutExpired:
        node.get_logger().error(f"Timeout spawning {name}")
        return False
    except Exception as exc:
        node.get_logger().error(f"Exception spawning {name}: {exc}")
        return False


def _spawn_part(node: Node, part: dict) -> bool:
    return _spawn_sdf(node, part["name"], _build_sdf(part))


class PartSpawner(Node):
    def __init__(self):
        super().__init__("part_spawner")
        # use_sim_time is auto-declared by rclpy; only declare if not already present
        if not self.has_parameter("use_sim_time"):
            self.declare_parameter("use_sim_time", True)

    def wait_for_gazebo(self, timeout_sec: float = 60.0) -> bool:
        """Wait until the /world/assembly_world/create gz service is available."""
        self.get_logger().info(
            f"Waiting for Gazebo service {CREATE_SERVICE} ..."
        )
        deadline = time.time() + timeout_sec
        while time.time() < deadline:
            check = subprocess.run(
                ["gz", "service", "--list"],
                capture_output=True, text=True, timeout=5,
            )
            if CREATE_SERVICE in check.stdout:
                self.get_logger().info("Gazebo service is ready.")
                return True
            time.sleep(1.0)
        self.get_logger().error(
            f"Gazebo service {CREATE_SERVICE} not found within {timeout_sec}s"
        )
        return False

    def spawn_all(self):
        if not self.wait_for_gazebo():
            return

        for part in PARTS:
            _spawn_part(self, part)
            time.sleep(0.5)

        self.get_logger().info("All parts spawned.")


def main():
    rclpy.init()
    node = PartSpawner()
    try:
        node.spawn_all()
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
