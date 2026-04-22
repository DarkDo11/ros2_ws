import os
import subprocess
import tempfile
import xml.etree.ElementTree as ET

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription
from launch.actions import OpaqueFunction
from launch.actions import SetEnvironmentVariable
from launch.actions import TimerAction
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PythonExpression
from launch.substitutions import Command
from launch.substitutions import FindExecutable
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def _strip_mesh_collisions_for_dart(urdf_path):
    tree = ET.parse(urdf_path)
    root = tree.getroot()

    collisionless_links = {
        "forearm_link",
        "wrist_1_link",
        "wrist_2_link",
        "wrist_3_link",
    }

    for link in root.findall("link"):
        if link.get("name") not in collisionless_links:
            continue
        for collision in list(link.findall("collision")):
            link.remove(collision)

    tree.write(urdf_path, encoding="utf-8", xml_declaration=True)


def _generate_temp_models(context):
    pkg_share = get_package_share_directory("gearbox_sim")
    xacro_exec = FindExecutable(name="xacro").perform(context)
    gear_mesh_scale = "0.002"
    demo_sun_mount_z = "0.135"

    out_dir = tempfile.mkdtemp(prefix="gearbox_sim_")

    model_specs = [
        (
            os.path.join(pkg_share, "urdf", "ur5e_robotiq_ft.urdf.xacro"),
            os.path.join(out_dir, "ur5e_cell_sim.urdf"),
            [
                "name:=ur5e_cell",
                "fixed_base:=true",
                "trajectory_topic:=/ur5e/joint_trajectory",
                "joint_state_topic:=/ur5e/joint_states_gz",
                "ft_topic:=/ur5e/ft_sensor",
                "use_simple_gripper:=true",
                "mount_demo_sun:=true",
                f"demo_sun_mesh_scale:={gear_mesh_scale}",
                f"demo_sun_mount_z:={demo_sun_mount_z}",
                "base_xyz:=0 0 0",
                "base_rpy:=0 0 0",
            ],
        ),
        (
            os.path.join(pkg_share, "urdf", "gearbox_gazebo.urdf.xacro"),
            os.path.join(out_dir, "gearbox_base.urdf"),
            [
                "name:=gearbox_base",
                "variant:=base",
                f"mesh_scale:={gear_mesh_scale}",
                "include_planets_in_base:=true",
                "include_carrier_in_base:=false",
            ],
        ),
        (
            os.path.join(pkg_share, "urdf", "gearbox_gazebo.urdf.xacro"),
            os.path.join(out_dir, "carrier.urdf"),
            ["name:=carrier", "variant:=carrier", f"mesh_scale:={gear_mesh_scale}"],
        ),
    ]

    for xacro_file, output_file, args in model_specs:
        with open(output_file, "w", encoding="utf-8") as stream:
            subprocess.run([xacro_exec, xacro_file, *args], check=True, stdout=stream)
        if output_file.endswith("ur5e_cell_sim.urdf"):
            _strip_mesh_collisions_for_dart(output_file)

    context.launch_configurations["generated_robot_urdf"] = os.path.join(out_dir, "ur5e_cell_sim.urdf")
    context.launch_configurations["generated_gearbox_base_urdf"] = os.path.join(out_dir, "gearbox_base.urdf")
    context.launch_configurations["generated_carrier_urdf"] = os.path.join(out_dir, "carrier.urdf")
    return []


def generate_launch_description():
    pkg_share = get_package_share_directory("gearbox_sim")
    ros_gz_sim_share = get_package_share_directory("ros_gz_sim")

    world = LaunchConfiguration("world")
    use_sim_time = LaunchConfiguration("use_sim_time")
    run_demo = LaunchConfiguration("run_demo")
    gui_teleop = LaunchConfiguration("gui_teleop")
    calibration_mode = LaunchConfiguration("calibration_mode")

    world_file = os.path.join(pkg_share, "worlds", "assembly_scene.sdf")
    calibration_world_file = os.path.join(
        pkg_share, "worlds", "assembly_scene_calibration.sdf"
    )
    robot_xacro = os.path.join(pkg_share, "urdf", "ur5e_robotiq_ft.urdf.xacro")
    gear_mesh_scale = "0.002"
    demo_sun_mount_z = "0.135"
    selected_world = PythonExpression(
        ["'", calibration_world_file, "' if '", calibration_mode, "' == 'true' else '", world, "'"]
    )

    robot_description = Command(
        [
            FindExecutable(name="xacro"),
            " ",
            robot_xacro,
            " ",
            "name:=ur5e_cell ",
            "fixed_base:=false ",
            "trajectory_topic:=/ur5e/joint_trajectory ",
            "joint_state_topic:=/ur5e/joint_states_gz ",
            "ft_topic:=/ur5e/ft_sensor ",
            "use_simple_gripper:=true ",
            "mount_demo_sun:=true ",
            f"demo_sun_mesh_scale:={gear_mesh_scale} ",
            f"demo_sun_mount_z:={demo_sun_mount_z} ",
        ]
    )

    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="screen",
        remappings=[("/joint_states", "/ur5e/joint_states_gz")],
        parameters=[
            {
                "use_sim_time": use_sim_time,
                "robot_description": robot_description,
            }
        ],
    )

    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(ros_gz_sim_share, "launch", "gz_sim.launch.py")
        ),
        launch_arguments={"gz_args": ["-r -v 4 ", selected_world]}.items(),
    )

    spawn_service_bridge = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        output="screen",
        arguments=["/world/assembly_world/create@ros_gz_interfaces/srv/SpawnEntity"],
    )

    topic_bridge = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        output="screen",
        arguments=[
            "/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock",
            "/ur5e/joint_states_gz@sensor_msgs/msg/JointState[gz.msgs.Model",
            "/ur5e/ft_sensor@geometry_msgs/msg/Wrench[gz.msgs.Wrench",
            "/ur5e/joint_trajectory@trajectory_msgs/msg/JointTrajectory]gz.msgs.JointTrajectory",
        ],
    )

    spawn_robot = Node(
        package="ros_gz_sim",
        executable="create",
        output="screen",
        arguments=[
            "-world",
            "assembly_world",
            "-name",
            "ur5e_cell",
            "-file",
            LaunchConfiguration("generated_robot_urdf"),
            "-x",
            "-0.45",
            "-y",
            "0.0",
            "-z",
            "0.77",
            "-R",
            "0.0",
            "-P",
            "0.0",
            "-Y",
            "1.5708",
        ],
    )

    spawn_gearbox_base = Node(
        package="ros_gz_sim",
        executable="create",
        output="screen",
        arguments=[
            "-world",
            "assembly_world",
            "-name",
            "gearbox_base",
            "-file",
            LaunchConfiguration("generated_gearbox_base_urdf"),
            "-x",
            "-0.33",
            "-y",
            "0.34",
            "-z",
            "0.79",
        ],
    )

    spawn_carrier = Node(
        package="ros_gz_sim",
        executable="create",
        output="screen",
        arguments=[
            "-world",
            "assembly_world",
            "-name",
            "carrier",
            "-file",
            LaunchConfiguration("generated_carrier_urdf"),
            "-x",
            "0.22",
            "-y",
            "0.28",
            "-z",
            "0.79",
        ],
    )

    assembly_demo = Node(
        package="gearbox_sim",
        executable="assembly_demo.py",
        output="screen",
        parameters=[
            {
                "use_sim_time": use_sim_time,
                "gripper_to_demo_sun_m": float(demo_sun_mount_z),
            }
        ],
        condition=IfCondition(run_demo),
    )

    joint_gui_teleop = Node(
        package="gearbox_sim",
        executable="joint_gui_teleop.py",
        output="screen",
        parameters=[{"use_sim_time": use_sim_time}],
        condition=IfCondition(gui_teleop),
    )

    return LaunchDescription(
        [
            DeclareLaunchArgument("world", default_value=world_file),
            DeclareLaunchArgument("use_sim_time", default_value="true"),
            DeclareLaunchArgument("run_demo", default_value="false"),
            DeclareLaunchArgument("gui_teleop", default_value="true"),
            DeclareLaunchArgument("calibration_mode", default_value="false"),
            SetEnvironmentVariable("RCUTILS_COLORIZED_OUTPUT", "1"),
            OpaqueFunction(function=_generate_temp_models),
            gz_sim,
            robot_state_publisher,
            spawn_service_bridge,
            topic_bridge,
            TimerAction(
                period=4.0,
                actions=[
                    spawn_robot,
                    spawn_gearbox_base,
                    spawn_carrier,
                    TimerAction(
                        period=4.0,
                        actions=[
                            assembly_demo,
                            joint_gui_teleop,
                        ],
                    ),
                ],
            ),
        ]
    )
