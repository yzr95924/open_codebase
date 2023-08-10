/**
 * @file container_with_water.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/container-with-most-water
 * @version 0.1
 * @date 2023-08-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/slide_two_q.h"

#define MAX(a,b) (((a) >= (b)) ? (a) : (b))
#define MIN(a,b) (((a) <= (b)) ? (a) : (b))

int maxArea(int* height, int heightSize)
{
    int leftIdx = 0;
    int rightIdx = heightSize - 1;
    int ret = 0;
    int curArea = 0;

    while (leftIdx < rightIdx) {
        curArea = MIN(height[leftIdx], height[rightIdx]) *
            (rightIdx - leftIdx);
        ret = MAX(curArea, ret);

        if (height[leftIdx] < height[rightIdx]) {
            leftIdx++;
        } else {
            rightIdx--;
        }
    }

    return ret;
}
