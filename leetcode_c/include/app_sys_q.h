/**
 * @file app_sys_q.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief the question set about application systems
 * @version 0.1
 * @date 2023-06-14
 *
 * @copyright Copyright (c) 2023
 *
 */


#ifndef LEETCODE_C_APP_SYS_Q_H
#define LEETCODE_C_APP_SYS_Q_H

#include "../../common_include/c_include.h"

/**
 * @brief 146. LRU Cache
 * @cite https://leetcode.cn/problems/lru-cache/
 *
 */
typedef struct {
    void *hashTblPtr;
    void *dLListPtr;
    int capacity;
    int curSize;
} LRUCache;
LRUCache* lRUCacheCreate(int capacity);
int lRUCacheGet(LRUCache *obj, int key);
void lRUCachePut(LRUCache *obj, int key, int value);
void lRUCacheFree(LRUCache *obj);

/**
 * @brief 215. Kth Largest Element in an Array
 * @cite https://leetcode.cn/problems/kth-largest-element-in-an-array/
 *
 */
int findKthLargest(int* nums, int numsSize, int k);

/**
 * @brief 347. Top K Frequent Elements
 * @cite https://leetcode.cn/problems/top-k-frequent-elements/
 *
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize);

/**
 * @brief 295. Find Median from Data Stream
 * @cite https://leetcode.cn/problems/find-median-from-data-stream/
 *
 */
typedef struct {
    void *maxHeapPtr;
    void *minHeapPtr;
    int curItemCnt;
} MedianFinder;
MedianFinder* medianFinderCreate();
void medianFinderAddNum(MedianFinder* obj, int num);
double medianFinderFindMedian(MedianFinder* obj);
void medianFinderFree(MedianFinder* obj);

#endif