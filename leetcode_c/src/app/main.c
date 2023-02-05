#include "../../include/array/arith_slices.h"

int main(int argc, char* argv[]) {
    /* code */
    int inputArray[] = {1,2,3,8};
    int arrSize = sizeof(inputArray) / sizeof(int);
    int ret = numberOfArithmeticSlices(inputArray, arrSize);
    printf("ret: %d\n", ret);
    return 0;
}