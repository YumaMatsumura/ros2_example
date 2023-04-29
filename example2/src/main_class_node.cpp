#include <memory>

#include <rclcpp/rclcpp.hpp>
#include "example2/main_class_component.hpp"

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor exe;
  auto node = std::make_shared<example2::MainClass>();
  exe.add_node(node->get_node_base_interface());
  exe.spin();
  rclcpp::shutdown();
  
  return 0;
}
