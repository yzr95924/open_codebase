#include "../../include/str/my_atoi.h"

int main(int argc, char* argv[]) {

    // int nums[] = {1, 2};
    // int numsSize = sizeof(nums) / sizeof(int);

    // int retSize;
    // int* retColumnSize;
    // int** retAns;

    char retAns[] = "2147483646";
    int ret;
    ret = myAtoi(retAns);
    printf("ret: %d\n", ret);

    // retAns = combine(3, 2, &retSize, &retColumnSize);

    // int retSize = 0;
    // char** retAns = generateParenthesis(1, &retSize);

    // printf("retSize: %d\n", retSize);
    // for (int i = 0; i < retSize; i++) {
    //     printf("%s\n", retAns[i]);
    //     free(retAns[i]);
    // }

    // // free(retColumnSize);
    // free(retAns);

    return 0;
}