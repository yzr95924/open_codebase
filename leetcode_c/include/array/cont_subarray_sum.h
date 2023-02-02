#ifndef LEETCODE_CONT_SUBARRAY_SUM_H
#define LEETCODE_CONT_SUBARRAY_SUM_H

#include "../const.h"
#include "../third/uthash.h"

typedef struct {
    int remainder; // remainder
    int firstPos; // first pos
    UT_hash_handle hh;
} HashMap_t;

HashMap_t* g_sumMap = NULL;

static void AddItem(int remainder, int curPos) {
    HashMap_t* curItem = NULL;
    HASH_FIND_INT(g_sumMap, &remainder, curItem);
    if (curItem == NULL) {
        curItem = (HashMap_t*)malloc(sizeof(HashMap_t));
        curItem->remainder = remainder;
        curItem->firstPos = curPos;
        HASH_ADD_INT(g_sumMap, remainder, curItem);
    }
    return ;
}

static bool CheckK(int k, int remainder, int curPos) {
    HashMap_t* findItem = NULL;
    HASH_FIND_INT(g_sumMap, &remainder, findItem);
    
    bool ret = false;
    if (findItem != NULL) {
        if (curPos - findItem->firstPos > 1) {
            ret = true;
        }
    }

    return ret;
}

static void ClearAll() {
    HashMap_t* curItem;
    HashMap_t* fakeItem;
    HASH_ITER(hh, g_sumMap, curItem, fakeItem) {
        HASH_DEL(g_sumMap, curItem);
        free(curItem);
    }
    return ;
}

bool checkSubarraySum(int* nums, int numsSize, int k){
    AddItem(0, -1);

    if (numsSize <= 1) {
        return false;
    }

    bool ret = false;
    int remainder = 0;
    for (int i = 0; i < numsSize; i++) {
        remainder = (remainder + nums[i]) % k;
        ret = CheckK(k, remainder, i);
        if (ret) {
            ClearAll();
            return ret;
        }
        AddItem(remainder, i);
    }

    ClearAll();
    return ret;
}

#endif