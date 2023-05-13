/**
 * @file chap_2_basic_api.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief basic file system api
 * @version 0.1
 * @date 2023-05-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef CHAP_2_BASIC_API_H
#define CHAP_2_BASIC_API_H

#include "define_const.h"
#include "my_log.h"

int32_t Chap2CopyFile(const char *srcFilePath, const char *destFilePath);

#endif
