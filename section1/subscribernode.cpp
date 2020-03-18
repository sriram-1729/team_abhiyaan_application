#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("%s", msg->data.c_str());
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "subscribernode");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/welcome_message", 100, chatterCallback);

  ros::spin();

  return 0;
}
