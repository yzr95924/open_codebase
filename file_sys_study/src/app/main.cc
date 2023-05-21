/**
 * @file main.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief the main template
 * @version 0.1
 * @date 2021-12-03
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "../../include/chap_2_basic_api.h"

#ifdef __cplusplus
}
#endif

#include <bits/stdc++.h>

#define MODULE_NAME "MAIN"

int main(int argc, char* argv[]) {
    /* code */
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "input src name %s\n", argv[1]);
    int testArray[4] = {1, 2, 4, 10};
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "done\n");
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "array size: %lu\n", ARRAY_SIZE(testArray));
    return 0;
}
