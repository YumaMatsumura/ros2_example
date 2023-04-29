#include "example2/sub_class.hpp"

namespace example2
{

SubClass::SubClass(
  const std::string & name,
  const std::string & parent_namespace)
: rclcpp::Node(name, 
  rclcpp::NodeOptions().arguments({
  "--ros-args", "-r", std::string("__ns:=") + parent_namespace,
  "--ros-args", "-r", std::string("__node:=") + name}))
{
  pub_string_ = this->create_publisher<std_msgs::msg::String>("sub", 1);
  timer_ = this->create_wall_timer(500ms, std::bind(&SubClass::publishString, this));
}

SubClass::~SubClass()
{
}

void SubClass::publishString()
{
  std_msgs::msg::String msg;
  msg.data = "sub";
  pub_string_->publish(msg);
}

} // namespace example2
