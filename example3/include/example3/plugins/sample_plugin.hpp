#pragma once

#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_lifecycle/lifecycle_publisher.hpp>

#include <std_msgs/msg/string.hpp>

#include "example3/plugin_base.hpp"

using namespace std::chrono_literals;

namespace example3
{

class SamplePlugin : public example3::PluginBase
{
public:
  SamplePlugin();
  virtual ~SamplePlugin();
  virtual void onInitialize();
  virtual void activate();
  virtual void deactivate();
  
protected:
  void publishString();
  
  rclcpp_lifecycle::LifecyclePublisher<std_msgs::msg::String>::SharedPtr pub_string_;
  rclcpp::TimerBase::SharedPtr timer_;
};

} // namespace example3
