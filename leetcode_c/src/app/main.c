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
#include "../../../common_include/my_log.h"

#define MODULE_ID "LeetCodeMain"

int main(int argc, char* argv[]) {
    ZUORU_ARR_LIST_T *listPtr = Zuoru_InitArrList(10);

    ZUORU_DATA_T val = 1;
    Zuoru_AppendArrList(listPtr, &val);
    val = 2;
    Zuoru_AppendArrList(listPtr, &val);
    val = 5;
    Zuoru_AppendArrList(listPtr, &val);
    val = 1;
    Zuoru_AppendArrList(listPtr, &val);
    val = 4;
    Zuoru_AppendArrList(listPtr, &val);

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "after init\n");
    for (int idx = 0; idx < listPtr->curSize; idx++) {
        fprintf(stderr, "%d ", listPtr->data[idx]);
    }
    fprintf(stderr, "\n");

    Zuoru_SortArrList(listPtr);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "after sort\n");
    for (int idx = 0; idx < listPtr->curSize; idx++) {
        fprintf(stderr, "%d ", listPtr->data[idx]);
    }
    fprintf(stderr, "\n");

    val = 100;
    Zuoru_InsertArrList(listPtr, 1, &val);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "after insert\n");
    for (int idx = 0; idx < listPtr->curSize; idx++) {
        fprintf(stderr, "%d ", listPtr->data[idx]);
    }
    fprintf(stderr, "\n");

    int posIdx;
    if (Zuoru_FindArrList(listPtr, &val, &posIdx)) {
        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "find ret: %d\n",
            posIdx);
    }

    return 0;
}