cmake_minimum_required(VERSION 3.8)
project(example1)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(example_msgs REQUIRED)

include_directories(include)

set(dynamic_params_server_executable dynamic_params_server)
set(dynamic_params_server_library ${dynamic_params_server_executable}_core)
set(dynamic_params_client_executable dynamic_params_client)
set(dynamic_params_client_library ${dynamic_params_client_executable}_core)
set(dependencies
  rclcpp
  rclcpp_components
  example_msgs)
  
add_executable(${dynamic_params_server_executable}
  src/dynamic_params_server_node.cpp
  src/dynamic_params_server_component.cpp)
add_executable(${dynamic_params_client_executable}
  src/dynamic_params_client_node.cpp
  src/dynamic_params_client_component.cpp)
add_library(${dynamic_params_server_library} SHARED
  src/dynamic_params_server_component.cpp)
add_library(${dynamic_params_client_library} SHARED
  src/dynamic_params_client_component.cpp)
ament_target_dependencies(${dynamic_params_server_executable}
  ${dependencies})
ament_target_dependencies(${dynamic_params_client_executable}
  ${dependencies})
ament_target_dependencies(${dynamic_params_server_library}
  ${dependencies})
ament_target_dependencies(${dynamic_params_client_library}
  ${dependencies})
rclcpp_components_register_nodes(${dynamic_params_server_library}
  "example1::DynamicParamsServer")
rclcpp_components_register_nodes(${dynamic_params_client_library}
  "example1::DynamicParamsClient")

install(TARGETS ${dynamic_params_server_executable} ${dynamic_params_client_executable}
  RUNTIME DESTINATION lib/${PROJECT_NAME})
install(TARGETS ${dynamic_params_server_library} ${dynamic_params_client_library}
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
ament_export_libraries(${dynamic_params_server_library} ${dynamic_params_client_library})
ament_export_dependencies(${dependencies})
ament_package()
