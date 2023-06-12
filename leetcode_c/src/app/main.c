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

#include "../../../common_include/c_my_data_struct.h"
#include "../../../common_include/c_my_hash.h"
#include "../../../common_include/my_log.h"

#define MODULE_ID "LeetCodeMain"

int main(int argc, char* argv[]) {
    ZUORU_HASH_TBL_INT_ITEM_H **hashTblPtr = NULL;
    hashTblPtr = Zuoru_InitIntHashTbl();
    ZUORU_HASH_TBL_INT_ITEM_H *tmpItem;

    ZUORU_DATA_T testVal = 1;
    Zuoru_InsertIntHashTbl(hashTblPtr, 1, &testVal);
    testVal = 2;
    Zuoru_InsertIntHashTbl(hashTblPtr, 2, &testVal);

    if (Zuoru_FindIntHashTbl(hashTblPtr, 1, &tmpItem)) {
        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "find the key, val: %d\n",
            tmpItem->hashVal);
    }

    Zuoru_FreeIntHashTbl(hashTblPtr);

    return 0;
}