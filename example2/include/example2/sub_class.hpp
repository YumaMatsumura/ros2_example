#pragma once

#include <chrono>
#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/string.hpp>

using namespace std::placeholders;
using namespace std::chrono_literals;

namespace example2
{

class SubClass : public rclcpp::Node
{
public:
  explicit SubClass(const std::string & name, const std::string & parent_namespace);
  ~SubClass();
  
private:
  void publishString();
  
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_string_;
  rclcpp::TimerBase::SharedPtr timer_;
};

} // namespace example2
