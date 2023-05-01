#pragma once

#include <rclcpp/rclcpp.hpp>

#include "behaviortree_cpp_v3/bt_factory.h"
#include "behaviortree_cpp_v3/utils/shared_library.h"
#include "behaviortree_cpp_v3/loggers/bt_zmq_publisher.h"

using namespace std::chrono_literals;

namespace example5
{

class BtEngine : public rclcpp::Node
{
public:
  explicit BtEngine(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
  
private:
  void timerCallback();
  void publishToGrootMonitor();
  void loadPlugins();
  void loadTree();
  
  rclcpp::TimerBase::SharedPtr timer_;
  
  BT::BehaviorTreeFactory factory_;
  std::shared_ptr<BT::Tree> tree_;
  std::unique_ptr<BT::PublisherZMQ> groot_monitor_;
  
  std::vector<std::string> plugin_lib_names_;
  std::string bt_file_;
  
  uint16_t publisher_port_{}, server_port_{}, max_msg_per_second_{};
};

} // namespace example5
