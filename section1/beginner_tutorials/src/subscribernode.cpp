#include "ros/ros.h"
#include "std_msgs/String.h"

namespace subscriber
{  
  void chatterCallback(const std_msgs::String::ConstPtr& message)
  {
    ROS_INFO("%s", message->data.c_str());
  }

} // namespace subscriber

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "subscribernode");

  ros::NodeHandle node_handle;

  ros::Subscriber subscriber1 = node_handle.subscribe("/welcome_message", 100, subscriber::chatterCallback);

  ros::spin();

  return 0;
}

