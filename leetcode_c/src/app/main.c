#include <stdio.h>
#include "../../include/array/sub_sum_k.h"


int main(int argc, char* argv[]) {
    /* code */
    int inputArray[] = {1};
    int arrSize = sizeof(inputArray) / sizeof(int);
    int ret = subarraySum(inputArray, arrSize, 1);
    // printf("ret: %d\n", ret);
    return 0;
}