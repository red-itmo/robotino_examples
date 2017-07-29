#include <stdio.h>
#include <Com.h>
#include "robot_functions.h"

int main( int argc, char **argv ){
    // connect to robot with IP which was specified as program's command
    // line argument or to 192.168.0.100 if no argument was provided
    ComId com;
    com = Com_construct();
    //setting of IP
    if(argc > 1){
        Com_setAddress(com, argv[1]);
        printf( "Trying to connect to %s...\n", argv[1]);
    }
    else{
        Com_setAddress(com, "192.168.0.100");
        printf( "Trying to connect to 192.168.0.100...\n");
    }
    //checking for connection
    if( Com_connect(com) ){
        printf( "Successfully connected!\n");
    }
    else{
        printf("Unable to connect! Program stopped.\n");
        return 0;
    }

    //robot initializations
    robotInit(com);

    //main program's loop
    int status;
    float goal_x, goal_y;
    while(true){
        printf("Specify coordinates of new goal point in meters:\n");
        printf("x = ");
        scanf("%f", &goal_x);
        printf("y = ");
        scanf("%f", &goal_y);
        printf("Robot is moving to (%f, %f) point...\n", goal_x, goal_y);

        status = robotMoveTo(goal_x, goal_y);
        if(status == 0){
            printf("Goal wasn't achieved due to bumper was pressed!\n");
                break;
        }
        printf("Goal was achieved!");
    }

    printf("Program stopped.");
    Com_destroy(com);
    return 0;
}
