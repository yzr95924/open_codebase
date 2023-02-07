/**
 * @file get_equal_sub_str.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/get-equal-substrings-within-budget/
 * @version 0.1
 * @date 2023-02-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_GET_EQUAL_SUB_STR_H
#define LEETCODE_GET_EQUAL_SUB_STR_H

#include "../const.h"

int equalSubstring(char * s, char * t, int maxCost){
    int strSize = strlen(s);

    int leftIdx = 0;
    int rightIdx = 0;

    int curCost = 0;
    int retVal = 0;
    curCost = abs(s[0] - t[0]);
    while (rightIdx < strSize) {
        if (curCost > maxCost) {
            if (rightIdx == leftIdx) {
                rightIdx++;
                leftIdx++;
                curCost = abs(s[rightIdx] - t[rightIdx]);
            } else {
                curCost -= abs(s[leftIdx] - t[leftIdx]);
                leftIdx++;
            }
        } else {
            int curLen = rightIdx - leftIdx + 1;
            retVal = MAX(retVal, curLen);
            rightIdx++;
            if (rightIdx == strSize) {
                break;
            } else {
                curCost += abs(s[rightIdx] - t[rightIdx]);
            }
        }  
    }

    return retVal;
}

#endif