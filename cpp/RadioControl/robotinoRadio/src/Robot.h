#ifndef ROBOT_H
#define ROBOT_H

#define MAXLINSPEED 2;
#define MAXANGSPEED 2;

#include <Com.h>
#include <Bumper.h>
#include <Odometry.h>
#include <OmniDrive.h>

// #include <rec/robotino/api2/Com.h>
// #include <rec/robotino/api2/Bumper.h>
// #include <rec/robotino/api2/OmniDrive.h>
// #include <rec/robotino/api2/Odometry.h>
#include <ctime>
#include <iostream>
#include <stdio.h>

using namespace rec::robotino::api2;

class Robot{
public:
  Robot(Com &com);
  double &moveWithVector(double x, double y, double rotation);
  void sleep(double secs);
  bool getBumperState();
  void stop();
private:
  Com _com;
  Bumper _bumper;
  OmniDrive _omni;
  Odometry _odom;
  double _coords[3];
};

#endif /*ROBOT_H*/
