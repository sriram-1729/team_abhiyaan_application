#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "publishernode");

  ros::NodeHandle node_handle;
  
  ros::Publisher publisher1 = node_handle.advertise<std_msgs::String>("/welcome_message", 100);

  ros::Rate loop_rate(10);

  while (ros::ok())
    {
     
      std_msgs::String message;

      std::stringstream stringstream1;
      stringstream1 << "Welcome to Abhiyaan";
      message.data = stringstream1.str();

      ROS_INFO("%s", message.data.c_str());

      publisher1.publish(message);

      ros::spinOnce();

      loop_rate.sleep();
    }


  return 0;
}
