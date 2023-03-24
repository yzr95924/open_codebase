#include "../../include/sorting/merge_intervals.h"

int main(int argc, char* argv[]) {

    int inputArray[][2] = {{1,4},{0,0}};
    int itemCnt = 2;

    int** inputArrayPtr = (int**)YZRConvertFixedTwoArrayToPtr((uint8_t*)&inputArray[0][0],
        itemCnt, 2, sizeof(int));

    int colSize[1] = {2};
    int retSize = 0;
    int* retColSize = NULL;
    int** retArray = merge(inputArrayPtr, itemCnt, colSize, &retSize, &retColSize);

    for (int i = 0; i < retSize; i++) {
        printf("{%d, %d} ", retArray[i][0], retArray[i][1]);
    }

    free(retColSize);
    for (int i = 0; i < itemCnt; i++) {
        free(retArray[i]);
    }
    free(retArray);

    YZRFreeFixedTwoArray((uint8_t**)inputArrayPtr, itemCnt);
    // Interval_T inputArray[2] = {{1,4}, {0,4}};

    // qsort(inputArray, 2, sizeof(Interval_T), CompFunc);

    // for (int i = 0; i < 2; i++) {
    //     printf("%d %d\n", inputArray[i].leftBound, inputArray[i].rightBound);
    // }

    return 0;
}