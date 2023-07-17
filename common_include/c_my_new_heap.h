/**
 * @file c_my_new_heap.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief my new heap
 * @version 0.1
 * @date 2023-07-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MY_NEW_HEAP_H
#define MY_NEW_HEAP_H

#include "define_const.h"
#include "c_include.h"

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

bool ZUORU_IsParentLarge(ZUORU_Heap *heapPtr, int parentIdx, int childIdx)
{
    ZUORU_HeapDataItem *parentItem = &heapPtr->heapItems[parentIdx];
    ZUORU_HeapDataItem *childItem = &heapPtr->heapItems[childIdx];
    if (heapPtr->isMaxHeap) {
        if (*parentItem - *childItem < 0) {
            return true;
        } else {
            return false;
        }
    } else {
        if (*parentItem - *childItem < 0) {
            return false;
        } else {
            return true;
        }
    }

    return false;
}

ZUORU_Heap* ZUORU_InitHeap(int capacity, bool isMaxHeap)
{
    ZUORU_Heap *heapPtr = (ZUORU_Heap*)calloc(1, sizeof(ZUORU_Heap));
    heapPtr->heapItems = (ZUORU_HeapDataItem*)calloc(capacity + 1, sizeof(ZUORU_HeapDataItem));
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

bool ZUORU_InsertHeap(ZUORU_Heap *heapPtr, ZUORU_HeapDataItem *inVal)
{
    if (ZUORU_IsFullHeap(heapPtr)) {
        fprintf(stderr, "heap is full\n");
        return false;
    }

    heapPtr->curSize++;
    int curIdx = heapPtr->curSize - 1;
    memcpy(&heapPtr->heapItems[curIdx], inVal, sizeof(ZUORU_HeapDataItem));

    int parentIdx = ZUORU_HeapGetParent(curIdx);
    while (curIdx != 0 && heapPtr->heapItems[parentIdx] > heapPtr->heapItems[curIdx]) {
        // ZUORU_IsParentLarge(heapPtr, parentIdx, curIdx)) {
        ZUORU_SwapHeapItem(heapPtr->heapItems, curIdx, parentIdx);
        curIdx = parentIdx;
        parentIdx = ZUORU_HeapGetParent(curIdx);
    }

    return true;
}

void ZUORU_MakeHeap(ZUORU_Heap *heapPtr, int curIdx)
{
    int leftIdx = ZUORU_HeapGetLeftChild(curIdx);
    int rightIdx = ZUORU_HeapGetRightChild(curIdx);
    int smallIdx = curIdx;

    if (leftIdx < heapPtr->curSize && heapPtr->heapItems[leftIdx] < heapPtr->heapItems[curIdx]) {
        // ZUORU_IsParentLarge(heapPtr, curIdx, leftIdx)) {
        smallIdx = leftIdx;
    }
    if (rightIdx < heapPtr->curSize && heapPtr->heapItems[rightIdx] < heapPtr->heapItems[curIdx]) {
        // ZUORU_IsParentLarge(heapPtr, curIdx, rightIdx)) {
        smallIdx = rightIdx;
    }
    if (smallIdx != curIdx) {
        ZUORU_SwapHeapItem(heapPtr->heapItems, curIdx, smallIdx);
        ZUORU_MakeHeap(heapPtr, smallIdx);
    }
    return;
}

bool ZUORU_RemoveHeapTop(ZUORU_Heap *heapPtr, ZUORU_HeapDataItem *outVal)
{
    if (heapPtr->curSize == 0) {
        return false;
    }

    memcpy(outVal, &heapPtr->heapItems[0], sizeof(ZUORU_HeapDataItem));
    if (heapPtr->curSize == 1) {
        return true;
    }

    memcpy(&heapPtr->heapItems[0], &heapPtr->heapItems[heapPtr->curSize - 1],
        sizeof(ZUORU_HeapDataItem));
    heapPtr->curSize--;
    ZUORU_MakeHeap(heapPtr, 0);

    return true;
}

#endif
