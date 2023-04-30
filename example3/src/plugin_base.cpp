#include "example3/plugin_base.hpp"

namespace example3
{

PluginBase::PluginBase()
: name_()
{
}

PluginBase::~PluginBase()
{
}

void PluginBase::initialize(
  std::string name, const rclcpp_lifecycle::LifecycleNode::WeakPtr & node)
{
  name_ = name;
  node_ = node;
  {
    auto node_shared_ptr = node_.lock();
    logger_ = node_shared_ptr->get_logger();
  }
  
  onInitialize();
}
} // namespace example3
