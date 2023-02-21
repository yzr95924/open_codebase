#include "../../include/str/multiply_str.h"

int main(int argc, char* argv[]) {

    // int nums[] = {1, 2};
    // int numsSize = sizeof(nums) / sizeof(int);

    // int retSize;
    // int* retColumnSize;
    // int** retAns;
    char input1[] = "9";
    char input2[] = "99";

    char* ret;
    ret = multiply(input1, input2);
    printf("ret: %s\n", ret);

    free(ret);


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