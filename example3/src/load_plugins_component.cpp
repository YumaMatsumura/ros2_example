#include "example3/load_plugins_component.hpp"

namespace example3
{

LoadPlugins::LoadPlugins(const rclcpp::NodeOptions & options)
: rclcpp_lifecycle::LifecycleNode("load_plugins", options)
{
  this->declare_parameter<std::vector<std::string>>("plugins", std::vector<std::string>(0, ""));
}

LoadPlugins::~LoadPlugins()
{
}

CallbackReturn LoadPlugins::on_configure(const rclcpp_lifecycle::State &)
{
  RCLCPP_INFO(this->get_logger(), "on_configure() was called.");
  
  try {
    loadPlugins();
  }
  catch(const std::exception & e) {
    RCLCPP_ERROR(this->get_logger(), "Could not load plugins! Caught exception: %s", e.what());
  }
  
  return CallbackReturn::SUCCESS;
}

CallbackReturn LoadPlugins::on_activate(const rclcpp_lifecycle::State &){
  RCLCPP_INFO(this->get_logger(), "on_activate() was called.");
  
  start();
  
  return CallbackReturn::SUCCESS;
}

CallbackReturn LoadPlugins::on_deactivate(const rclcpp_lifecycle::State &){
  RCLCPP_INFO(this->get_logger(), "on_deactivate() was called.");
  
  stop();
  
  return CallbackReturn::SUCCESS;
}

CallbackReturn LoadPlugins::on_cleanup(const rclcpp_lifecycle::State &){
  RCLCPP_INFO(this->get_logger(), "on_cleanup() was called.");
  
  return CallbackReturn::SUCCESS;
}

CallbackReturn LoadPlugins::on_shutdown(const rclcpp_lifecycle::State &){
  RCLCPP_INFO(this->get_logger(), "on_configure() was called.");
  
  return CallbackReturn::SUCCESS;
}

void LoadPlugins::loadPlugins()
{
  this->get_parameter("plugins", plugin_names_);
  
  plugins_.resize(plugin_names_.size());
  plugin_types_.resize(plugin_names_.size());
  
  for(size_t i = 0; i < plugin_names_.size(); i++) {
    this->declare_parameter<std::string>(plugin_names_[i] + ".plugin", "");
    if(!this->get_parameter(plugin_names_[i] + ".plugin", plugin_types_[i])) {
      throw std::runtime_error("No plugins defined for load_plugins node.");
    }
    
    this->get_parameter(plugin_names_[i] + ".plugin", plugin_types_[i]);
    
    try {
      RCLCPP_INFO(this->get_logger(), "Load %s plugin.", plugin_names_[i].c_str());
      plugins_[i] = plugin_loader_.createSharedInstance(plugin_types_[i]);
      plugins_[i]->initialize(plugin_names_[i], shared_from_this());
    }
    catch(pluginlib::PluginlibException & ex) {
      RCLCPP_ERROR(
        this->get_logger(), 
        "The plugin failed to load for some reason. Error: %s", ex.what());
    }
    RCLCPP_INFO(this->get_logger(), "Plugin initialized.");
  }
}

void LoadPlugins::start()
{
  for(size_t i = 0; i < plugins_.size(); i++) {
    plugins_[i]->activate();
  }
}

void LoadPlugins::stop()
{
  for(size_t i = 0; i < plugins_.size(); i++) {
    plugins_[i]->deactivate();
  }
}

} // namespace example3

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(example3::LoadPlugins)
