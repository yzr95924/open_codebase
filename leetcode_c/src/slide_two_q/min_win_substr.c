/**
 * @file min_win_substr.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/minimum-window-substring
 * @version 0.1
 * @date 2023-09-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/slide_two_q.h"
#include "../../../common_include/third_party/uthash.h"

typedef int ZUORU_HashData;
#define MIN(a,b) (((a) <= (b)) ? (a) : (b))

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

void UpdateHashTblWithChar(ZUORU_HashTblIntItem **hashTblPtr, char inputChar)
{
    ZUORU_HashTblIntItem *curItem = NULL;
    if (ZUORU_FindIntHashTbl(hashTblPtr, (int)inputChar, &curItem)) {
        curItem->hashVal++;
    } else {
        int tmpVal = 1;
        ZUORU_InsertIntHashTbl(hashTblPtr, (int)inputChar, &tmpVal);
    }
    return;
}

void RemoveHashTblWithChar(ZUORU_HashTblIntItem **hashTblPtr, char inputChar)
{
    ZUORU_HashTblIntItem *curItem = NULL;
    if (ZUORU_FindIntHashTbl(hashTblPtr, (int)inputChar, &curItem)) {
        curItem->hashVal--;
    }
    return;
}

bool IsContainSubstr(ZUORU_HashTblIntItem **sHashTblPtr, ZUORU_HashTblIntItem **tHashTblPtr)
{
    ZUORU_HashTblIntItem *sCurItem;
    ZUORU_HashTblIntItem *tmpItem;
    ZUORU_HashTblIntItem *tCurItem;
    bool isContainSubstr = true;

    HASH_ITER(hh, *tHashTblPtr, tCurItem, tmpItem) {
        if (ZUORU_FindIntHashTbl(sHashTblPtr, (int)tCurItem->hashKey, &sCurItem)) {
            if (sCurItem->hashVal < tCurItem->hashVal) {
                isContainSubstr = false;
                break;
            }
        } else {
            isContainSubstr = false;
            break;
        }
    }

    return isContainSubstr;
}

char *minWindow(char *s, char *t)
{
    ZUORU_HashTblIntItem **sHashTblPtr = ZUORU_InitIntHashTbl();
    ZUORU_HashTblIntItem **tHashTblPtr = ZUORU_InitIntHashTbl();

    int tStrLen = strlen(t);
    for (int idx = 0; idx < tStrLen; idx++) {
        UpdateHashTblWithChar(tHashTblPtr, t[idx]);
    }

    int minLen = INT32_MAX;
    int leftIdx = 0;
    int rightIdx = 0;
    int sStrLen = strlen(s);
    int minLeftIdx = 0;

    UpdateHashTblWithChar(sHashTblPtr, s[0]);
    while (rightIdx <= sStrLen - 1 && leftIdx <= rightIdx) {
        if (IsContainSubstr(sHashTblPtr, tHashTblPtr)) {
            int curLen = rightIdx - leftIdx + 1;
            if (curLen <= minLen) {
                minLen = curLen;
                minLeftIdx = leftIdx;
            }
            RemoveHashTblWithChar(sHashTblPtr, s[leftIdx]);
            leftIdx++;
        } else {
            rightIdx++;
            UpdateHashTblWithChar(sHashTblPtr, s[rightIdx]);
        }
    }

    ZUORU_FreeIntHashTbl(sHashTblPtr);
    ZUORU_FreeIntHashTbl(tHashTblPtr);

    if (minLen == INT32_MAX) {
        return (char*)calloc(1, sizeof(char));
    }

    char *ret = (char*)calloc(minLen + 1, sizeof(char));
    memcpy(ret, s + minLeftIdx, minLen);

    return ret;
}
