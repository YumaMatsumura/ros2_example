#include "example1/dynamic_params_server_component.hpp"

namespace example1
{

DynamicParamsServer::DynamicParamsServer(const rclcpp::NodeOptions & options)
: Node("dynamic_params_server", options)
{
  this->declare_parameter<bool>("bool_example", true);
  this->declare_parameter<int>("int_example", 1);
  this->declare_parameter<double>("double_example", 1.0);
  this->declare_parameter<std::string>("string_example", "example");
  
  this->get_parameter("bool_example", bool_example_);
  this->get_parameter("int_example", int_example_);
  this->get_parameter("double_example", double_example_);
  this->get_parameter("string_example", string_example_);
  
  dyn_params_handler_ = this->add_on_set_parameters_callback(
    std::bind(&DynamicParamsServer::dynamicParametersCallback, this, _1));
  pub_params_ = this->create_publisher<example_msgs::msg::Params>("params", 1);
  timer_ = this->create_wall_timer(
    500ms, std::bind(&DynamicParamsServer::publishParams, this));
}

DynamicParamsServer::~DynamicParamsServer()
{
}

void DynamicParamsServer::publishParams()
{
  std::lock_guard<std::mutex> lock(dynamic_params_lock_);
  
  example_msgs::msg::Params msg;
  
  msg.bool_value = bool_example_;
  msg.int_value = int_example_;
  msg.double_value = double_example_;
  msg.string_value = string_example_;
  
  pub_params_->publish(msg);
}

rcl_interfaces::msg::SetParametersResult
DynamicParamsServer::dynamicParametersCallback(std::vector<rclcpp::Parameter> parameters)
{
  std::lock_guard<std::mutex> lock(dynamic_params_lock_);
  
  rcl_interfaces::msg::SetParametersResult result;
  
  for(auto parameter : parameters) {
    //const auto & type = parameter.get_type();
    const auto & name = parameter.get_name();
    
    if(name == "bool_example") {
      bool_example_ = parameter.as_bool();
    }
    else if(name == "int_example") {
      int_example_ = parameter.as_int();
    }
    else if(name == "double_example") {
      double_example_ = parameter.as_double();
    }
    else if(name == "string_example") {
      string_example_ = parameter.as_string();
    }
  }
  
  result.successful = true;
  return result;
}

} // namespace example1

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(example1::DynamicParamsServer)
