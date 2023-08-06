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
#include "../../include/hash_q.h"

#define MODULE_ID "LeetCodeMain"

int ZUORU_CompFunc(const void *rawInput1, const void *rawInput2)
{
    char *input1 = (char*)rawInput1;
    char *input2 = (char*)rawInput2;
    int ret = *input1 - *input2; // ascend

    return ret;
}

int main(int argc, char* argv[]) {
    char testStr[] = "abba";
    qsort(testStr, strlen(testStr), sizeof(char), ZUORU_CompFunc);
    printf("%s\n", testStr);
    return 0;
}