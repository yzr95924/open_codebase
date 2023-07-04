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
#include "../../include/app_sys_q.h"
#include "../../include/math_q.h"

#define MODULE_ID "LeetCodeMain"

int main(int argc, char* argv[]) {

    int testNum = 121;

    printf("test num: %d\n", isPalindrome(testNum));

    return 0;
}