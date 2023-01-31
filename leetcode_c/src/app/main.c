#include <stdio.h>
#include "../../include/array/duplicate_zeros.h"

int main(int argc, char* argv[]) {
    /* code */
    int inputArray[] = {1,0,2,3,0,4,5,0};
    int arrSize = sizeof(inputArray) / sizeof(int);
    duplicateZeros(inputArray, arrSize);

    for (size_t i = 0; i < arrSize; i++) {
        printf("%d ", inputArray[i]);
    }
    printf("\n");

    return 0;
}