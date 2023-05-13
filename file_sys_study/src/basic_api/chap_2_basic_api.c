/**
 * @file chap_2_basic_api.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief implement the interfaces in chap_2
 * @version 0.1
 * @date 2023-05-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/chap_2_basic_api.h"

int32_t Chap2CopyFile(const char *srcFilePath, const char *destFilePath)
{
    int srcFd = 0;
    int destFs = 0;
    char dataBuf[MAX_READ_BUF_SIZE] = {0};
    size_t readCnt = 0;
    size_t writeCnt = 0;

    srcFd = open(srcFilePath, O_RDONLY);
    if (-1 == srcFd) {
    }

    return EXIT_SUCCESS;
}
