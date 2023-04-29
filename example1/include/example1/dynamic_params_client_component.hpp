#pragma once

#include <chrono>
#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp>

namespace example1
{

class DynamicParamsClient : public rclcpp::Node
{
public:
  explicit DynamicParamsClient(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
  ~DynamicParamsClient();
  
private:
  void sendRequest();
  
  rclcpp::AsyncParametersClient::SharedPtr cli_params_;
};

} // namespace example1
