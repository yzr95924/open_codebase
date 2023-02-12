#include "../../include/array/daily_temperature.h"

int main(int argc, char* argv[]) {
    /* code */
    // char version1[] = "1.0.1";
    // char version2[] = "1";

    // int ret = compareVersion(version1, version2);
    // printf("ret: %d\n", ret);
    // int posArray[] = {10,8,0,5,3};
    // int speedArray[] = {2,4,1,1,3};
    // int posSize = sizeof(posArray) / sizeof(int);
    // int speedSize = sizeof(speedArray) / sizeof(int);
    // int ret = carFleet(12, posArray, posSize, speedArray, speedSize);
    // printf("ret: %d\n", ret);

    int nums[] = {73,74,75,71,69,72,76,73};
    int arraySize = sizeof(nums) / sizeof(int);

    int retSize;
    int* ret = dailyTemperatures(nums, arraySize, &retSize);

    for (int i = 0; i < retSize; i++) {
        printf("%d\n", ret[i]);
    }

    free(ret);

    return 0;
}