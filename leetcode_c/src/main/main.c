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
#include "../../include/stack_q.h"

#define MODULE_ID "LeetCodeMain"

int main(int argc, char* argv[]) {
    char inputStr[] = "2[20[bc]31[xy]]xd4[rt]";
    char *retArr = decodeString(inputStr);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "ret: %s\n", retArr);
    free(retArr);
    return 0;
}