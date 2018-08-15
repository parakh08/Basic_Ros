#include "ros/ros.h"
#include <stdio.h>
#include <math.h>
#include <sensor_msgs/NavSatFix.h>
#include <visualization_msgs/Marker.h>
//#include "std_msgs/String.h"
float a,b,x,y,z,l,m,p;
int flag=1;
ros::Publisher pub;
void chatterCallback(const sensor_msgs::NavSatFix::ConstPtr& msg)
{
  a=(3.14*msg->latitude)/180;
  b=(3.14*msg->longitude)/180;
  x=6371*cos(a)*cos(b);
  y=6371*cos(a)*sin(b);
  z=6371*sin(b);

  visualization_msgs::Marker marker;
    if(flag==1)
    {
      l=x;
      m=y;
      p=z;
      flag=0;
    } 
    if (flag==0)
    {
      marker.header.frame_id = "Hedwig";
      marker.header.stamp = ros::Time();
      marker.ns = "my_namespace";
      marker.id=0;
      marker.type = visualization_msgs::Marker::SPHERE;
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.z=(x-l)*1000;
      marker.pose.position.x=(y-m)*1000;
      marker.pose.position.y=(z-p)*500;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = 0.0;
      marker.pose.orientation.w = 1.0;
      marker.scale.x = 1;
      marker.scale.y = 0.1;
      marker.scale.z = 0.1;
      marker.color.a = 1.0; // Don't forget to set the alpha!
      marker.color.r = 0.0;
      marker.color.g = 1.0;
      marker.color.b = 0.0;
    }
       //marker.lifetime = ros::Duration();
    pub.publish(marker);
  //ROS_INFO("%f", a);
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("mavros/global_position/raw/fix", 1000, chatterCallback);
  pub = n.advertise<visualization_msgs::Marker>("coordinates", 1000);
  //ros::Rate loop_rate(10);
  ros::spin();
  //loop_rate.sleep();
  //ros::spin();
  return 0;
}