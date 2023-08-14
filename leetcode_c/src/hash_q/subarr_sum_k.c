/**
 * @file subarr_sum_k.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/subarray-sum-equals-k
 * @version 0.1
 * @date 2023-08-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/hash_q.h"
#include "../../../common_include/third_party/uthash.h"

typedef int ZUORU_HashData;

typedef struct {
    int hashKey;
    ZUORU_HashData hashVal;
    UT_hash_handle hh;
} ZUORU_HashTblIntItem;

ZUORU_HashTblIntItem** ZUORU_InitIntHashTbl()
{
    ZUORU_HashTblIntItem **hashTblPtr = (ZUORU_HashTblIntItem**)calloc(1,
        sizeof(ZUORU_HashTblIntItem*));
    *hashTblPtr = NULL;
    return hashTblPtr;
}

ZUORU_HashTblIntItem* ZUORU_InsertIntHashTbl(ZUORU_HashTblIntItem **hashTblPtr,
    int key, ZUORU_HashData *inVal)
{
    ZUORU_HashTblIntItem *tmpHashItem;

    HASH_FIND_INT(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        tmpHashItem = (ZUORU_HashTblIntItem*)calloc(1, sizeof(ZUORU_HashTblIntItem));
        tmpHashItem->hashKey = key;
        HASH_ADD_INT(*hashTblPtr, hashKey, tmpHashItem);
    }
    memcpy(&tmpHashItem->hashVal, inVal, sizeof(ZUORU_HashData));
    return tmpHashItem;
}

bool ZUORU_FindIntHashTbl(ZUORU_HashTblIntItem **hashTblPtr, int key,
    ZUORU_HashTblIntItem **ret)
{
    ZUORU_HashTblIntItem *tmpHashItem = NULL;
    HASH_FIND_INT(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        *ret = NULL;
        return false;
    }

    *ret = tmpHashItem;
    return true;
}

void ZUORU_DelIntHashTbl(ZUORU_HashTblIntItem **hashTblPtr,
    ZUORU_HashTblIntItem *hashItem)
{
    HASH_DEL(*hashTblPtr, hashItem);
    free(hashItem);
    return;
}

void ZUORU_FreeIntHashTbl(ZUORU_HashTblIntItem **hashTblPtr)
{
    ZUORU_HashTblIntItem *curItem;
    ZUORU_HashTblIntItem *tmpItem;

    HASH_ITER(hh, *hashTblPtr, curItem, tmpItem) {
        HASH_DEL(*hashTblPtr, curItem);
        free(curItem);
    }
    free(hashTblPtr);
    return;
}

int subarraySum(int* nums, int numsSize, int k)
{
    ZUORU_HashTblIntItem **hashTblPtr = ZUORU_InitIntHashTbl();
    int ret = 0;
    int curSum = 0;
    ZUORU_HashTblIntItem *tmpItem;
    ZUORU_HashData tmpData;

    tmpData = 1;
    ZUORU_InsertIntHashTbl(hashTblPtr, 0, &tmpData);
    for (int idx = 0; idx < numsSize; idx++) {
        curSum += nums[idx];
        if (ZUORU_FindIntHashTbl(hashTblPtr, curSum - k,
            &tmpItem)) {
            ret += tmpItem->hashVal;
        }
        if (ZUORU_FindIntHashTbl(hashTblPtr, curSum,
            &tmpItem)) {
            tmpItem->hashVal++;
        } else {
            tmpData = 1;
            ZUORU_InsertIntHashTbl(hashTblPtr, curSum, &tmpData);
        }
    }

    ZUORU_FreeIntHashTbl(hashTblPtr);

    return ret;
}
