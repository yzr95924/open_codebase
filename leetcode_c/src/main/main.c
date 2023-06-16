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
#include "../../include/app_sys.h"

#define MODULE_ID "LeetCodeMain"

int main(int argc, char* argv[]) {
    LRUCache *lruCacheObj = lRUCacheCreate(2);

    lRUCachePut(lruCacheObj, 2, 1);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "insert [2,1]\n");
    lRUCachePut(lruCacheObj, 1, 1);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "insert [1,1]\n");
    lRUCachePut(lruCacheObj, 2, 3);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "insert [2,3]\n");
    lRUCachePut(lruCacheObj, 4, 1);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "insert [4,1]\n");
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "get value 1: %d\n", lRUCacheGet(lruCacheObj, 1));
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "get value 2: %d\n", lRUCacheGet(lruCacheObj, 2));

    lRUCacheFree(lruCacheObj);

    return 0;
}