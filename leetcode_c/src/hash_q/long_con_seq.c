/**
 * @file long_con_seq.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/longest-consecutive-sequence
 * @version 0.1
 * @date 2023-08-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/hash_q.h"
#include "../../../common_include/third_party/uthash.h"

#define MAX(a,b) (((a) >= (b)) ? (a) : (b))
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

int longestConsecutive(int* nums, int numsSize)
{
    int ret = 0;
    ZUORU_HashTblIntItem **hashTblPtr = ZUORU_InitIntHashTbl();
    ZUORU_HashData tmpData = 0;
    for (int idx = 0; idx < numsSize; idx++) {
        ZUORU_InsertIntHashTbl(hashTblPtr, nums[idx], &tmpData);
    }

    ZUORU_HashTblIntItem *tmpItem;
    for (int idx = 0; idx < numsSize; idx++) {
        if (ZUORU_FindIntHashTbl(hashTblPtr, nums[idx] - 1, &tmpItem)) {
            continue;
        } else {
            int curFindVal = nums[idx] + 1;
            int curLength = 1;
            while (ZUORU_FindIntHashTbl(hashTblPtr, curFindVal, &tmpItem)) {
                curFindVal++;
                curLength++;
            }
            ret = MAX(ret, curLength);
        }
    }

    ZUORU_FreeIntHashTbl(hashTblPtr);
    return ret;
}
