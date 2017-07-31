## Content of the repository
The repository contains examples of two simple programs for
[Robotino](http://www.festo-didactic.com/int-en/learning-systems/education-and-research-robots-robotino/the-complete-robotino-package.htm?fbid=aW50LmVuLjU1Ny4xNy4xOC44NTguNDc1Ng)
which use [RobotinoAPI2](http://wiki.openrobotino.org/index.php?title=API2) library.
Each program has C and C++ realizations.

## Programs description
The first program is an *Obstacle avoidance*. It causes robot's forward motion until there are no obstacles in front of it.
When the latter meets an obstacle, it stops and starts rotate in place. As soon as any obstacles disappear from its view the robot stops its rotation and continues forward motion. For detecting obstacles three front distance sensors are used.

The second program (*To point motion*) does the folllowing. First of all it asks to enter coordinates of a goal point. Then it "delivers" robot to this point using simple control law. After that all processes are repeated. Coordinates for the goal point are specified in the initial robot frame. The origin of this frame is attached to the point where robot is located when program starts. Direction of its X-axis coincides with direction of robot's view. Y-axis goes from robot's center to its left side.

Both programs stop when Robotino's bumper is pressed.

## Building
For building repository's programs these commands can be used (DIRECTORY is a folder on your computer which contains robotino_examples repository; GNU GCC is used):
- Common steps
```bash
$ cd DIRECTORY/robotino_examples
$ mkdir build
$ cd build
```
- Obstacle avoidance (C)
```bash
$ g++ -I/usr/local/robotino/api2/include/rec/robotino/api2/c -I/usr/local/robotino/api2/include -c ../c/obstacle_avoidance/obstacle_avoidance.c -o obstacle_avoidance.o
$ g++ obstacle_avoidance.o /usr/local/robotino/api2/lib/librec_robotino_api2.so -o obstacle_avoidance
```
- Obstacle avoidance (C++)
```bash
$ g++ -I/usr/local/robotino/api2/include/rec/robotino/api2 -I/usr/local/robotino/api2/include -c ../cpp/obstacle_avoidance/obstacle_avoidance.cpp -o obstacle_avoidance.o
$ g++ obstacle_avoidance.o /usr/local/robotino/api2/lib/librec_robotino_api2.so -o obstacle_avoidance
```
- To point motion (C)
```bash
$ g++ -c ../common/sleep.c -o sleep.o
$ g++ -I/usr/local/robotino/api2/include/rec/robotino/api2/c -I/usr/local/robotino/api2/include -c ../c/to_point_motion/main.c ../c/to_point_motion/robot_functions.c
$ g++ main.o robot_functions.o sleep.o /usr/local/robotino/api2/lib/librec_robotino_api2.so -o to_point_motion
```
- To point motion (C++)
```bash
$ g++ -c ../common/sleep.c -o sleep.o
$ g++ -I/usr/local/robotino/api2/include/rec/robotino/api2 -I/usr/local/robotino/api2/include -c ../cpp/to_point_motion/main.cpp ../cpp/to_point_motion/Robot.cpp
$ g++ main.o Robot.o sleep.o /usr/local/robotino/api2/lib/librec_robotino_api2.so -o to_point_motion
```
