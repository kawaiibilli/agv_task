#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <typeinfo>
#include "opencv/cv.h"
#include <math.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stack>
#include <queue>
#include <bits/stdc++.h>
#include "geometry_msgs/Point.h"

using namespace std;
using namespace cv;

Mat img;

typedef struct
{
  int ii;
  int jj;
}poin;

poin a;

void pathCallback(const geometry_msgs::Point::ConstPtr &msg)
{
  a.ii=(int)(msg->x);
  a.jj=(int)msg->y; 
  ROS_INFO("point received:[%d],[%d]",a.ii,a.jj);
  
  img.at<Vec3b>(a.ii,a.jj)[0]=255;
  img.at<Vec3b>(a.ii,a.jj)[1]=0;
  img.at<Vec3b>(a.ii,a.jj)[2]=0;

  imshow("mapped",img);
  
  waitKey(150);
}

int main(int argc, char **argv)
{
  img = imread("/home/swastik/catkin_ws/src/agv_task/src/ps1.png",CV_LOAD_IMAGE_COLOR);
  ros::init(argc,argv,"mapper");
  ros::NodeHandle n;
  ros::Subscriber sub=n.subscribe("path",3000,pathCallback);
  ros::spin();
  return 0;
}
