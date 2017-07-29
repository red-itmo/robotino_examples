#include <math.h>

#include <Com.h>
#include <Bumper.h>
#include <Odometry.h>
#include <OmniDrive.h>

#define K 0.1
#define LIMIT 0.1
#define SOME_TIME 0.05

void sleep(double secs);


OdometryId odom;
BumperId bumper;
OmniDriveId omni;


void robotInit(ComId com){
    //connect devices with their handles
    odom = Odometry_construct();
    bumper = Bumper_construct();
    omni = OmniDrive_construct();
    Odometry_setComId(odom, com);
    Bumper_setComId(bumper, com);
    OmniDrive_setComId(omni, com);
    //reset odometry
    Odometry_set(odom, 0.0, 0.0, 0.0);
}


int robotMoveTo(float x, float y){
    float vel_x, vel_y;
    float cur_x, cur_y;

    cur_x = Odometry_x(odom);
    cur_y = Odometry_y(odom);
    while( pow(x - cur_x, 2) + pow(y - cur_y, 2) > pow(LIMIT,2) ){
        //check bumper's state
        if(Bumper_value(bumper))
            return 0;
        //motion control
        vel_x = K * (x - cur_x);
        vel_y = K * (y - cur_y);
        OmniDrive_setVelocity(omni, vel_x, vel_y, 0.0);
        sleep(SOME_TIME);
        cur_x = Odometry_x(odom);
        cur_y = Odometry_y(odom);
    }

    return 1;
}
