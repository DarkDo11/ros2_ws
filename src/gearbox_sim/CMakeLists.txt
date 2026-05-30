cmake_minimum_required(VERSION 3.8)
project(gearbox_sim)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "action/RunScrewdriver.action"
  "srv/RunPressCycle.srv"
  "srv/SetAttachment.srv"
  DEPENDENCIES builtin_interfaces
)

# Устанавливаем папки в директорию share пакета
install(DIRECTORY
  config
  launch
  meshes
  urdf
  worlds
  DESTINATION share/${PROJECT_NAME}
)

install(FILES
  .setup_assistant
  DESTINATION share/${PROJECT_NAME}
)

install(PROGRAMS
  scripts/animator.py
  scripts/assembly_demo.py
  scripts/assembly_fsm.py
  scripts/assembly_sequence_legacy.py
  scripts/assembly_state_machine.py
  scripts/get_joints.py
  scripts/joint_gui_teleop.py
  scripts/motion_planner.py
  scripts/press_controller.py
  scripts/grasp_attacher.py
  scripts/screwdriver_server.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_export_dependencies(rosidl_default_runtime)

ament_package()
