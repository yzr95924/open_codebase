#include "../../include/backtrack/subsets.h"

int main(int argc, char* argv[]) {

    int nums[] = {1, 2};
    int numsSize = sizeof(nums) / sizeof(int);

    int retSize;
    int* retColumnSize;
    int** retAns;

    retAns = subsets(nums, numsSize, &retSize, &retColumnSize);

    for (int i = 0; i < retSize; i++) {
        printf("[ ");
        for (int j = 0; j < retColumnSize[i]; j++) {
            printf("%d ", retAns[i][j]);
        }
        printf(" ]\n");

        free(retAns[i]);
    }

    free(retColumnSize);
    free(retAns);

    return 0;
}