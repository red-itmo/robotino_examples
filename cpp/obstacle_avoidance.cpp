#include <ctime>
#include <iostream>

#include <Com.h>
#include <Bumper.h>
#include <OmniDrive.h>
#include <RobotinoException.h>
#include <DistanceSensorArray.h>

#define SOME_TIME 0.05

using namespace rec::robotino::api2;


class MyCom : public Com{
public:
    MyCom(const char *name) : Com(name){ }
    bool connectTo(const char *ip);
};


bool MyCom::connectTo(const char *ip){

    setAddress(ip);
    std::cout << "Trying to connect with " << ip << "..." <<std::endl;

    //try connect to Robotino with IP=ip
    try{
        connectToServer(true);
        std::cout << "Successfully connected!" << std::endl;
    }
    catch(...){
        std::cout << "Unable to connect! Program stopped." << std::endl;
        return false;
    }

    return true;
}



class MyBumper: public Bumper{
public:
    bool touched;
    MyBumper(){ touched = false; }
    void bumperEvent( bool has_contact ) { touched = has_contact;}
};



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

    MyCom com("first_client");
    MyDistanceSensorArray dist_sens;
    MyBumper bumper;
    OmniDrive omni;

    /*connect to robot with IP which was specified as program's command line
    argument or to 192.168.0.100 if no argument was provided*/
    if(argc > 1){
         if( !com.connectTo(argv[1]) )
            return 0;
    }
    else{
        if( !com.connectTo("192.168.1.100") )
            return 0;
    }

    //connect devices with their handles
    omni.setComId(com.id());
    bumper.setComId(com.id());
    omni.setComId(com.id());
    dist_sens.setComId(com.id());

    while(!bumper.touched){
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
