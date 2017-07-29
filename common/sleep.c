#include <time.h>

void sleep(double secs){
    clock_t start_time = clock();
    float waiting_time = 0.0;
    while(waiting_time < secs){
        waiting_time = (clock() - (float)start_time) / CLOCKS_PER_SEC;
    }
}
