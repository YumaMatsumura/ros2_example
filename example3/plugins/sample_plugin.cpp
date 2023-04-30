#include "example3/plugins/sample_plugin.hpp"

namespace example3
{

SamplePlugin::SamplePlugin()
{
}

SamplePlugin::~SamplePlugin()
{
}

void SamplePlugin::onInitialize()
{
  auto node = node_.lock();
  if(!node) {
    throw std::runtime_error{"Failed to lock node"};
  }
  
  pub_string_ = node->create_publisher<std_msgs::msg::String>("sample", 1);
}

void SamplePlugin::activate()
{
  RCLCPP_INFO(logger_, "Activate was called.");
  
  auto node = node_.lock();
  if(!node) {
    throw std::runtime_error{"Failed to lock node"};
  }
  pub_string_->on_activate();
  timer_ = node->create_wall_timer(500ms, std::bind(&SamplePlugin::publishString, this));
}

void SamplePlugin::deactivate()
{
  RCLCPP_INFO(logger_, "Deactivate was called.");
  
  if(timer_) {
    timer_->cancel();
    timer_.reset();
  }
  
  pub_string_->on_deactivate();
}

void SamplePlugin::publishString()
{
  RCLCPP_INFO(logger_, "Timer called.");
  
  std_msgs::msg::String msg;
  msg.data = "sample";
  pub_string_->publish(msg);
}

} // namespace example3

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(example3::SamplePlugin, example3::PluginBase)
