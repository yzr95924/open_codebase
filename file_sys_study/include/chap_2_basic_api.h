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

/**
 * @brief copy file from the src to dest
 *
 * @param srcFilePath src file path
 * @param destFilePath dest file path
 * @return int32_t ret
 */
int32_t Chap2CopyFile(const char *srcFilePath, const char *destFilePath);

/**
 * @brief list the item of a dir
 *
 * @param targetDirPath target dir path
 * @return int32_t ret
 */
int32_t Chap2ListDir(const char *targetDirPath);

/**
 * @brief change the file mode
 *
 * @param targetFilePath target file path
 * @return int32_t ret
 */
int32_t Chap2ChmodFile(const char *targetFilePath);

/**
 * @brief lock the file test
 *
 * @param testFilePath target test file path
 * @return int32_t ret
 */
int32_t Chap2LckFile(const char *testFilePath);

#endif
