#include "Robot.h"

Robot::Robot(Com &com){
  _com=com;
  _omni.setComId(_com.id());
  _bumper.setComId(_com.id());
  _odom.setComId(_com.id());
  _odom.set(0.0, 0.0, 0.0, true);
}

double &Robot::moveWithVector(double x, double y, double rotation){
  unsigned int seq=0;
  double cur_x, cur_y, cur_angle;

  if(_bumper.value()) throw std::string("Bumper was pressed!");
  _com.processEvents();
  _odom.readings(&cur_x, &cur_y, &cur_angle, &seq);
  _omni.setVelocity(x,y,rotation);
  _coords[0]=cur_x;
  _coords[1]=cur_y;
  _coords[2]=cur_angle;
  return *_coords;
}

void Robot::sleep(double secs){
  clock_t start_time = std::clock();
  float time = 0.0;
  while(time < secs){
      time = (std::clock() - (float)start_time) / CLOCKS_PER_SEC;
  }
}

void Robot::stop(){
  moveWithVector(0,0,0);
}
bool Robot::getBumperState(){
  return _bumper.value();
}
