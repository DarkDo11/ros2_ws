import os
import subprocess
import tempfile

from ament_index_python.packages import PackageNotFoundError, get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription, LogInfo, OpaqueFunction, SetEnvironmentVariable, TimerAction
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PythonExpression
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def _generate_scene_urdf(context):
    pkg_share = get_package_share_directory("gearbox_sim")
    xacro_exec = FindExecutable(name="xacro").perform(context)
    out_dir = tempfile.mkdtemp(prefix="gearbox_cell_")
    output_urdf = os.path.join(out_dir, "main_scene.urdf")
    xacro_file = os.path.join(pkg_share, "urdf", "main_scene.urdf.xacro")

    with open(output_urdf, "w", encoding="utf-8") as stream:
        subprocess.run([xacro_exec, xacro_file], check=True, stdout=stream)

    context.launch_configurations["scene_urdf"] = output_urdf
    return []


def _maybe_moveit_notice(_context):
    try:
        get_package_share_directory("moveit_ros_move_group")
        get_package_share_directory("moveit_msgs")
        return [LogInfo(msg="MoveIt packages detected. motion_planner.py will use /compute_ik and /compute_cartesian_path when available.")]
    except PackageNotFoundError:
        return [LogInfo(msg="MoveIt packages are not installed in this environment. motion_planner.py will stay in dry-run fallback mode.")]


def _build_gz_args(context):
    pkg_share = get_package_share_directory("gearbox_sim")
    world_file = os.path.join(pkg_share, "worlds", "assembly_cell.sdf")
    gz_verbose = LaunchConfiguration("gz_verbose").perform(context)

    # Run the SERVER headless (-s). On NVIDIA + Gazebo Harmonic, a combined
    # server+GUI process makes the GUI's GLX context collide with the server's
    # camera-sensor EGL render context: the camera RenderThread starts, advertises
    # the /cameras/* topics, then dies ("egl: failed to create dri2 screen" ->
    # SensorsPrivate::RenderThread stopped) and no frames are ever published.
    # Splitting the headless server (owns camera rendering) from a separate GUI
    # process keeps the camera render thread alive.
    context.launch_configurations["gz_args"] = f"-r -s -v {gz_verbose} {world_file}"
    return []


def generate_launch_description():
    pkg_share = get_package_share_directory("gearbox_sim")
    ros_gz_sim_share = get_package_share_directory("ros_gz_sim")

    use_sim_time = LaunchConfiguration("use_sim_time")
    run_state_machine = LaunchConfiguration("run_state_machine")
    planner_dry_run = LaunchConfiguration("planner_dry_run")
    gz_args = LaunchConfiguration("gz_args")

    world_file = os.path.join(pkg_share, "worlds", "assembly_cell.sdf")
    xacro_file = os.path.join(pkg_share, "urdf", "main_scene.urdf.xacro")
    config_file = os.path.join(pkg_share, "config", "assembly_cell.yaml")
    robot_description = ParameterValue(Command([FindExecutable(name="xacro"), " ", xacro_file]), value_type=str)

    topic_bridge = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        output="screen",
        arguments=[
            "/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock",
            "/joint_states@sensor_msgs/msg/JointState[gz.msgs.Model",
            "/ur5e_press/ft_sensor@geometry_msgs/msg/Wrench[gz.msgs.Wrench",
            "/ur5e_assembly/ft_sensor@geometry_msgs/msg/Wrench[gz.msgs.Wrench",
            "/ur3e_screw/ft_sensor@geometry_msgs/msg/Wrench[gz.msgs.Wrench",
            "/ur5e_press/joint_trajectory@trajectory_msgs/msg/JointTrajectory]gz.msgs.JointTrajectory",
            "/ur5e_assembly/joint_trajectory@trajectory_msgs/msg/JointTrajectory]gz.msgs.JointTrajectory",
            "/ur3e_screw/joint_trajectory@trajectory_msgs/msg/JointTrajectory]gz.msgs.JointTrajectory",
            "/ur3e_screw_tool/joint_trajectory@trajectory_msgs/msg/JointTrajectory]gz.msgs.JointTrajectory",
            "/press/joint_trajectory@trajectory_msgs/msg/JointTrajectory]gz.msgs.JointTrajectory",
        ],
    )

    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="screen",
        parameters=[{"use_sim_time": use_sim_time, "robot_description": robot_description}],
    )

    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(ros_gz_sim_share, "launch", "gz_sim.launch.py")),
        launch_arguments={"gz_args": gz_args}.items(),
    )

    # Separate GUI process (server runs headless for camera rendering). Started
    # after a short delay so the server is up; its OpenGL/GLX context lives in a
    # different process and no longer kills the server-side camera render thread.
    gz_gui = ExecuteProcess(
        cmd=["gz", "sim", "-g", "-v", "2"],
        output="screen",
        condition=IfCondition(PythonExpression(["'", LaunchConfiguration("gz_gui"), "' == 'true'"])),
    )

    move_group_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(pkg_share, "launch", "move_group.launch.py")),
        condition=IfCondition(PythonExpression(["'", planner_dry_run, "' == 'false'"])),
        launch_arguments={"use_sim_time": use_sim_time}.items(),
    )

    spawn_scene = Node(
        package="ros_gz_sim",
        executable="create",
        output="screen",
        arguments=["-world", "assembly_world", "-name", "gearbox_assembly_cell", "-file", LaunchConfiguration("scene_urdf")],
    )

    press_controller = Node(
        package="gearbox_sim",
        executable="press_controller.py",
        output="screen",
        parameters=[{"use_sim_time": use_sim_time}],
    )

    screwdriver_server = Node(
        package="gearbox_sim",
        executable="screwdriver_server.py",
        output="screen",
        parameters=[{"use_sim_time": use_sim_time}],
    )

    ft_monitor = Node(
        package="gearbox_sim",
        executable="ft_monitor.py",
        output="screen",
        parameters=[
            {
                "use_sim_time": use_sim_time,
                "force_threshold_n": 5.0,
                "torque_threshold_nm": 1.0,
            }
        ],
    )

    grasp_attacher = Node(
        package="gearbox_sim",
        executable="grasp_attacher.py",
        output="screen",
        parameters=[
            {
                "use_sim_time": use_sim_time,
                "config_file": config_file,
                "sync_entity_poses": True,
            }
        ],
    )

    motion_planner = Node(
        package="gearbox_sim",
        executable="motion_planner.py",
        output="screen",
        parameters=[
            {
                "use_sim_time": use_sim_time,
                "config_file": config_file,
                "dry_run": planner_dry_run,
            }
        ],
    )

    state_machine = Node(
        package="gearbox_sim",
        executable="assembly_fsm.py",
        name="assembly_fsm",
        output="screen",
        condition=IfCondition(run_state_machine),
        parameters=[
            {
                "use_sim_time": use_sim_time,
                "config_file": config_file,
                "dry_run": planner_dry_run,
                "start_delay_sec": 5.0,
            }
        ],
    )

    camera_press = Node(package="ros_gz_image", executable="image_bridge", arguments=["/cameras/press/image_raw"], output="screen")
    camera_transfer = Node(package="ros_gz_image", executable="image_bridge", arguments=["/cameras/transfer/image_raw"], output="screen")
    camera_assembly = Node(package="ros_gz_image", executable="image_bridge", arguments=["/cameras/assembly/image_raw"], output="screen")
    camera_screw = Node(package="ros_gz_image", executable="image_bridge", arguments=["/cameras/screw/image_raw"], output="screen")
    camera_output = Node(package="ros_gz_image", executable="image_bridge", arguments=["/cameras/output/image_raw"], output="screen")

    part_spawner = Node(
        package="gearbox_sim",
        executable="part_spawner.py",
        output="screen",
        parameters=[{"use_sim_time": use_sim_time}],
    )

    yasmin_viewer = Node(
        package="yasmin_viewer",
        executable="yasmin_viewer_node",
        output="screen",
        parameters=[{"host": "localhost", "port": 5000}],
    )

    return LaunchDescription(
        [
            DeclareLaunchArgument("use_sim_time", default_value="true"),
            DeclareLaunchArgument("run_state_machine", default_value="true"),
            DeclareLaunchArgument("planner_dry_run", default_value="true"),
            DeclareLaunchArgument("gz_headless", default_value="false"),
            DeclareLaunchArgument("gz_gui", default_value="true"),
            DeclareLaunchArgument("gz_verbose", default_value="4"),
            SetEnvironmentVariable("RCUTILS_COLORIZED_OUTPUT", "1"),
            SetEnvironmentVariable("GZ_SIM_RESOURCE_PATH", pkg_share),
            OpaqueFunction(function=_generate_scene_urdf),
            OpaqueFunction(function=_build_gz_args),
            OpaqueFunction(function=_maybe_moveit_notice),
            gz_sim,
            gz_gui,
            move_group_launch,
            topic_bridge,
            robot_state_publisher,
            yasmin_viewer,
            TimerAction(
                period=4.0,
                actions=[
                    spawn_scene,
                    TimerAction(
                        period=4.0,
                        actions=[
                            press_controller,
                            screwdriver_server,
                            grasp_attacher,
                            motion_planner,
                            state_machine,
                            ft_monitor,
                            camera_press,
                            camera_transfer,
                            camera_assembly,
                            camera_screw,
                            camera_output,
                        ],
                    ),
                    TimerAction(
                        period=8.0,
                        actions=[part_spawner],
                    ),
                ],
            ),
        ]
    )
