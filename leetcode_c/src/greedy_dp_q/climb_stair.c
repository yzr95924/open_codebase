/**
 * @file climb_stair.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/climbing-stairs
 * @version 0.1
 * @date 2023-07-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/greedy_dp_q.h"

int climbStairs(int n)
{
    int ret = 0;
    if (n == 1) {
        return 1;
    }
    int *stairArr = (int*)calloc(n + 1, sizeof(int));
    stairArr[1] = 1;
    stairArr[2] = 2;
    for (int idx = 3; idx <= n; idx++) {
        stairArr[idx] = stairArr[idx - 1] + stairArr[idx - 2];
    }
    ret = stairArr[n];
    free(stairArr);
    return ret;
}