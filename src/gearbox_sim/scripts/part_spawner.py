#!/usr/bin/env python3
"""Spawn each gearbox part as a separate Gazebo model (kinematic, no gravity).

Each part is spawned as an independent model so that set_pose with type=MODEL
(type=2) works correctly, unlike fixed-joint links inside the main scene URDF.
"""
from __future__ import annotations

import subprocess
import time

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
        "x": -1.26, "y": -0.24, "z": 0.915,
    },
    {
        "name": "main_bearing",
        "stl": "big_roller.STL",
        "collision": "cylinder",
        "col_radius": 0.020, "col_length": 0.014,
        "r": 0.78, "g": 0.80, "b": 0.82,
        "x": -1.26, "y": -0.30, "z": 0.907,
    },
    {
        "name": "cover",
        "stl": "Back_box.STL",
        "collision": "box",
        "col_size": "0.048 0.048 0.022",
        "r": 0.22, "g": 0.24, "b": 0.28,
        "x": -1.02, "y": -0.24, "z": 0.911,
    },
    {
        "name": "small_bearing",
        "stl": "Small_roller.STL",
        "collision": "cylinder",
        "col_radius": 0.015, "col_length": 0.010,
        "r": 0.78, "g": 0.80, "b": 0.82,
        "x": -1.02, "y": -0.30, "z": 0.905,
    },
    {
        "name": "housing",
        "stl": "Middle_box.STL",
        "collision": "box",
        "col_size": "0.056 0.056 0.040",
        "r": 0.22, "g": 0.24, "b": 0.28,
        "x": -0.78, "y": -0.24, "z": 0.920,
    },
    {
        "name": "ring_gear",
        "stl": "Spur_gear.STL",
        "collision": "cylinder",
        "col_radius": 0.021, "col_length": 0.010,
        "r": 0.10, "g": 0.23, "b": 0.75,
        "x": -0.78, "y": -0.30, "z": 0.905,
    },
    {
        "name": "planet_1",
        "stl": "satellite.STL",
        "collision": "cylinder",
        "col_radius": 0.008, "col_length": 0.010,
        "r": 0.84, "g": 0.67, "b": 0.18,
        "x": -0.16, "y": -0.10, "z": 0.905,
    },
    {
        "name": "planet_2",
        "stl": "satellite.STL",
        "collision": "cylinder",
        "col_radius": 0.008, "col_length": 0.010,
        "r": 0.84, "g": 0.67, "b": 0.18,
        "x": -0.16, "y": -0.15, "z": 0.905,
    },
    {
        "name": "planet_3",
        "stl": "satellite.STL",
        "collision": "cylinder",
        "col_radius": 0.008, "col_length": 0.010,
        "r": 0.84, "g": 0.67, "b": 0.18,
        "x": -0.16, "y": -0.20, "z": 0.905,
    },
    {
        "name": "sun_gear",
        "stl": "Sun_gear.STL",
        "collision": "cylinder",
        "col_radius": 0.010, "col_length": 0.018,
        "r": 0.25, "g": 0.56, "b": 0.29,
        "x": -0.085, "y": -0.12, "z": 0.909,
    },
    {
        "name": "carrier",
        "stl": "Vodilo.STL",
        "collision": "cylinder",
        "col_radius": 0.018, "col_length": 0.014,
        "r": 0.10, "g": 0.23, "b": 0.75,
        "x": -0.085, "y": -0.18, "z": 0.907,
    },
]

MESH_BASE = "/home/dark/ros2_ws/install/gearbox_sim/share/gearbox_sim/meshes/nema17"
CREATE_SERVICE = "/world/assembly_world/create"

# ---------------------------------------------------------------------------
# Composite assembled gearbox
# ---------------------------------------------------------------------------
# The finished product is built from the three real NEMA17 box meshes stacked
# along Z into a motor-reducer (see reference photo Untitled 2.JPG): a black
# anodized base, an aluminium body, a bright machined face, and a steel output
# shaft.  Each box mesh is 62x62 mm and thin along its local Y axis, so a +90 deg
# roll about X lays the thin axis vertical and the 62x62 face becomes the
# horizontal footprint.  Spawned below ground; revealed on the assembly table by
# assembly_fsm once the cell finishes its work.
ASSEMBLED_GEARBOX_NAME = "assembled_gearbox"
_GEARBOX_BOXES = [
    # name,    mesh,            z_pose,  (r, g, b)
    ("back",   "Back_box.STL",   0.004, (0.07, 0.07, 0.09)),   # black anodized base
    ("middle", "Middle_box.STL", 0.014, (0.58, 0.60, 0.63)),   # aluminium body
    ("front",  "Front_box.STL",  0.025, (0.71, 0.73, 0.76)),   # bright machined face
]
_GEARBOX_SHAFT = {"z": 0.048, "r": 0.006, "l": 0.024, "rgb": (0.76, 0.78, 0.81)}


def _build_assembled_gearbox_sdf() -> str:
    visuals = []
    for name, mesh, z, (r, g, b) in _GEARBOX_BOXES:
        visuals.append(
            f'<visual name="{name}">'
            f'<pose>0 0 {z} 1.5708 0 0</pose>'
            f'<geometry><mesh><uri>file://{MESH_BASE}/{mesh}</uri>'
            f'<scale>0.001 0.001 0.001</scale></mesh></geometry>'
            f'<material><ambient>{r} {g} {b} 1</ambient>'
            f'<diffuse>{r} {g} {b} 1</diffuse>'
            f'<specular>0.3 0.3 0.3 1</specular></material>'
            f'</visual>'
        )
    sr, sg, sb = _GEARBOX_SHAFT["rgb"]
    visuals.append(
        f'<visual name="shaft">'
        f'<pose>0 0 {_GEARBOX_SHAFT["z"]} 0 0 0</pose>'
        f'<geometry><cylinder><radius>{_GEARBOX_SHAFT["r"]}</radius>'
        f'<length>{_GEARBOX_SHAFT["l"]}</length></cylinder></geometry>'
        f'<material><ambient>{sr} {sg} {sb} 1</ambient>'
        f'<diffuse>{sr} {sg} {sb} 1</diffuse>'
        f'<specular>0.6 0.6 0.6 1</specular></material>'
        f'</visual>'
    )
    return (
        '<sdf version="1.9">'
        f'<model name="{ASSEMBLED_GEARBOX_NAME}">'
        # Static: the finished gearbox is a final visual result positioned only
        # via set_pose at UNLOAD. A non-static kinematic link integrates any
        # residual velocity (e.g. from parts teleporting through it during the
        # hide step) and drifts across the world; static removes it from
        # dynamics entirely so it stays exactly where set_pose puts it.
        '<static>true</static>'
        '<link name="base_link">'
        '<inertial><mass>0.3</mass>'
        '<inertia><ixx>0.0005</ixx><ixy>0</ixy><ixz>0</ixz>'
        '<iyy>0.0005</iyy><iyz>0</iyz><izz>0.0005</izz></inertia></inertial>'
        f'{"".join(visuals)}'
        '<collision name="col"><pose>0 0 0.018 0 0 0</pose>'
        '<geometry><box><size>0.062 0.062 0.037</size></box></geometry></collision>'
        '</link>'
        '<pose>0 0 -1 0 0 0</pose>'
        '</model></sdf>'
    )


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
        f'<kinematic>true</kinematic>'
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


def _model_exists(name: str) -> bool:
    """Return True if a model with this name is present in the world.

    The /create service returns data:true even when Gazebo rejects the SDF, so
    callers must verify the entity actually exists rather than trust the reply.
    """
    try:
        result = subprocess.run(
            ["gz", "model", "-m", name, "-p"],
            capture_output=True, text=True, timeout=8,
        )
    except Exception:
        return False
    out = (result.stdout or "") + (result.stderr or "")
    return ("No model named" not in out) and (f"Name: {name}" in out or "Pose" in out)


def _spawn_sdf_verified(node: Node, name: str, sdf: str, retries: int = 4) -> bool:
    """Spawn an SDF model and confirm the entity was actually created.

    Gazebo can transiently reject a (valid) SDF string when it is busy, while the
    /create service still reports success, so we re-submit until the model is
    really present.
    """
    for attempt in range(1, retries + 1):
        _spawn_sdf(node, name, sdf)
        time.sleep(1.0)
        if _model_exists(name):
            node.get_logger().info(f"Verified {name} present (attempt {attempt}).")
            return True
        node.get_logger().warn(
            f"{name} not present after attempt {attempt}/{retries}; retrying."
        )
        time.sleep(1.0)
    node.get_logger().error(f"Failed to create {name} after {retries} attempts.")
    return False


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

        # Spawn the composite finished gearbox FIRST, while Gazebo is still idle
        # (its multi-mesh SDF is the one most prone to transient rejection when
        # the engine is busy).  Verify-and-retry guards against that.  It lives
        # below ground until assembly_fsm reveals it on the assembly table.
        _spawn_sdf_verified(
            self, ASSEMBLED_GEARBOX_NAME, _build_assembled_gearbox_sdf()
        )
        time.sleep(1.0)

        for part in PARTS:
            _spawn_part(self, part)
            time.sleep(2.0)

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
