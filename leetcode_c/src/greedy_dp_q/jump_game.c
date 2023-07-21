/**
 * @file jump_game.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/jump-game/
 * @version 0.1
 * @date 2023-07-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/greedy_dp_q.h"

#define MIN(a,b) (((a) <= (b)) ? (a) : (b))
#define MAX(a,b) (((a) >= (b)) ? (a) : (b))

bool canJump(int* nums, int numsSize)
{
    int finalMaxPos = 0;
    int curMaxPos = 0;
    for (int idx = 0; idx < numsSize; idx++) {
        curMaxPos = idx + nums[idx];
        finalMaxPos = MAX(finalMaxPos, curMaxPos);
        if (finalMaxPos < idx + 1) {
            break;
        }
    }

    if (finalMaxPos >= numsSize - 1) {
        return true;
    } else {
        return false;
    }
}
