#include "example2/main_class_component.hpp"

namespace example2
{

MainClass::MainClass(const rclcpp::NodeOptions & options)
: rclcpp::Node("main_class", options)
{
  sub_class_ = std::make_shared<example2::SubClass>("sub_class", std::string{get_namespace()});
  sub_class_thread_ = std::make_unique<example_util::NodeThread>(sub_class_->get_node_base_interface());
  
  pub_string_ = this->create_publisher<std_msgs::msg::String>("main", 1);
  timer_ = this->create_wall_timer(500ms, std::bind(&MainClass::publishString, this));
}

MainClass::~MainClass()
{
  sub_class_thread_.reset();
}

void MainClass::publishString()
{
  std_msgs::msg::String msg;
  msg.data = "main";
  pub_string_->publish(msg);
}


} // namespace example2

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(example2::MainClass)
