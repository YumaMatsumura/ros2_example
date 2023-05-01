cmake_minimum_required(VERSION 3.8)
project(example5)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(behaviortree_cpp_v3 REQUIRED)

include_directories(include)

set(bt_engine_executable bt_engine)
set(bt_engine_library ${bt_engine_executable}_core)
set(hello_world_action_bt_node hello_world_action_bt_node)
set(dependencies
  rclcpp
  rclcpp_components
  behaviortree_cpp_v3)
  
add_executable(${bt_engine_executable}
  src/bt_engine_node.cpp
  src/bt_engine_component.cpp)
add_library(${bt_engine_library} SHARED
  src/bt_engine_component.cpp)
add_library(${hello_world_action_bt_node} SHARED
  plugins/action/hello_world_action.cpp)
ament_target_dependencies(${bt_engine_executable}
  ${dependencies})
ament_target_dependencies(${bt_engine_library}
  ${dependencies})
rclcpp_components_register_nodes(${bt_engine_library}
  "example5::BtEngine")
  
list(APPEND plugin_libs ${hello_world_action_bt_node})
foreach(bt_plugin ${plugin_libs})
  ament_target_dependencies(${bt_plugin} ${dependencies})
  target_compile_definitions(${bt_plugin} PRIVATE BT_PLUGIN_EXPORT)
endforeach()
  
install(TARGETS ${bt_engine_executable}
  RUNTIME DESTINATION lib/${PROJECT_NAME})
install(TARGETS ${bt_engine_library} ${plugin_libs}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
install(DIRECTORY behavior_trees
  DESTINATION share/${PROJECT_NAME})
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
ament_export_libraries(${bt_engine_library} ${plugin_libs})
ament_export_dependencies(${dependencies})
ament_package()
