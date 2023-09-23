/**
 * @file jump_game_2.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/jump-game-ii/
 * @version 0.1
 * @date 2023-07-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/greedy_dp_q.h"

#define MAX(a,b) (((a) >= (b)) ? (a) : (b))

int jump_45(int* nums, int numsSize)
{
    int curMaxIdx = 0;
    int finalMaxIdx = 0;
    int endIdx = 0;
    int step = 0;

    for (int idx = 0; idx < numsSize - 1; idx++) {
        curMaxIdx = idx + nums[idx];
        finalMaxIdx = MAX(finalMaxIdx, curMaxIdx);
        if (idx == endIdx) {
            endIdx = finalMaxIdx;
            step++;
        }
    }

    return step;
}
