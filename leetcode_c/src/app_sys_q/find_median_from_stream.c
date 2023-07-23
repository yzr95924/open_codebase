/**
 * @file find_median_from_stream.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief
 * @version 0.1
 * @date 2023-07-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/app_sys_q.h"

typedef int ZUORU_HeapDataItem;
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
        if (heapPtr->heapItems[parentIdx] > heapPtr->heapItems[childIdx]) {
            return true;
        } else {
            return false;
        }
    } else {
        if (heapPtr->heapItems[parentIdx] < heapPtr->heapItems[childIdx]) {
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

MedianFinder* medianFinderCreate()
{
    MedianFinder *finderPtr = (MedianFinder*)malloc(sizeof(MedianFinder));
    finderPtr->maxHeapPtr = ZUORU_InitHeap(30000, true);
    finderPtr->minHeapPtr = ZUORU_InitHeap(30000, false);
    finderPtr->curItemCnt = 0;
    return finderPtr;
}

void medianFinderAddNum(MedianFinder* obj, int num)
{
    ZUORU_Heap *maxHeapPtr = (ZUORU_Heap*)obj->maxHeapPtr;
    ZUORU_Heap *minHeapPtr = (ZUORU_Heap*)obj->minHeapPtr;
    obj->curItemCnt++;
    if (ZUORU_IsEmptyHeap(maxHeapPtr)) {
        ZUORU_InsertHeap(maxHeapPtr, &num);
        return;
    }

    ZUORU_HeapDataItem tmpDataItem;
    if (num < maxHeapPtr->heapItems[0]) {
        ZUORU_InsertHeap(maxHeapPtr, &num);
        if (maxHeapPtr->curSize > minHeapPtr->curSize + 1) {
            ZUORU_RemoveHeapTop(maxHeapPtr, &tmpDataItem);
            ZUORU_InsertHeap(minHeapPtr, &tmpDataItem);
        }
    } else {
        ZUORU_InsertHeap(minHeapPtr, &num);
        if (minHeapPtr->curSize > maxHeapPtr->curSize) {
            ZUORU_RemoveHeapTop(minHeapPtr, &tmpDataItem);
            ZUORU_InsertHeap(maxHeapPtr, &tmpDataItem);
        }
    }
    return;
}

double medianFinderFindMedian(MedianFinder* obj)
{
    double ret = 0;
    ZUORU_Heap *maxHeapPtr = (ZUORU_Heap*)obj->maxHeapPtr;
    ZUORU_Heap *minHeapPtr = (ZUORU_Heap*)obj->minHeapPtr;
    if (obj->curItemCnt % 2 == 0) {
        ret = ((double)maxHeapPtr->heapItems[0] + (double)minHeapPtr->heapItems[0]) / 2;
    } else {
        ret = (double)maxHeapPtr->heapItems[0];
    }
    return ret;
}

void medianFinderFree(MedianFinder* obj)
{
    ZUORU_FreeHeap((ZUORU_Heap*)obj->maxHeapPtr);
    ZUORU_FreeHeap((ZUORU_Heap*)obj->minHeapPtr);
    free(obj);
}
