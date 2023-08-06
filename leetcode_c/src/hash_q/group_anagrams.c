/**
 * @file group_anagrams.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/group-anagrams
 * @version 0.1
 * @date 2023-08-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/hash_q.h"
#include "../../../common_include/third_party/uthash.h"

typedef int ZUORU_HashData;
#define MAX_HASH_KEY_SIZE 100

int ZUORU_CompFunc(const void *rawInput1, const void *rawInput2)
{
    char *input1 = (char*)rawInput1;
    char *input2 = (char*)rawInput2;
    int ret = *input1 - *input2; // ascend

    return ret;
}

typedef struct {
    char hashKey[MAX_HASH_KEY_SIZE];
    ZUORU_HashData hashVal;
    UT_hash_handle hh;
} ZUORU_HashTblStrItem;

ZUORU_HashTblStrItem** ZUORU_InitStrHashTbl()
{
    ZUORU_HashTblStrItem **hashTblPtr = (ZUORU_HashTblStrItem**)calloc(1,
        sizeof(ZUORU_HashTblStrItem*));
    *hashTblPtr = NULL;
    return hashTblPtr;
}

void ZUORU_InsertStrHashTbl(ZUORU_HashTblStrItem **hashTblPtr, const char *key,
    ZUORU_HashData *inVal)
{
    ZUORU_HashTblStrItem *tmpHashItem = NULL;
    HASH_FIND_STR(*hashTblPtr, key, tmpHashItem);
    if (tmpHashItem == NULL) {
        tmpHashItem = (ZUORU_HashTblStrItem*)calloc(1, sizeof(ZUORU_HashTblStrItem));
        strcpy(tmpHashItem->hashKey, key);
        HASH_ADD_STR(*hashTblPtr, hashKey, tmpHashItem);
    }
    memcpy(&tmpHashItem->hashVal, inVal, sizeof(ZUORU_HashData));
    return;
}

bool ZUORU_FindStrHashTbl(ZUORU_HashTblStrItem **hashTblPtr, const char *key,
    ZUORU_HashTblStrItem **ret)
{
    ZUORU_HashTblStrItem *tmpHashItem = NULL;
    HASH_FIND_STR(*hashTblPtr, key, tmpHashItem);
    if (tmpHashItem == NULL) {
        *ret = NULL;
        return false;
    }

    *ret = tmpHashItem;
    return true;
}

void ZUORU_DelStrHashTbl(ZUORU_HashTblStrItem **hashTblPtr,
    ZUORU_HashTblStrItem *hashItem)
{
    HASH_DEL(*hashTblPtr, hashItem);
    free(hashItem);
    return;
}

void ZUORU_FreeStrHashTbl(ZUORU_HashTblStrItem **hashTblPtr)
{
    ZUORU_HashTblStrItem *curItem;
    ZUORU_HashTblStrItem *tmpItem;

    HASH_ITER(hh, *hashTblPtr, curItem, tmpItem) {
        HASH_DEL(*hashTblPtr, curItem);
        free(curItem);
    }
    free(hashTblPtr);
    return;
}

bool IsNewStr(ZUORU_HashTblStrItem **hashTblPtr, const char *inputStr, int curCnt,
    int *outCnt)
{
    ZUORU_HashTblStrItem curItem = { 0 };
    ZUORU_HashTblStrItem *tmpItem = NULL;
    int len = strlen(inputStr);
    memcpy(curItem.hashKey, inputStr, len);
    qsort(curItem.hashKey, len, sizeof(char), ZUORU_CompFunc);

    if (ZUORU_FindStrHashTbl(hashTblPtr, curItem.hashKey,
        &tmpItem)) {
        *outCnt = tmpItem->hashVal;
        return false;
    } else {
        ZUORU_InsertStrHashTbl(hashTblPtr, curItem.hashKey, &curCnt);
        *outCnt = curCnt;
    }

    return true;
}

char ***groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes)
{
    int uniqueCnt = 0;
    int outCnt = 0;
    ZUORU_HashTblStrItem **hashTblPtr = ZUORU_InitStrHashTbl();
    int strCnt[10000] = { 0 };
    int cntMap[10000] = { 0 };
    char ***retStrArr;

    for (int idx = 0; idx < strsSize; idx++) {
        if (IsNewStr(hashTblPtr, strs[idx], uniqueCnt, &outCnt)) {
            strCnt[outCnt]++;
            uniqueCnt++;
        } else {
            strCnt[outCnt]++;
        }
        cntMap[idx] = outCnt;
    }

    *returnSize = uniqueCnt;
    *returnColumnSizes = (int*)calloc(uniqueCnt, sizeof(int));
    retStrArr = (char***)calloc(uniqueCnt, sizeof(char**));
    for (int idx = 0; idx < uniqueCnt; idx++) {
        retStrArr[idx] = (char**)calloc(strCnt[idx], sizeof(char*));
        for (int strIdx = 0; strIdx < strCnt[idx]; strIdx++) {
            retStrArr[idx][strIdx] = (char*)calloc(100, sizeof(char));
        }
        (*returnColumnSizes)[idx] = strCnt[idx];
    }

    int curArrCnt = 0;
    for (int idx = 0; idx < uniqueCnt; idx++) {
        curArrCnt = 0;
        for (int curStrIdx = 0; curStrIdx < strsSize; curStrIdx++) {
            if (cntMap[curStrIdx] == idx) {
                memcpy(retStrArr[idx][curArrCnt], strs[curStrIdx], strlen(strs[curStrIdx]));
                curArrCnt++;
            }
        }
    }

    ZUORU_FreeStrHashTbl(hashTblPtr);
    return retStrArr;
}
