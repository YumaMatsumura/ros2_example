cmake_minimum_required(VERSION 3.8)
project(example3)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(std_msgs REQUIRED)
find_package(pluginlib REQUIRED)

include_directories(include)

set(load_plugins_executable load_plugins)
set(load_plugins_library ${load_plugins_execuctable}_core)
set(plugin_library plugin_library)
set(dependencies
  rclcpp
  rclcpp_components
  rclcpp_lifecycle
  std_msgs
  pluginlib)
  
add_executable(${load_plugins_executable}
  src/load_plugins_node.cpp
  src/load_plugins_component.cpp
  src/plugin_base.cpp)
add_library(${load_plugins_library} SHARED
  src/load_plugins_component.cpp
  src/plugin_base.cpp)
add_library(${plugin_library} SHARED
  plugins/sample_plugin.cpp)
ament_target_dependencies(${load_plugins_executable}
  ${dependencies})
ament_target_dependencies(${load_plugins_library}
  ${dependencies})
ament_target_dependencies(${plugin_library}
  ${dependencies})
rclcpp_components_register_nodes(${load_plugins_library}
  "example3::LoadPlugins")
target_link_libraries(${plugin_library}
  ${load_plugins_library})
  
install(TARGETS ${load_plugins_executable}
  RUNTIME DESTINATION lib/${PROJECT_NAME})
install(TARGETS ${load_plugins_library} ${plugin_library}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
install(FILES plugins.xml
  DESTINATION share/${PROJECT_NAME})
install(DIRECTORY launch params
  DESTINATION share/${PROJECT_NAME})
install(DIRECTORY include/
  DESTINATION include/)
  
pluginlib_export_plugin_description_file(example3 plugins.xml)

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
ament_export_libraries(${load_plugins_library} ${plugin_library})
ament_export_dependencies(${dependencies})
ament_package()
