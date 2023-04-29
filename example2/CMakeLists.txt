cmake_minimum_required(VERSION 3.8)
project(example2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_util REQUIRED)

include_directories(include)

set(main_class_executable main_class)
set(main_class_library ${main_class}_core)
set(sub_class_library sub_class_core)
set(dependencies
  rclcpp
  rclcpp_components
  std_msgs
  example_util)
  
add_executable(${main_class_executable}
  src/main_class_node.cpp
  src/main_class_component.cpp
  src/sub_class.cpp)
add_library(${main_class_library} SHARED
  src/main_class_component.cpp)
add_library(${sub_class_library} SHARED
  src/sub_class.cpp)
ament_target_dependencies(${main_class_executable}
  ${dependencies})
ament_target_dependencies(${main_class_library}
  ${dependencies})
ament_target_dependencies(${sub_class_library}
  ${dependencies})
rclcpp_components_register_nodes(${main_class_library}
  "example2::MainClass")
  
install(TARGETS ${main_class_executable}
  RUNTIME DESTINATION lib/${PROJECT_NAME})
install(TARGETS ${main_class_library} ${sub_class_library}
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
ament_export_libraries(${main_class_library} ${sub_class_library})
ament_export_dependencies(${dependencies})
ament_package()
