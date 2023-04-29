#include "example_util/node_thread.hpp"

namespace example_util
{

NodeThread::NodeThread(rclcpp::node_interfaces::NodeBaseInterface::SharedPtr node_base)
: node_(node_base)
{
  exe_ = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
  thread_ = std::make_unique<std::thread>(
    [&]()
    {
      exe_->add_node(node_);
      exe_->spin();
      exe_->remove_node(node_);
    }
  );
}

NodeThread::~NodeThread()
{
  exe_->cancel();
  thread_->join();
}

} // namespace example_util
