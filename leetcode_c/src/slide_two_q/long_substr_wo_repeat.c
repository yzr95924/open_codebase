/**
 * @file long_substr_wo_repeat.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/longest-substring-without-repeating-characters
 * @version 0.1
 * @date 2023-08-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/slide_two_q.h"

#define MAX(a,b) (((a) >= (b)) ? (a) : (b))
void InsertChar(uint8_t *bitMap, char inputChar)
{
    int pos = (int)inputChar;
    bitMap[pos]++;
    return;
}

void RemoveChar(uint8_t *bitMap, char inputChar)
{
    int pos = (int)inputChar;
    bitMap[pos]--;
    return;
}

bool IsCurWindowExistDup(uint8_t *bitMap, char *s, int len)
{
    for (int idx = 0; idx < len; idx++) {
        int pos = (int)s[idx];
        if (bitMap[pos] > 1) {
            return true;
        }
    }
    return false;
}

int lengthOfLongestSubstring(char * s)
{
    int len = strlen(s);
    int leftBound = 0;
    int rightBound = 0;
    int ret = 1;
    uint8_t bitMap[128] = { 0 };

    if (len == 0) {
        return 0;
    }

    if (len == 1) {
        return 1;
    }

    leftBound = 0;
    rightBound = 0;
    InsertChar(bitMap, s[0]);
    while (rightBound < len ) {
        if (IsCurWindowExistDup(bitMap, &s[leftBound],
            rightBound - leftBound + 1)) {
            RemoveChar(bitMap, s[leftBound]);
            leftBound++;
        } else {
            ret = MAX(ret, rightBound - leftBound + 1);
            rightBound++;
            InsertChar(bitMap, s[rightBound]);
        }
    }

    return ret;
}
