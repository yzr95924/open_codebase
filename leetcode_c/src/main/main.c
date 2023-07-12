/**
 * @file main.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief the main process
 * @version 0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../../common_include/my_log.h"
#include "./../../common_include/define_const.h"
#include "../../include/app_sys_q.h"
#include "../../include/bfs_q.h"
#include "../../include/math_q.h"

#define MODULE_ID "LeetCodeMain"

int main(int argc, char* argv[]) {

    int inputArr[] = {2, 7, 11, 15};
    int target = 9;
    int retSize;
    int inputSize = ARRAY_SIZE(inputArr);
    int *ret = NULL;

    ret = twoSum(inputArr, inputSize, target, &retSize);

    free(ret);
    return 0;
}