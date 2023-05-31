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

#include "../../include/basic_io/basic_io_w.h"

#ifdef __cplusplus
}
#endif

#define MODULE_ID "MAIN"

extern int g_var;

int main(int argc, char *argv[]) {
    /* code */
    PrintGlobalPtr();

    int* outPtr = &g_var;
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "out ptr: %p\n", outPtr);

    return 0;
}
