/**
 * @file app_sys.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief some questions about application systems
 * @version 0.1
 * @date 2023-06-14
 *
 * @copyright Copyright (c) 2023
 *
 */


#ifndef LEETCODE_C_APP_SYS_H
#define LEETCODE_C_APP_SYS_H

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

#endif