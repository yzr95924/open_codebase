/**
 * @file sub_sum_divisible.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/subarray-sums-divisible-by-k/
 * @version 0.1
 * @date 2023-02-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LEETCODE_SUB_SUM_DIVISIBLE_H
#define LEETCODE_SUB_SUM_DIVISIBLE_H

#include "../const.h"
#include "../third/uthash.h"

typedef struct {
    int remainder;
    int cnt;
    UT_hash_handle hh;
} HashMap_t;

HashMap_t* g_hashMap = NULL;

void AddItem(int remainder) {
    HashMap_t* curItem = NULL;
    HASH_FIND_INT(g_hashMap, &remainder, curItem);
    if (curItem == NULL) {
        curItem = (HashMap_t*)malloc(sizeof(HashMap_t));
        curItem->remainder = remainder;
        curItem->cnt = 1;
        HASH_ADD_INT(g_hashMap, remainder, curItem);
    } else {
        curItem->cnt++;
    }
    return ;
}

int CheckRemainder(int remainder) {
    HashMap_t* curItem = NULL;
    HASH_FIND_INT(g_hashMap, &remainder, curItem);
    if (curItem == NULL) {
        return 0;
    } else {
        return curItem->cnt;
    }
}

int subarraysDivByK(int* nums, int numsSize, int k){
    g_hashMap = NULL;
    AddItem(0); // init offset

    int ret = 0;
    int remainder = 0;
    int curSum = 0;
    for (int i = 0; i < numsSize; i++) {
        curSum += nums[i];
        remainder = (curSum % k + k) % k;
        ret += CheckRemainder(remainder);
        AddItem(remainder);
    }

    return ret;
}

#endif