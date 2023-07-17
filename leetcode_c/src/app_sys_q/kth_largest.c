/**
 * @file kth_largest.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/kth-largest-element-in-an-array/
 * @version 0.1
 * @date 2023-07-13
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

void ZUORU_SwapHeapItem(ZUORU_HeapDataItem *heapItems, int idx1, int idx2)
{
    ZUORU_HeapDataItem tmpItem;
    memcpy(&tmpItem, &heapItems[idx1], sizeof(ZUORU_HeapDataItem));
    memcpy(&heapItems[idx1], &heapItems[idx2], sizeof(ZUORU_HeapDataItem));
    memcpy(&heapItems[idx2], &tmpItem, sizeof(ZUORU_HeapDataItem));
    return;
}

bool ZUORU_IsParentLarge(ZUORU_HeapDataItem *heapItems,
    int parentIdx, int childIdx, bool isMaxHeap)
{
    ZUORU_HeapDataItem *parentItem = &heapItems[parentIdx];
    ZUORU_HeapDataItem *childItem = &heapItems[childIdx];
    if (isMaxHeap) {
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
    int newIdx = heapPtr->curSize;
    memcpy(&heapPtr->heapItems[newIdx], inVal, sizeof(ZUORU_HeapDataItem));

    while (((newIdx / 2) > 0) &&
        ZUORU_IsParentLarge(heapPtr->heapItems, newIdx / 2, newIdx, heapPtr->isMaxHeap)) {
            ZUORU_SwapHeapItem(heapPtr->heapItems, newIdx, newIdx / 2);
            newIdx = newIdx / 2;
    }

    return true;
}

bool ZUORU_RemoveHeapTop(ZUORU_Heap *heapPtr, ZUORU_HeapDataItem *outVal)
{
    if (heapPtr->curSize == 0) {
        return false;
    }

    memcpy(outVal, &heapPtr->heapItems[1], sizeof(ZUORU_HeapDataItem));
    memcpy(&heapPtr->heapItems[1], &heapPtr->heapItems[heapPtr->curSize],
        sizeof(ZUORU_HeapDataItem));
    heapPtr->curSize--;

    int curIdx = 1;
    int nextPos;
    while (true) {
        nextPos = curIdx;
        if (2 * curIdx <= heapPtr->curSize &&
            ZUORU_IsParentLarge(heapPtr->heapItems, curIdx, 2 * curIdx, heapPtr->isMaxHeap)) {
            nextPos = curIdx * 2;
        }
        if (2 * curIdx + 1 <= heapPtr->curSize &&
            ZUORU_IsParentLarge(heapPtr->heapItems, curIdx, 2 * curIdx + 1, heapPtr->isMaxHeap)) {
            nextPos = curIdx * 2 + 1;
        }
        if (nextPos == curIdx) {
            break;
        }
        ZUORU_SwapHeapItem(heapPtr->heapItems, curIdx, nextPos);
        curIdx = nextPos;
    }

    return true;
}

/**
 * @brief 215. Kth Largest Element in an Array
 *
 * @param nums input nums
 * @param numsSize input size
 * @param k top k
 * @return int return value
 */
int findKthLargest(int* nums, int numsSize, int k)
{
    ZUORU_Heap *heapPtr = ZUORU_InitHeap(100000, true);
}