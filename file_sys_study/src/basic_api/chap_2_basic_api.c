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

#define MODULE_NAME "CHAP2_BASIC_API"

/**
 * @brief copy file from the src to dest
 *
 * @param srcFilePath src file path
 * @param destFilePath dest file path
 * @return int32_t ret
 */
int32_t Chap2CopyFile(const char *srcFilePath, const char *destFilePath)
{
    int srcFd = 0;
    int destFd = 0;
    char dataBuf[MAX_READ_BUF_SIZE] = {0};
    size_t readCnt = 0;
    size_t writeCnt = 0;
    int32_t ret = RETURN_OK;

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "start to copy the file.\n");

    srcFd = open(srcFilePath, O_RDONLY);
    if (-1 == srcFd) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME, "open src file failed.\n");
        return RETURN_ERROR;
    }

    destFd = open(destFilePath, O_WRONLY | O_CREAT, 0644);
    if (-1 == destFd) {
        close(srcFd);
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME, "open dest file failed.\n");
        return RETURN_ERROR;
    }

    while ((readCnt = read(srcFd, &dataBuf, MAX_READ_BUF_SIZE)) > 0) {
        size_t remainDataCnt = readCnt;
        while (remainDataCnt > 0) {
            writeCnt = write(destFd, &dataBuf, remainDataCnt);
            if (writeCnt < 0) {
                close(destFd);
                close(srcFd);
                ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME, "write data error.\n");
                return RETURN_ERROR;
            }
            remainDataCnt -= writeCnt;
        }
    }

    if (readCnt < 0 || writeCnt < 0) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME, "copy data failed.\n");
        ret = RETURN_ERROR;
    }
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "finish copying the file.\n");

    close(destFd);
    close(srcFd);

    return ret;
}

/**
 * @brief list the item of a dir
 *
 * @param targetDirPath target dir path
 * @return int32_t ret
 */
int32_t Chap2ListDir(const char *targetDirPath) {
    DIR *dir = NULL;
    struct dirent *dentPtr;

    dir = opendir(targetDirPath);
    if (NULL == dir) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME, "open the target dir failed\n");
        return RETURN_ERROR;
    }

    while((dentPtr = readdir(dir)) != NULL) {
        ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "item name: %s, %llu\n",
            dentPtr->d_name, dentPtr->d_ino);
    }

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "finish readdir\n");
    closedir(dir);
    return RETURN_OK;
}

/**
 * @brief change the file mode
 *
 * @param targetFilePath target file path
 * @return int32_t ret
 */
int32_t Chap2ChmodFile(const char *targetFilePath)
{
    int32_t ret = RETURN_OK;
    struct stat fileInfo;
    int mode = 0;

    ret = stat(targetFilePath, &fileInfo);
    if (ret < 0) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME, "get file stat failed.\n");
        return RETURN_ERROR;
    }

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "original mode: %d\n", fileInfo.st_mode);
    mode = fileInfo.st_mode | S_IXUSR;
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "new mode: %d\n", mode);

    ret = chmod(targetFilePath, mode);
    if (ret < 0) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME, "change the mode failed.\n");
        return RETURN_ERROR;
    }

    return RETURN_OK;
}

/**
 * @brief lock the file test
 *
 * @param testFilePath target test file path
 * @return int32_t ret
 */
int32_t Chap2LckFile(const char *testFilePath)
{
    int32_t ret = RETURN_OK;
    struct flock testLock = {
        .l_whence = SEEK_SET,
        .l_type = F_WRLCK
    };

    int testFileFd = open(testFilePath, O_RDWR);
    if (testFileFd < 0) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME, "open file failed.\n");
        return RETURN_ERROR;
    }

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "before lock file.\n");
    ret = fcntl(testFileFd, F_SETLK, &testLock);
    if (ret < 0) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME, "lock the file failed.\n");
        close(testFileFd);
        return RETURN_ERROR;
    }
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "after lock file.\n");
    sleep(30);

    testLock.l_type = F_UNLCK;
    ret = fcntl(testFileFd, F_SETLK, &testLock);
    if (ret < 0) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME, "unlock the file failed.\n");
        return RETURN_ERROR;
    }
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "unlock the file.\n");

    return RETURN_OK;
}
