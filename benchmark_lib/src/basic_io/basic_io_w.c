/**
 * @file basic_io_w.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief
 * @version 0.1
 * @date 2023-06-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/basic_io/basic_io_w.h"

#define MODULE_ID "BASIC_IO_W"

int g_var = 0;

int* GetGlobalVarPtr()
{
    return &g_var;
}

void PrintGlobalPtr()
{
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_ID, "inner: %p\n", GetGlobalVarPtr());
    return ;
}