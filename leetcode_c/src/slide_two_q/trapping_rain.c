/**
 * @file trapping_rain.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/trapping-rain-water/
 * @version 0.1
 * @date 2023-08-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/slide_two_q.h"

#define MIN(a,b) (((a) <= (b)) ? (a) : (b))
#define MAX(a,b) (((a) >= (b)) ? (a) : (b))

int trap(int* height, int heightSize)
{
    int *leftMaxArr = (int*)calloc(sizeof(int), heightSize);
    int *rightMaxArr = (int*)calloc(sizeof(int), heightSize);
    int ret = 0;

    leftMaxArr[0] = height[0];
    for (int idx = 1; idx < heightSize; idx++) {
        leftMaxArr[idx] = MAX(height[idx], leftMaxArr[idx - 1]);
    }

    rightMaxArr[heightSize - 1] = height[heightSize - 1];
    for (int idx = heightSize - 2; idx >= 0; idx--) {
        rightMaxArr[idx] = MAX(height[idx], rightMaxArr[idx + 1]);
    }

    for (int idx = 0; idx < heightSize; idx++) {
        if (idx == 0 || idx == heightSize - 1) {
            continue;
        }
        int area = MIN(leftMaxArr[idx], rightMaxArr[idx]) - height[idx];
        if (area > 0) {
            ret += area;
        }
    }

    free(leftMaxArr);
    free(rightMaxArr);

    return ret;
}
