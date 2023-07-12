/**
 * @file two_sum.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/two-sum/
 * @version 0.1
 * @date 2023-07-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/math_q.h"
#include "../../../common_include/c_include.h"
#include "../../../common_include/third_party/uthash.h"

typedef int ZUORU_HashData;

typedef struct {
    int hashKey;
    ZUORU_HashData hashVal;
    UT_hash_handle hh;
} ZUORU_HashTblIntItem;

/**
 *********************************************
 ***               for int key hash table
 *********************************************
 */

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

/**
 * @brief 1. Two Sum
 *
 * @param nums input array
 * @param numsSiz input array size
 * @param target target number
 * @param returnSize return size
 * @return int* return array
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    int *retArray = (int*)calloc(2, sizeof(int));
    *returnSize = 2;
    ZUORU_HashTblIntItem **gHashTbl = ZUORU_InitIntHashTbl();
    int remain = 0;
    bool isFind = false;
    ZUORU_HashTblIntItem *tmpItemPtr = NULL;

    for (int idx = 0; idx < numsSize; idx++) {
        remain = target - nums[idx];
        isFind = ZUORU_FindIntHashTbl(gHashTbl, remain, &tmpItemPtr);
        if (isFind) {
            retArray[0] = tmpItemPtr->hashVal;
            retArray[1] = idx;
            break;
        }
        ZUORU_InsertIntHashTbl(gHashTbl, nums[idx], &idx);
    }
    ZUORU_FreeIntHashTbl(gHashTbl);

    return retArray;
}
