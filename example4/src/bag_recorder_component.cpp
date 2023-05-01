#include "example4/bag_recorder_component.hpp"

namespace example4
{

BagRecorder::BagRecorder(const rclcpp::NodeOptions & options)
: Node("bag_recorder", options)
{
  std::string bag_file;
  
  this->declare_parameter<std::string>(
    "bag_file", "/path/to/sample_bag");
  this->get_parameter("bag_file", bag_file);
  
  writer_ = std::make_unique<rosbag2_cpp::Writer>();
  writer_->open(bag_file);
  
  sub_string_ = this->create_subscription<std_msgs::msg::String>(
    "sample", 10, std::bind(&BagRecorder::stringCallback, this, _1));
}

BagRecorder::~BagRecorder()
{
}

void BagRecorder::stringCallback(std::shared_ptr<rclcpp::SerializedMessage> msg) const
{
  rclcpp::Time time_stamp = this->now();
  writer_->write(msg, "sample", "std_msgs/msg/String", time_stamp);
}

} // namespace example4

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(example4::BagRecorder)
