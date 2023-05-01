#include "example5/bt_engine_component.hpp"

namespace example5
{

BtEngine::BtEngine(const rclcpp::NodeOptions& options)
: Node("bt_engine", options)
{
  const std::vector<std::string> plugin_libs = {"hello_world_action_bt_node"};
  
  // Set ros2 params
  this->declare_parameter<std::vector<std::string>>("plugin_lib_names", plugin_libs);
  this->declare_parameter<std::string>("bt_file", "/path/to/hello_world.xml");
  this->declare_parameter<uint16_t>("publisher_port", 1666);
  this->declare_parameter<uint16_t>("server_port", 1667);
  this->declare_parameter<uint16_t>("max_msg_per_second", 25);
  this->declare_parameter<bool>("use_groot_monitor", true);
  
  
  // Get ros2 params
  std::string xml_package_path;
  std::string xml_filename;
  bool use_groot_monitor;
  this->get_parameter("plugin_lib_names", plugin_lib_names_);
  this->get_parameter("bt_file", bt_file_);
  this->get_parameter("publisher_port", publisher_port_);
  this->get_parameter("server_port", server_port_);
  this->get_parameter("max_msg_per_second", max_msg_per_second_);
  this->get_parameter("use_groot_monitor", use_groot_monitor);
  
  loadPlugins();
  loadTree();
  if(use_groot_monitor) {
    publishToGrootMonitor();
  }
  
  // Create timer
  timer_ = this->create_wall_timer(500ms, std::bind(&BtEngine::timerCallback, this));
}

void BtEngine::timerCallback()
{
  tree_->tickRoot();
}

void BtEngine::publishToGrootMonitor()
{
  groot_monitor_ = std::make_unique<BT::PublisherZMQ>(
    *tree_, max_msg_per_second_, publisher_port_, server_port_);
}

void BtEngine::loadPlugins()
{
  BT::SharedLibrary loader;
  for(const auto & p : plugin_lib_names_) {
    RCLCPP_INFO(this->get_logger(), "Loading plugin: %s", loader.getOSName(p).c_str());
    factory_.registerFromPlugin(loader.getOSName(p));
  }
}

void BtEngine::loadTree()
{
  auto blackboard = BT::Blackboard::create();
  blackboard->set<rclcpp::Node::SharedPtr>("node", std::make_shared<rclcpp::Node>("bt_node"));
  tree_ = std::make_shared<BT::Tree>(factory_.createTreeFromFile(bt_file_, blackboard));
}

} // namespace example5

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(example5::BtEngine)
