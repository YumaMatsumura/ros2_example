#include <memory>

#include <rclcpp/rclcpp.hpp>
#include "example4/bag_recorder_component.hpp"

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor exe;
  auto node = std::make_shared<example4::BagRecorder>();
  exe.add_node(node->get_node_base_interface());
  exe.spin();
  rclcpp::shutdown();
  
  return 0;
}
