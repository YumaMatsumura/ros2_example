#pragma once

#include <chrono>
#include <string>
#include <memory>
#include <vector>
#include <mutex>

#include <rclcpp/rclcpp.hpp>

#include "example_msgs/msg/params.hpp"

using namespace std::placeholders;
using namespace std::chrono_literals;

namespace example1
{

class DynamicParamsServer : public rclcpp::Node
{
public:
  explicit DynamicParamsServer(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
  ~DynamicParamsServer();
  
private:
  void publishParams();
  rcl_interfaces::msg::SetParametersResult
  dynamicParametersCallback(std::vector<rclcpp::Parameter> parameters);
  
  // Dynamic parameters handler
  rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr dyn_params_handler_;
  std::mutex dynamic_params_lock_;
  
  // Publisher
  rclcpp::Publisher<example_msgs::msg::Params>::SharedPtr pub_params_;
  
  // Timer
  rclcpp::TimerBase::SharedPtr timer_;
  
  // Parameters
  bool bool_example_;
  int int_example_;
  double double_example_;
  std::string string_example_;
};

} // namespace example1
