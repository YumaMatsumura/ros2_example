#pragma once

#include <memory>
#include <string>
#include <vector>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>
#include <pluginlib/class_loader.hpp>

#include "example3/plugin_base.hpp"

using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

namespace example3
{

class LoadPlugins : public rclcpp_lifecycle::LifecycleNode
{
public:
  explicit LoadPlugins(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
  ~LoadPlugins();
  
  CallbackReturn on_configure(const rclcpp_lifecycle::State &);
  CallbackReturn on_activate(const rclcpp_lifecycle::State &);
  CallbackReturn on_deactivate(const rclcpp_lifecycle::State &);
  CallbackReturn on_cleanup(const rclcpp_lifecycle::State &);
  CallbackReturn on_shutdown(const rclcpp_lifecycle::State &);
  
  std::shared_ptr<example3::LoadPlugins> shared_from_this()
  {
    return std::static_pointer_cast<example3::LoadPlugins>(
      rclcpp_lifecycle::LifecycleNode::shared_from_this());
  }

private:
  void loadPlugins();
  void start();
  void stop();
  
  pluginlib::ClassLoader<example3::PluginBase> plugin_loader_{"example3", "example3::PluginBase"};
  std::vector<std::shared_ptr<example3::PluginBase>> plugins_;
  
  std::vector<std::string> plugin_names_;
  std::vector<std::string> plugin_types_;
};

} // namespace example3
