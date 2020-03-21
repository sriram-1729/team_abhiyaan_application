#include "ros/ros.h"
#include "beginner_tutorials/Turtle1.h"
#include<math.h>

#define PI 3.1415926

bool velocity(beginner_tutorials::Turtle1::Request &req, beginner_tutorials::Turtle1::Response &res)
{
  float distance = sqrt(pow(req.abhiyaanPosition.x - req.turtle1Position.x, 2) + pow(req.abhiyaanPosition.y - req.turtle1Position.y, 2));
  float velocity = 1;
  
  while(distance > 2)
    {
      float angle = atan((req.abhiyaanPosition.y - req.turtle1Position.y) / (req.abhiyaanPosition.x - req.turtle1Position.x));
      if (((angle > 0) && ((req.abhiyaanPosition.y - req.turtle1Position.y) < 0))||(((angle < 0) && ((req.abhiyaanPosition.y - req.turtle1Position.y) > 0))))
	angle = angle + PI;
      
      while((req.turtle1Position.theta >= angle + 0.1) || (req.turtle1Position.theta <= angle - 0.1))
	{
	  res.turtle1Velocity.angular.z = 1;
	  return true;
	}
      res.turtle1Velocity.linear.z = res.turtle1Velocity.angular.x = res.turtle1Velocity.angular.y = 0;

      res.turtle1Velocity.linear.x = velocity * cos(req.turtle1Position.theta);
      res.turtle1Velocity.linear.y = velocity * sin(req.turtle1Position.theta);
      return true;
    }
  
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "turtle1_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("turtle1_velocity", velocity);
  ROS_INFO("Starting turtle1Velocity service.");
  ros::spin();

  return 0;
}
