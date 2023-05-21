/**
 * @file define_const.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief common define and const
 * @version 0.1
 * @date 2023-05-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DEFINE_CONST_H
#define DEFINE_CONST_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_READ_BUF_SIZE (4096)

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

#ifndef RETURN_OK
#define RETURN_OK 0
#endif

#ifndef RETURN_ERROR
#define RETURN_ERROR 1
#endif

#endif
