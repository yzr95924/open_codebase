/**
 * @file find_anagrams.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/find-all-anagrams-in-a-string
 * @version 0.1
 * @date 2023-08-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/slide_two_q.h"

bool IsTwoStrAnagrams(uint8_t *oldBitMap, uint8_t *newBitMap)
{
    for (int idx = 0; idx < 26; idx++) {
        if (oldBitMap[idx] != newBitMap[idx]) {
            return false;
        }
    }
    return true;
}

int* findAnagrams(char * s, char * p, int* returnSize)
{
    uint8_t oldBitMap[26] = { 0 };
    uint8_t newBitMap[26] = { 0 };
    int targetLen = strlen(p);
    int inputLen = strlen(s);
    int *retArr = (int*)calloc(sizeof(int), inputLen);
    int retAnsCnt = 0;

    if (inputLen < targetLen) {
        *returnSize = retAnsCnt;
        return retArr;
    }

    for (int idx = 0; idx < targetLen; idx++) {
        int pos = p[idx] - 'a';
        oldBitMap[pos]++;
    }

    for (int idx = 0; idx < targetLen; idx++) {
        int pos = s[idx] - 'a';
        newBitMap[pos]++;
    }

    int leftIdx = 0;
    int rightIdx = targetLen - 1;
    while (rightIdx < inputLen) {
        if (IsTwoStrAnagrams(oldBitMap, newBitMap)) {
            retArr[retAnsCnt] = leftIdx;
            retAnsCnt++;
        }
        int pos = s[leftIdx] - 'a';
        newBitMap[pos]--;
        leftIdx++;

        rightIdx++;
        if (rightIdx == inputLen) {
            break;
        }
        pos = s[rightIdx] - 'a';
        newBitMap[pos]++;
    }

    *returnSize = retAnsCnt;
    return retArr;
}
