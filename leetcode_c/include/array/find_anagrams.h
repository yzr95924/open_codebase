/**
 * @file find_anagrams.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/find-all-anagrams-in-a-string/
 * @version 0.1
 * @date 2023-02-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_FIND_ANAGRAMS_H
#define LEETCODE_FIND_ANAGRAMS_H

#define CHAR_DIFF_SIZE 26

#include "../const.h"

static bool checkAnagrams(char* str1, char* str2, int strSize) {
    int str1Map[CHAR_DIFF_SIZE] = {0};
    int str2Map[CHAR_DIFF_SIZE] = {0};

    // map a str to a map
    for (int i = 0; i < strSize; i++) {
        str1Map[(int)(str1[i] - 'a')] += 1;
        str2Map[(int)(str2[i] - 'a')] += 1;
    }

    // check whether two maps are same
    for (int i = 0; i < CHAR_DIFF_SIZE; i++) {
        if (str1Map[i] != str2Map[i]) {
            return false;
        }
    }

    return true;
}


int* findAnagrams(char* s, char* p, int* returnSize){
    int pLen = strlen(p);
    int sLen = strlen(s);

    int* ans = (int*)malloc(sizeof(int) * sLen);
    *returnSize = 0;

    if (pLen > sLen) {
        return ans;
    }


    char* rearPtr = s;
    int rearIdx = 0;
    char* frontPtr = s + (pLen - 1);
    int frontIdx = pLen - 1;

    while (frontIdx <= sLen - 1) {
        if (checkAnagrams(rearPtr, p, pLen)) {
            ans[*returnSize] = rearIdx;
            (*returnSize)++;
            // printf("find ans: %d\n", rearIdx);
        }
        rearPtr++;
        rearIdx++;
        frontPtr++;
        frontIdx++;
    }

    return ans;
}

#endif