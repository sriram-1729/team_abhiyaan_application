#include "ros/ros.h"
#include "beginner_tutorials/Turtle1.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <math.h>

#define PI 3.1415926

turtlesim::Pose abhiyaan_position;
turtlesim::Pose turtle_position;
geometry_msgs::Twist velocity;

namespace turtle_exercise
{

  bool determineVelocity()
  {
    float distance = sqrt(pow(abhiyaan_position.x - turtle_position.x, 2) + pow(abhiyaan_position.y - turtle_position.y, 2));
    float speed = 2;
  
    while(distance > 2)
      {
	float angle = asin((abhiyaan_position.y - turtle_position.y) / sqrt(pow((abhiyaan_position.x - turtle_position.x), 2) + pow((abhiyaan_position.y - turtle_position.y), 2)));
	if ((abhiyaan_position.x - turtle_position.x < 0) && (abhiyaan_position.y - turtle_position.y > 0))
	  angle = PI - angle;
	else if((abhiyaan_position.x - turtle_position.x < 0) && (abhiyaan_position.y - turtle_position.y < 0))
	  angle = PI - angle;
	else if((abhiyaan_position.x - turtle_position.x > 0) && (abhiyaan_position.y - turtle_position.y < 0)) 
	  angle = 2 * PI + angle;
	while((turtle_position.theta >= angle + 0.1) || (turtle_position.theta <= angle - 0.1))
	  {
	    velocity.angular.z = 1;
	    return true;
	  }
      
	velocity.linear.z = velocity.angular.x = velocity.angular.y = velocity.angular.z = 0;

	velocity.linear.x = speed * cos(turtle_position.theta);
	velocity.linear.y = speed * sin(turtle_position.theta);
      
	return true;
      }

    velocity.linear.x = velocity.linear.y = velocity.angular.z = 0;
  
    return true;
  }

  void copyAbhiyaanPosition(const turtlesim::Pose& duplicate_abhiyaan_position)
  {
    abhiyaan_position.x = duplicate_abhiyaan_position.x;
    abhiyaan_position.y = duplicate_abhiyaan_position.y;
    abhiyaan_position.theta = duplicate_abhiyaan_position.theta;
    abhiyaan_position.linear_velocity = duplicate_abhiyaan_position.linear_velocity;
    abhiyaan_position.angular_velocity = duplicate_abhiyaan_position.angular_velocity;
  }

  void copyTurtlePosition(const turtlesim::Pose& duplicate_turtle_position)
  {
    turtle_position.x = duplicate_turtle_position.x;
    turtle_position.y = duplicate_turtle_position.y;
    turtle_position.theta = duplicate_turtle_position.theta;
    turtle_position.linear_velocity = duplicate_turtle_position.linear_velocity;
    turtle_position.angular_velocity = duplicate_turtle_position.angular_velocity;
  }

} // namespace turtle_exercise

int main(int argc, char** argv)
{
  ros::init(argc, argv, "turtle1_client");
  ros::NodeHandle node_handle;

  ros::Subscriber subscriber1 = node_handle.subscribe("abhiyaan/pose", 100, turtle_exercise::copyAbhiyaanPosition);

  ros::Subscriber subscriber2 = node_handle.subscribe("turtle1/pose", 100, turtle_exercise::copyTurtlePosition);

  ros::Publisher publisher1 = node_handle.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 100);
  ros::Rate loop_rate(10);

  while(ros::ok())
    {
      turtle_exercise::determineVelocity();
      
      publisher1.publish(velocity);

      ros::spinOnce();
      loop_rate.sleep(); 
    }
  
  return 0;
}
