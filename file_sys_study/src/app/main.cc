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

#define CUR_MODULE_NAME "MAIN"

int main(int argc, char* argv[]) {
    /* code */
    Logging(DEBUG_LOG_LEVEL, CUR_MODULE_NAME, "hello world");
    return 0;
}
