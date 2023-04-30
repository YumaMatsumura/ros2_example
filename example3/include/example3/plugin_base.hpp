#pragma once

#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>

namespace example3
{

class PluginBase
{
public:
  PluginBase();
  virtual ~PluginBase();
  void initialize(std::string name, const rclcpp_lifecycle::LifecycleNode::WeakPtr & node);
  virtual void activate() {}
  virtual void deactivate() {}
  
protected:
  virtual void onInitialize() {}
  
  std::string name_;
  rclcpp_lifecycle::LifecycleNode::WeakPtr node_;
  rclcpp::Logger logger_{rclcpp::get_logger("example3")};
};

} // namespace example3
