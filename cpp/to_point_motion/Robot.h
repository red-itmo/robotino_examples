#include <Com.h>
#include <Bumper.h>
#include <Odometry.h>
#include <OmniDrive.h>

using namespace rec::robotino::api2;

class Robot{
    Bumper bumper;
    Odometry odom;
    OmniDrive omni;
public:
    Robot(Com &com);
    void moveTo(float x, float y);
};
