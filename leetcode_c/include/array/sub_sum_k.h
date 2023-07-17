/**
 * @file sub_sum_k.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/subarray-sum-equals-k/
 * @version 0.1
 * @date 2023-02-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_SUB_SUM_H
#define LEETCODE_SUB_SUM_H

#include "../const.h"
#include "../third/uthash.h"

typedef struct {
    int prefixSum; // idx
    int cnt; // sum
    UT_hash_handle hh;
} HASH_MAP_T;

HASH_MAP_T* gSumMap = NULL;

void AddItem(int prefixSum, int cnt) {
    HASH_MAP_T* curItem = NULL;
    HASH_FIND_INT(gSumMap, &prefixSum, curItem);
    if (curItem == NULL) {
        curItem = (HASH_MAP_T*)malloc(sizeof(HASH_MAP_T));
        curItem->prefixSum = prefixSum;
        curItem->cnt = cnt;
        HASH_ADD_INT(gSumMap, prefixSum, curItem);
    } else {
        curItem->cnt++;
    }
    return;
}

static void ClearAll() {
    HASH_MAP_T* curItem;
    HASH_MAP_T* fakeItem;
    HASH_ITER(hh, gSumMap, curItem, fakeItem) {
        HASH_DEL(gSumMap, curItem);
        free(curItem);
    }
    return;
}

int subarraySum(int* nums, int numsSize, int k){
    // prefix sum + hash
    int prefixSum = 0;
    AddItem(prefixSum, 1);

    int count = 0;
    int curPrefixSum = 0;
    for (int i = 0; i < numsSize; i++) {
        curPrefixSum += nums[i];

        int targetPrefixSum = curPrefixSum - k;
        HASH_MAP_T* findItem = NULL;
        HASH_FIND_INT(gSumMap, &targetPrefixSum, findItem);
        if (findItem != NULL) {
            count += findItem->cnt;
        }

        AddItem(curPrefixSum, 1);
    }

    ClearAll();

    return count;
}

#endif