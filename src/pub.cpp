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

void bfs(int,int,int,int);
typedef struct
{
  int ii;
  int jj;
}poin;

poin **visited;
int main(int argc,char **argv)
{
  ros::init(argc,argv,"pointer");
  ros::NodeHandle n;

  ros::Publisher path_pub=n.advertise<geometry_msgs::Point>("path",3000);

  ros::Rate loop_rate(10);
  
  img = imread("/home/swastik/catkin_ws/src/agv_task/src/ps1.png",CV_LOAD_IMAGE_COLOR);
    int gci,gcj,rci,rcj,i,j;

    visited=(poin **)malloc(img.rows*sizeof(poin *));

    for(i=0;i<img.rows;i++)
	{
	  *(visited+i)=(poin *)malloc(img.cols*sizeof(poin));
        }


    int gmaxj=0,gminj=img.cols,gmaxi=0,gmini=img.rows,rmaxj=0,rminj=img.cols,rmaxi=0,rmini=img.cols;
    Mat im=imread("/home/swastik/catkin_ws/src/agv_task/src/ps1.png",CV_LOAD_IMAGE_COLOR);

  for(i=0;i<img.rows;i++)
    {
      for(j=0;j<img.cols;j++)
	{
	  if((img.at<Vec3b>(i,j)[0]<80) && (img.at<Vec3b>(i,j)[1]>100) && (img.at<Vec3b>(i,j)[2]<80))
	    {
	      if(gmaxj<j)
		gmaxj=j;
	      if(gminj>j)
		gminj=j;

	      if(gmaxi<i)
		gmaxi=i;
	      if(gmini>i)
		gmini=i;
	    }

	  if((img.at<Vec3b>(i,j)[0]<80) && (img.at<Vec3b>(i,j)[1]<80) && (img.at<Vec3b>(i,j)[2]>170))
	    {
	      if(rmaxj<j)
		rmaxj=j;
	      if(rminj>j)
		rminj=j;

	      if(rmaxi<i)
		rmaxi=i;
	      if(rmini>i)
		rmini=i;
	    }
	}
    }
  rci=(rmaxi+rmini)/2;
  rcj=(rmaxj+rminj)/2;

  gci=(gmaxi+gmini)/2;
  gcj=(gmaxj+gminj)/2;

  img.at<Vec3b>(rci,rcj)[0]=255;
  img.at<Vec3b>(rci,rcj)[1]=0;
  img.at<Vec3b>(rci,rcj)[2]=0;

  img.at<Vec3b>(gci,gcj)[1]=0;
  img.at<Vec3b>(gci,gcj)[2]=0;
  img.at<Vec3b>(gci,gcj)[0]=255;

  bfs(rci,rcj,gci,gcj);
  poin s;
  s.ii=rci;
  s.jj=rcj;

  poin temp;
  temp.ii=gci;
  temp.jj=gcj;

  poin abc[1000];
  int siz=0,temps=0;

  while(1)
    {
      im.at<Vec3b>(temp.ii,temp.jj)[0]=255;
      abc[temps++]=temp;
      siz++;      
	if(temp.ii==s.ii && temp.jj==s.jj)
        {
	  abc[temps++]=temp;
	  siz++;
 	  break;
        }
      temp=visited[temp.ii][temp.jj];
     }

  //imshow("changed",im);
  //imshow("orginal",img);
  waitKey(1000);

  siz--;
  
  int k=0;
  while(ros::ok())
    {
      geometry_msgs::Point tt;
      tt.x=abc[k].ii;
      tt.y=abc[k++].jj;

      if(k>=siz)
      k=0;

      ROS_INFO("point sent:[%f,%f]",tt.x,tt.y);
      path_pub.publish(tt);
      ros::spinOnce();
      loop_rate.sleep();
    }
  return 0;
  }

void bfs(int si,int sj,int fi,int fj)
{

  int i,j,f=0,a,b;
  for(i=0;i<img.rows;i++)
    {
      for(j=0;j<img.cols;j++)
	{
	  visited[i][j].ii=0;
	  visited[i][j].jj=0;
	}
    }

  queue <poin> q;

  poin tmp,tmp2;

  tmp.ii=si;
  tmp.jj=sj;

  q.push(tmp);

  while(1)
    {
      tmp=q.front();

      q.pop();
		  
      for(a=-1;a<2;a++)
	{
	  for(b=-1;b<2;b++)
	    {
	      if(a!=0 || b!=0)
		{
		  if(tmp.ii>0 && tmp.ii<img.rows-1 && tmp.jj>0 && tmp.jj<img.cols-1)
		    {
		      if(visited[a+tmp.ii][b+tmp.jj].ii==0 && visited[a+tmp.ii][b+tmp.jj].jj==0)
			{
			  visited[a+tmp.ii][b+tmp.jj]=tmp;
			  tmp2.ii=a+tmp.ii;
			  tmp2.jj=b+tmp.jj;

			  if((img.at<Vec3b>(tmp2.ii,tmp2.jj)[0]<70) || (img.at<Vec3b>(tmp2.ii,tmp2.jj)[1]<70) || (img.at<Vec3b>(tmp2.ii,tmp2.jj)[2]<70))
			    {
			  q.push(tmp2);
			  
			    }	      
			  if(tmp2.ii==fi && tmp2.jj==fj)
			    {
			      f=1;
			      break;
			    }
			}
		    }
		}
	    }
	}

      if(f==1)
	break;
    }
}
