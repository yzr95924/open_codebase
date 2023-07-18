/**
 * @file top_k_freq.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/top-k-frequent-elements
 * @version 0.1
 * @date 2023-07-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/app_sys_q.h"
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

typedef struct {
    int key;
    int freq;
} ZUORU_HeapDataItem;
typedef struct {
    ZUORU_HeapDataItem *heapItems;
    int capacity;
    int curSize;
    bool isMaxHeap;
} ZUORU_Heap;

int ZUORU_HeapGetParent(int curIdx)
{
    return (curIdx - 1) / 2;
}

int ZUORU_HeapGetLeftChild(int curIdx)
{
    return (curIdx * 2 + 1);
}

int ZUORU_HeapGetRightChild(int curIdx)
{
    return (curIdx * 2 + 2);
}

void ZUORU_SwapHeapItem(ZUORU_HeapDataItem *heapItems, int idx1, int idx2)
{
    ZUORU_HeapDataItem tmpItem;
    memcpy(&tmpItem, &heapItems[idx1], sizeof(ZUORU_HeapDataItem));
    memcpy(&heapItems[idx1], &heapItems[idx2], sizeof(ZUORU_HeapDataItem));
    memcpy(&heapItems[idx2], &tmpItem, sizeof(ZUORU_HeapDataItem));
    return;
}

ZUORU_Heap* ZUORU_InitHeap(int capacity, bool isMaxHeap)
{
    ZUORU_Heap *heapPtr = (ZUORU_Heap*)calloc(1, sizeof(ZUORU_Heap));
    heapPtr->heapItems = (ZUORU_HeapDataItem*)calloc(capacity, sizeof(ZUORU_HeapDataItem));
    heapPtr->capacity = capacity;
    heapPtr->isMaxHeap = isMaxHeap;
    heapPtr->curSize = 0;
    return heapPtr;
}

void ZUORU_FreeHeap(ZUORU_Heap *heapPtr)
{
    free(heapPtr->heapItems);
    free(heapPtr);
    return;
}

bool ZUORU_IsFullHeap(ZUORU_Heap *heapPtr)
{
    if (heapPtr->curSize == heapPtr->capacity) {
        return true;
    }
    return false;
}

bool ZUORU_IsEmptyHeap(ZUORU_Heap *heapPtr)
{
    if (heapPtr->curSize == 0) {
        return true;
    }
    return false;
}

bool ZUORU_ChkHeapParent(ZUORU_Heap *heapPtr, int parentIdx, int childIdx)
{
    if (heapPtr->isMaxHeap) {
        if (heapPtr->heapItems[parentIdx].freq > heapPtr->heapItems[childIdx].freq) {
            return true;
        } else {
            return false;
        }
    } else {
        if (heapPtr->heapItems[parentIdx].freq < heapPtr->heapItems[childIdx].freq) {
            return true;
        } else {
            return false;
        }
    }
    return true;
}

void ZUORU_InsertHeapImpl(ZUORU_Heap *heapPtr, int curIdx)
{
    int parentIdx = ZUORU_HeapGetParent(curIdx);
    if (!ZUORU_ChkHeapParent(heapPtr, parentIdx, curIdx) && (parentIdx != curIdx)) {
        ZUORU_SwapHeapItem(heapPtr->heapItems, parentIdx, curIdx);
        ZUORU_InsertHeapImpl(heapPtr, parentIdx);
    }

    return;
}

bool ZUORU_InsertHeap(ZUORU_Heap *heapPtr, ZUORU_HeapDataItem *inVal)
{
    if (ZUORU_IsFullHeap(heapPtr)) {
        fprintf(stderr, "heap is full\n");
        return false;
    }
    memcpy(&heapPtr->heapItems[heapPtr->curSize], inVal,
        sizeof(ZUORU_HeapDataItem));
    ZUORU_InsertHeapImpl(heapPtr, heapPtr->curSize);
    heapPtr->curSize++;

    return true;
}

void ZUORU_MakeHeap(ZUORU_Heap *heapPtr, int curIdx)
{
    int leftIdx = ZUORU_HeapGetLeftChild(curIdx);
    int rightIdx = ZUORU_HeapGetRightChild(curIdx);
    int targetIdx = curIdx;
    if (leftIdx >= heapPtr->curSize) {
        leftIdx = INT32_MIN;
    }
    if (rightIdx >= heapPtr->curSize) {
        rightIdx = INT32_MIN;
    }

    if (leftIdx != INT32_MIN && !ZUORU_ChkHeapParent(heapPtr, targetIdx, leftIdx)) {
        targetIdx = leftIdx;
    }
    if (rightIdx != INT32_MIN && !ZUORU_ChkHeapParent(heapPtr, targetIdx, rightIdx)) {
        targetIdx = rightIdx;
    }
    if (targetIdx != curIdx) {
        ZUORU_SwapHeapItem(heapPtr->heapItems, curIdx, targetIdx);
        ZUORU_MakeHeap(heapPtr, targetIdx);
    }

    return;
}

bool ZUORU_RemoveHeapTop(ZUORU_Heap *heapPtr, ZUORU_HeapDataItem *outVal)
{
    if (heapPtr->curSize == 0) {
        return false;
    }
    memcpy(outVal, &heapPtr->heapItems[0], sizeof(ZUORU_HeapDataItem));
    memcpy(&heapPtr->heapItems[0], &heapPtr->heapItems[heapPtr->curSize - 1],
        sizeof(ZUORU_HeapDataItem));
    heapPtr->curSize--;
    ZUORU_MakeHeap(heapPtr, 0);

    return true;
}

/**
 * @brief 347. Top K Frequent Elements
 *
 * @param nums input num array
 * @param numsSize array size
 * @param k
 * @param returnSize
 * @return int*
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize)
{
    ZUORU_HashTblIntItem **hashTbl = ZUORU_InitIntHashTbl();
    ZUORU_Heap *heapPtr = ZUORU_InitHeap(k, false);
    int *retArr = (int*)calloc(k, sizeof(int));
    *returnSize = k;

    for (int idx = 0; idx < numsSize; idx++) {
        ZUORU_HashTblIntItem *tmpItem;
        if (ZUORU_FindIntHashTbl(hashTbl, nums[idx], &tmpItem)) {
            tmpItem->hashVal++;
        } else {
            ZUORU_HashData tmpData = 1;
            ZUORU_InsertIntHashTbl(hashTbl, nums[idx], &tmpData);
        }
    }

    ZUORU_HashTblIntItem *curItem;
    ZUORU_HashTblIntItem *tmpItem;
    ZUORU_HeapDataItem tmpData;
    ZUORU_HeapDataItem outData;
    HASH_ITER(hh, *hashTbl, curItem, tmpItem) {
        tmpData.key = curItem->hashKey;
        tmpData.freq = curItem->hashVal;
        if (!ZUORU_IsFullHeap(heapPtr)) {
            ZUORU_InsertHeap(heapPtr, &tmpData);
        } else {
            if (tmpData.freq > heapPtr->heapItems[0].freq) {
                ZUORU_RemoveHeapTop(heapPtr, &outData);
                ZUORU_InsertHeap(heapPtr, &tmpData);
            }
        }
    }

    int curSize = heapPtr->curSize;
    for (int idx = 0; idx < curSize; idx++) {
        ZUORU_RemoveHeapTop(heapPtr, &outData);
        retArr[idx] = outData.key;
    }

    ZUORU_FreeIntHashTbl(hashTbl);
    ZUORU_FreeHeap(heapPtr);
    return retArr;
}
