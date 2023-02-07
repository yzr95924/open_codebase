#include "../../include/sorting/car_fleet.h"

int main(int argc, char* argv[]) {
    /* code */
    int posArray[] = {10,8,0,5,3};
    int speedArray[] = {2,4,1,1,3};
    int posSize = sizeof(posArray) / sizeof(int);
    int speedSize = sizeof(speedArray) / sizeof(int);
    int ret = carFleet(12, posArray, posSize, speedArray, speedSize);
    printf("ret: %d\n", ret);
    return 0;
}