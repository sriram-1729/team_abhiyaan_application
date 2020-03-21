#include "ros/ros.h"
#include "beginner_tutorials/Turtle1.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <math.h>

#define PI 3.1415926

turtlesim::Pose abhi;
turtlesim::Pose turt1;
geometry_msgs::Twist vel;

bool velocity()
{
  float distance = sqrt(pow(abhi.x - turt1.x, 2) + pow(abhi.y - turt1.y, 2));
  float velocity = 2;
  
  while(distance > 2)
    {
      float angle = asin((abhi.y - turt1.y) / sqrt(pow((abhi.x - turt1.x), 2) + pow((abhi.y - turt1.y), 2)));
      if ((abhi.x - turt1.x < 0) && (abhi.y - turt1.y > 0))
	angle = PI - angle;
      else if((abhi.x - turt1.x < 0) && (abhi.y - turt1.y < 0))
	angle = PI - angle;
      else if((abhi.x - turt1.x > 0) && (abhi.y - turt1.y < 0)) 
	angle = 2 * PI + angle;
      while((turt1.theta >= angle + 0.1) || (turt1.theta <= angle - 0.1))
	{
	  vel.angular.z = 1;
	  return true;
	}
      
      vel.linear.z = vel.angular.x = vel.angular.y = vel.angular.z = 0;

      vel.linear.x = velocity * cos(turt1.theta);
      vel.linear.y = velocity * sin(turt1.theta);
      
      return true;
    }

  vel.linear.x = vel.linear.y = vel.angular.z = 0;
  
  return true;
}

void subsabhiyaanPose(const turtlesim::Pose& d_abhi)
{
  abhi.x = d_abhi.x;
  abhi.y = d_abhi.y;
  abhi.theta = d_abhi.theta;
  abhi.linear_velocity = d_abhi.linear_velocity;
  abhi.angular_velocity = d_abhi.angular_velocity;
}

void substurtle1Pose(const turtlesim::Pose& d_turt1)
{
  turt1.x = d_turt1.x;
  turt1.y = d_turt1.y;
  turt1.theta = d_turt1.theta;
  turt1.linear_velocity = d_turt1.linear_velocity;
  turt1.angular_velocity = d_turt1.angular_velocity;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "turtle1_client");
  ros::NodeHandle n;

  beginner_tutorials::Turtle1 srv;

  ros::Subscriber sub1 = n.subscribe("abhiyaan/pose", 100, subsabhiyaanPose);

  ros::Subscriber sub2 = n.subscribe("turtle1/pose", 100, substurtle1Pose);

  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 100);
  ros::Rate loop_rate(10);

  while(ros::ok())
    {
      velocity();
      
      pub.publish(vel);

      ros::spinOnce();
      loop_rate.sleep();
	  
    }
  
  return 0;
}
