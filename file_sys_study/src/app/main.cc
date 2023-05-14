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

#define MODULE_NAME "MAIN"

int main(int argc, char* argv[]) {
    /* code */
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "input src name %s\n", argv[1]);
    // ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "input dest name %s\n", argv[2]);
    // Chap2CopyFile(argv[1], argv[2]);
    // ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "done\n");
    Chap2LckFile(argv[1]);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "done\n");
    return 0;
}
