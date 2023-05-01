cmake_minimum_required(VERSION 3.8)
project(example4)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rosbag2_cpp REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)

set(bag_recorder_executable bag_recorder)
set(bag_recorder_library ${bag_recorder_executable}_core)
set(dependencies
  rclcpp
  rclcpp_components
  rosbag2_cpp
  std_msgs)

add_executable(${bag_recorder_executable}
  src/bag_recorder_node.cpp
  src/bag_recorder_component.cpp)
add_library(${bag_recorder_library} SHARED
  src/bag_recorder_component.cpp)
ament_target_dependencies(${bag_recorder_executable}
  ${dependencies})
ament_target_dependencies(${bag_recorder_library}
  ${dependencies})
rclcpp_components_register_nodes(${bag_recorder_library}
  "example4::BagRecorder")
  
install(TARGETS ${bag_recorder_executable}
  RUNTIME DESTINATION lib/${PROJECT_NAME})
install(TARGETS ${bag_recorder_library}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
install(DIRECTORY include/
  DESTINATION include/)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(include)
ament_export_libraries(${bag_recorder_library})
ament_export_dependencies(${dependencies})
ament_package()
