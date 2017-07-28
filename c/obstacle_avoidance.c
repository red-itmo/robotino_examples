#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <Com.h>
#include <Bumper.h>
#include <OmniDrive.h>
#include <DistanceSensor.h>


#define SOME_TIME 0.05


void sleep(double secs){
    clock_t start_time = clock();
    float time = 0.0;
    while(time < secs){
        time = ( clock() - (float)start_time ) / CLOCKS_PER_SEC;
    }
}


int main( int argc, char **argv ){

    ComId com;
    OmniDriveId omni;
    BumperId bumper;
    DistanceSensorId left_sensor, front_sensor, right_sensor;

    com = Com_construct();

    /*connect to robot with IP which was specified as program's command line
    argument or to 192.168.0.100 if no argument was provided*/
    if(argc > 1){
        Com_setAddress(com, argv[1]);
        printf( "Trying to connect to %s...\n", argv[1]);
    }
    else{
        Com_setAddress( com, "192.168.0.100" );
        printf( "Trying to connect to 192.168.0.100...\n");
    }

    //Checking for connection
    if(Com_connect(com)){
        printf( "Successfully connected!\n");
    }
    else{
        printf("Unable to connect! Program stopped.\n");
        return 0;
    }

    //connect devices with their handles
    omni = OmniDrive_construct();
    OmniDrive_setComId(omni, com);

    bumper = Bumper_construct();
    Bumper_setComId(bumper, com);

    front_sensor = DistanceSensor_construct(0);
    DistanceSensor_setComId(front_sensor, com);
    right_sensor = DistanceSensor_construct(8);
    DistanceSensor_setComId(right_sensor, com);
    left_sensor = DistanceSensor_construct(1);
    DistanceSensor_setComId(left_sensor, com);


    //loop until bumper be pressed
    float front, left, right;
    while(!Bumper_value(bumper)){

        front = DistanceSensor_voltage(front_sensor);
        right = DistanceSensor_voltage(right_sensor);
        left = DistanceSensor_voltage(left_sensor);

        /*if no obstacles in front of robot, go forward;
        else rotate in place*/
        if( (front < 0.65) && (right < 0.45) && (left  < 0.45) )
            OmniDrive_setVelocity(omni, 0.5, 0.0, 0.0);
        else
            OmniDrive_setVelocity(omni, 0.0, 0.0, 0.5);

        sleep(SOME_TIME);
    }

    printf("Bumper was pressed! Program stopped.\n");

    OmniDrive_destroy(omni);
    Bumper_destroy(bumper);
    Com_destroy(com);
    DistanceSensor_destroy(front_sensor);
    DistanceSensor_destroy(left_sensor);
    DistanceSensor_destroy(right_sensor);

    return 0;
}
