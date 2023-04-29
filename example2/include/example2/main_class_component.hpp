#pragma once

#include <chrono>
#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/string.hpp>

#include "example2/sub_class.hpp"
#include "example_util/node_thread.hpp"

using namespace std::placeholders;
using namespace std::chrono_literals;

namespace example2
{

class MainClass : public rclcpp::Node
{
public:
  explicit MainClass(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
  ~MainClass();
  
private:
  void publishString();
  
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_string_;
  rclcpp::TimerBase::SharedPtr timer_;
  
  std::shared_ptr<example2::SubClass> sub_class_;
  std::unique_ptr<example_util::NodeThread> sub_class_thread_;
};

} // namespace example2
