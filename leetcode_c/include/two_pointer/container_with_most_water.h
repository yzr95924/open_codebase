/**
 * @file container_with_most_water.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/container-with-most-water/?favorite=2cktkvj
 * @version 0.1
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_CONTAINER_WITH_MOST_WATER_H
#define LEETCODE_CONTAINER_WITH_MOST_WATER_H

#include "../const.h"

#define MIN(a,b) (((a) <= (b)) ? (a) : (b))
#define MAX(a,b) (((a) >= (b)) ? (a) : (b))

int maxArea(int* height, int heightSize)
{
    int rearIdx = 0;
    int frontIdx = heightSize - 1;
    int ret = 0;

    int curArea = 0;
    while (rearIdx != frontIdx) {
        int curMinHeight = MIN(height[rearIdx], height[frontIdx]);
        curArea = (frontIdx - rearIdx) * curMinHeight;
        ret = MAX(curArea, ret);

        if (height[rearIdx] < height[frontIdx]) {
            rearIdx++;
        } else {
            frontIdx--;
        }
    }

    return ret;
}

#endif