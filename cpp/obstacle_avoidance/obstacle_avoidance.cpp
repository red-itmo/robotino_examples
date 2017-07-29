#include <ctime>
#include <iostream>

#include <Com.h>
#include <Bumper.h>
#include <OmniDrive.h>
#include <DistanceSensorArray.h>

#define SOME_TIME 0.05

using namespace rec::robotino::api2;


class MyDistanceSensorArray : public DistanceSensorArray {
public:
    bool detect_danger;
    MyDistanceSensorArray() { detect_danger = false; }
    void distancesChangedEvent( const float* distances, unsigned int size );
};


void MyDistanceSensorArray::distancesChangedEvent( const float* distances, unsigned int size ){
    //it there are some obstacles in front of robot, then danger_detected = true
    if( (distances[0] < 0.2) || (distances[1] < 0.3) || (distances[size-1] < 0.3) )
        detect_danger = true;
    else
        detect_danger = false;
}



void sleep(double secs){
    clock_t start_time = std::clock();
    float time = 0.0;
    while(time < secs){
        time = (std::clock() - (float)start_time) / CLOCKS_PER_SEC;
    }
}



int main(int argc, char **argv){

    Com com;
    MyDistanceSensorArray dist_sens;
    Bumper bumper;
    OmniDrive omni;

    /*connect to robot with IP which was specified as program's command line
    argument or to 192.168.0.100 if no argument was provided*/
    //setting IP
    if(argc > 1){
         com.setAddress(argv[1]);
         std::cout << "Trying to connect to " << argv[1] << "..." << std::endl;
    }
    else{
        com.setAddress("192.168.0.100");
        std::cout << "Trying to connect to 192.168.0.100..." << std::endl;
    }
    //try to connect
    try{
        com.connectToServer(true);
        std::cout << "Successfully connected!" << std::endl;
    }
    catch(...){
        std::cout << "Unable to connect! Program stopped." << std::endl;
        return 0;
    }

    //connect devices with their handles
    omni.setComId(com.id());
    bumper.setComId(com.id());
    omni.setComId(com.id());
    dist_sens.setComId(com.id());

    //loop until bumper be pressed
    while(!bumper.value()){
        com.processEvents();
        if(dist_sens.detect_danger){
            omni.setVelocity(0, 0, 0.5);
        }
        else{
            omni.setVelocity(0.5, 0, 0);
        }
        sleep(SOME_TIME);
    }

    std::cout << "Bumper was pressed! Program stopped." << std::endl;
    com.disconnectFromServer();
    return 0;
}
