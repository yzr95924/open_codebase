#include <stdio.h>
#include "../../include/number/two_sum.h"

int main(int argc, char* argv[]) {
    /* code */
    int input[4] = {2,7,11,15};
    int target = 9;
    int* retArray = NULL;
    int retSize = 0;
    retArray = twoSum(input, 4, target, &retSize);

    free(retArray);

    return 0;
}