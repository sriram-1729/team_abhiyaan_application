#include "ros/ros.h"
#include "beginner_tutorials/Turtle1.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"

turtlesim::Pose abhi;
turtlesim::Pose turt1;

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

  ros::ServiceClient client = n.serviceClient<beginner_tutorials::Turtle1>("/turtle1_velocity");

  beginner_tutorials::Turtle1 srv;

  ros::Subscriber sub1 = n.subscribe("abhiyaan/pose", 100, subsabhiyaanPose);

  ros::Subscriber sub2 = n.subscribe("turtle1/pose", 100, substurtle1Pose);

  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 100);
  ros::Rate loop_rate(10);

  while(ros::ok())
    {
      srv.request.abhiyaanPosition.x = abhi.x;
      srv.request.abhiyaanPosition.y = abhi.y;
      srv.request.abhiyaanPosition.theta = abhi.theta;
      srv.request.abhiyaanPosition.linear_velocity = abhi.linear_velocity;
      srv.request.abhiyaanPosition.angular_velocity = abhi.angular_velocity;
  
      srv.request.turtle1Position.x = turt1.x;
      srv.request.turtle1Position.y = turt1.y;
      srv.request.turtle1Position.theta = turt1.theta;
      srv.request.turtle1Position.linear_velocity = turt1.linear_velocity;
      srv.request.turtle1Position.angular_velocity = turt1.angular_velocity;

      if(client.call(srv))
	{
	  geometry_msgs::Twist vel;

	  vel.linear.x = srv.response.turtle1Velocity.linear.x;
	  vel.linear.y = srv.response.turtle1Velocity.linear.y;
	  vel.linear.z = srv.response.turtle1Velocity.linear.z;
	  vel.angular.x = srv.response.turtle1Velocity.angular.x;
	  vel.angular.y = srv.response.turtle1Velocity.angular.y;
	  vel.angular.z = srv.response.turtle1Velocity.angular.z;
  
	  pub.publish(vel);

	  ros::spinOnce();
	  loop_rate.sleep();
	}
    }
  
  return 0;
}
