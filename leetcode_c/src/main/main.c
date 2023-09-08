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
#include "../../../common_include/my_util.h"
#include "../../../common_include/define_const.h"
#include "../../include/app_sys_q.h"
#include "../../include/bfs_q.h"
#include "../../include/math_q.h"
#include "../../include/stack_q.h"
#include "../../include/hash_q.h"
#include "../../include/slide_two_q.h"
#include "../../include/str_arr_q.h"
#include "../../include/greedy_dp_q.h"

#define MODULE_ID "LeetCodeMain"

int main(int argc, char* argv[]) {
    int nums[] = {3, 4, -1, 1};
    int ret = firstMissingPositive(nums, ARRAY_SIZE(nums));
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "ret: %d\n", ret);
    return 0;
}