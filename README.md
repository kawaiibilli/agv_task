This is the code for plotting a path between the two points given points.
steps for running the code...

1.install opencv 2.4.9 on your computer if not already present. guide link(http://www.samontab.com/web/2014/06/installing-opencv-2-4-9-in-ubuntu-14-04-lts/)

2.install ROS INDIGO.

3.in your catkin workspace , clone this repository to the src folder.

4.open the sub.cpp and pub.cpp file in any text editor.

5.find the following line in those two codes(there should be total 3 lines): "/home/swastik/catkin_ws/src/agv_task/src/ps1.png"

6.replace the line with "/home/[your ubuntu user name]/[your catkin workspace name]/src/agv_task/src/ps1.png",

7.open the terminal,change directory to your catkin workspace and run "source devel/setup.bash".

8.run "catkin_make"

9.run "roscore"

10.run "rosrun agv_task mapper"

11.run "rosrun agv_task pointer"

NOTE:if you run the pointer node before mapper node, the line might start plotting from middle of the picture.
