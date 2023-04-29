#include "example1/dynamic_params_client_component.hpp"

namespace example1
{

DynamicParamsClient::DynamicParamsClient(const rclcpp::NodeOptions & options)
: Node("dynamic_params_client", options)
{
  std::string target_node;
  
  this->declare_parameter<std::string>("target_node", "dynamic_params_server");
  this->get_parameter("target_node", target_node);
  
  cli_params_ = std::make_shared<rclcpp::AsyncParametersClient>(this, target_node);
  
  sendRequest();
}

DynamicParamsClient::~DynamicParamsClient()
{
}

void DynamicParamsClient::sendRequest()
{
  while(!cli_params_->wait_for_service(std::chrono::seconds(1))) {
    if(!rclcpp::ok()) {
      RCLCPP_ERROR(this->get_logger(), "Interrepted while waiting for the service. Exiting.");
      return;
    }
    RCLCPP_INFO(this->get_logger(), "Service not available, waiting again...");
  }
  
  auto result_future = cli_params_->set_parameters({
    rclcpp::Parameter("bool_example", false),
    rclcpp::Parameter("int_example", -1),
    rclcpp::Parameter("double_example", 12.3),
    rclcpp::Parameter("string_example", "hogehoge")});
  if(rclcpp::spin_until_future_complete(this->get_node_base_interface(), result_future) != rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_ERROR(this->get_logger(), "Failed to get param list.");
    return;
  }
  for(auto &result : result_future.get()) {
    if(!result.successful) {
      RCLCPP_ERROR(this->get_logger(), "Failed to set parameters: %s", result.reason.c_str());
    }
  }
}

} // namespace example1

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(example1::DynamicParamsClient)
