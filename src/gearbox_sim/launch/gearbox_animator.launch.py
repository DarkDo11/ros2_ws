import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    pkg_share = get_package_share_directory("gearbox_sim")
    urdf_path = os.path.join(pkg_share, "urdf", "gearbox.urdf")
    rviz_config_path = os.path.join(pkg_share, "config", "gearbox_animator.rviz")

    with open(urdf_path, "r", encoding="utf-8") as stream:
        robot_description = stream.read()

    use_rviz = LaunchConfiguration("use_rviz")

    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="screen",
        parameters=[{"robot_description": robot_description}],
    )

    animator = Node(
        package="gearbox_sim",
        executable="animator.py",
        output="screen",
    )

    rviz = Node(
        package="rviz2",
        executable="rviz2",
        output="screen",
        arguments=["-d", rviz_config_path],
        condition=IfCondition(use_rviz),
    )

    return LaunchDescription(
        [
            DeclareLaunchArgument("use_rviz", default_value="true"),
            robot_state_publisher,
            animator,
            rviz,
        ]
    )
