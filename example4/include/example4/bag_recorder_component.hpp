#pragma once

#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <rosbag2_cpp/writer.hpp>

#include <std_msgs/msg/string.hpp>

using namespace std::placeholders;

namespace example4
{

class BagRecorder : public rclcpp::Node
{
public:
  explicit BagRecorder(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
  ~BagRecorder();
  
private:
  void stringCallback(std::shared_ptr<rclcpp::SerializedMessage> msg) const;
  
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_string_;
  
  std::unique_ptr<rosbag2_cpp::Writer> writer_;
};

} // namespace example4
