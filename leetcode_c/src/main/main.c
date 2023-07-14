/**
 * @file main.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief the main process
 * @version 0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../../common_include/my_log.h"
#include "./../../common_include/define_const.h"
#include "../../include/app_sys_q.h"
#include "../../include/bfs_q.h"
#include "../../include/math_q.h"
#include "../../../common_include/c_my_heap.h"

#define MODULE_ID "LeetCodeMain"

int main(int argc, char* argv[]) {

    ZUORU_Heap *heapPtr = ZUORU_InitHeap(100, true);
    int arr[] = {2,1,10,21,19,6,5,12,9};

    for (int idx = 0; idx < ARRAY_SIZE(arr); idx++) {
        ZUORU_InsertHeap(heapPtr, &arr[idx]);
    }

    ZUORU_HeapDataItem outVal = 0;
    ZUORU_RemoveTop(heapPtr, &outVal);
    int totalSize = heapPtr->curSize;
    for (int idx = 1; idx <= totalSize; idx++) {
        fprintf(stderr, "%d ", heapPtr->heapItems[idx]);
    }
    fprintf(stderr, "\n");

    ZUORU_FreeHeap(heapPtr);
    return 0;
}