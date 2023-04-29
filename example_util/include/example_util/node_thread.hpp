#pragma once

#include<memory>

#include <rclcpp/rclcpp.hpp>

namespace example_util
{

class NodeThread
{
public:
  explicit NodeThread(rclcpp::node_interfaces::NodeBaseInterface::SharedPtr node_base);
  ~NodeThread();
  
protected:
  rclcpp::node_interfaces::NodeBaseInterface::SharedPtr node_;
  std::unique_ptr<std::thread> thread_;
  rclcpp::Executor::SharedPtr exe_;
};

} // namespace example_util
