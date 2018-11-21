#include "Robot.h"
#include "SerialControl/SERIALRead.h"
Com com;
#define TIME_DELAY 0.05
#define Kspeed 0.1

int main(int argc, char **argv){
    std::setlocale(LC_ALL, "C");
    SERIALReader reader(argv[1],9600);
    if(argc > 1){
         com.setAddress(argv[2]);
         std::cout << "Trying to connect to " << argv[2] << "..." << std::endl;
    }
    else{
        com.setAddress("192.168.2.100");
        std::cout << "Trying to connect to 192.168.2.100..." << std::endl;
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
    float initx=0;
    float inity=0;
    float inita=0;
    float x=0;
    float y=0;
    float r=0;
    Robot robotino(com);
    vector<float> signal;
    sleep(2);
    cout<<"Initializing radio control"<<endl;
    signal=reader.getSignalForInterval();
    initx=signal[0];
    inity=signal[1];
    inita=signal[2];
    while(true){
      signal=reader.getSignalForInterval();
      if(robotino.getBumperState()){
        robotino.stop();
      }
      x=(signal[0]-initx)*Kspeed;
      y=(signal[1]-inity)*Kspeed;
      r=(signal[2]-inita)*Kspeed;
      // 0.13 -0.04 0.08
      robotino.moveWithVector(x,y,r);
      cout<< x<<" "<<y<<" "<<r<<endl;
      robotino.sleep(TIME_DELAY);
    }
    com.disconnectFromServer();
    return 0;
}
