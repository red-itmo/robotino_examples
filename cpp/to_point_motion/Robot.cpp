#include <cmath>
#include "Robot.h"

#define K 0.1
#define LIMIT 0.1
#define SOME_TIME 0.05

void sleep(double secs);


Robot::Robot(Com &com){
    //connect devices with their handles
    omni.setComId(com.id());
    odom.setComId(com.id());
    bumper.setComId(com.id());
    //reset odometry
    odom.set(0.0, 0.0, 0.0, true);
}


void Robot::moveTo(float x, float y){
    unsigned int seq;
    double vel_x, vel_y;
    double cur_x, cur_y, cur_angle;

    odom.readings(&cur_x, &cur_y, &cur_angle, &seq);
    while( pow(x - cur_x, 2) + pow(y - cur_y, 2) > pow(LIMIT,2) ){
        //check bumper's state
        if(bumper.value())
            throw std::string("Bumper was pressed!");
        //motion control
        vel_x = K * (x - cur_x);
        vel_y = K * (y - cur_y);
        omni.setVelocity(vel_x, vel_y, 0.0);
        sleep(SOME_TIME);
        odom.readings(&cur_x, &cur_y, &cur_angle, &seq);
    }
}
