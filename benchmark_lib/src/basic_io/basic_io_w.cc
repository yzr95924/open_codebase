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
#define RAW_DATA_FILE_PREFIX "tmp_data"
#define STAGING_DATA_FILE_PREFIX "staging_data"

using namespace std;

/**
 * @brief Construct a new Basic I O Util object
 *
 * @param io_size test io size
 */
BasicWriteUtil::BasicWriteUtil()
{
    ZUORU_LOGGING(INFO_LOG_LEVEL, "setting io size (KiB): %llu\n",
        sizeof(syn_data) * WRITE_IO_COUNT / KiB_2_B);
}

/**
 * @brief Destroy the Basic IO Util object
 *
 */
BasicWriteUtil::~BasicWriteUtil()
{

}

/**
 * @brief write operation with buffer
 *
 * @param idx test index
 */
void BasicWriteUtil::WriteWithBuf(uint32_t idx)
{
    string input_path = "tmp_data" + to_string(idx);
    int fd = open(input_path.c_str(), O_NOATIME | O_RDWR | O_CREAT, 0644);
    int ret = RETURN_OK;

    ret = posix_fallocate(fd, 0, sizeof(syn_data) * WRITE_IO_COUNT);
    if (ret != 0) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, "fallocate error: %d\n", ret);
    }
    lseek(fd, 0, SEEK_SET);

    for (size_t idx = 0; idx < WRITE_IO_COUNT; idx++) {
        write(fd, syn_data, WRITE_ONCE_BYTE_SIZE);
    }

    close(fd);

    return;
}

/**
 * @brief write operation without buffer
 *
 * @param idx test index
 */
void BasicWriteUtil::WriteWithoutBuf(uint32_t idx)
{
    string input_path = RAW_DATA_FILE_PREFIX + to_string(idx);
    string staging_fname = STAGING_DATA_FILE_PREFIX + to_string(idx);
    char *base = NULL;
    char *cursor = NULL;
    uint64_t staging_offset = 0;
    uint64_t file_offset = 0;
    int ret = RETURN_OK;
    void *staging_ptr = NULL;

    int staging_fd = open(staging_fname.c_str(), O_NOATIME | O_RDWR | O_CREAT,
        0644);
    ret = posix_fallocate(staging_fd, 0, DIRECT_WRITE_BUFFER_SIZE);
    if (ret != 0) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, "fallocate error: %d\n", ret);
        close(staging_fd);
        return;
    }

    staging_ptr = mmap(NULL, DIRECT_WRITE_BUFFER_SIZE, PROT_READ | PROT_WRITE,
        MAP_SHARED, staging_fd, 0);
    if (unlikely(staging_ptr == MAP_FAILED)) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, "mmap error\n");
        close(staging_fd);
        return;
    }

    int fd = open(input_path.c_str(), O_DIRECT | O_NOATIME | O_RDWR | O_CREAT,
        0644);
    ret = posix_fallocate(fd, 0, sizeof(syn_data) * WRITE_IO_COUNT);
    if (ret != 0) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, "fallocate error: %d\n",
            ret);
        close(staging_fd);
        close(fd);
        return;
    }
    lseek(fd, 0, SEEK_SET);

    base = (char*)staging_ptr;
    cursor = (char*)staging_ptr;

    for (size_t cnt = 0; cnt < WRITE_IO_COUNT; cnt++) {
        if (unlikely(staging_offset >= DIRECT_WRITE_BUFFER_SIZE)) {
            pwrite64(fd, staging_ptr, DIRECT_WRITE_BUFFER_SIZE, file_offset);
            cursor = base;
            file_offset += DIRECT_WRITE_BUFFER_SIZE;
            staging_offset = 0;
        }
        memcpy(cursor, syn_data, WRITE_ONCE_BYTE_SIZE);
        cursor += WRITE_ONCE_BYTE_SIZE;
        staging_offset += WRITE_ONCE_BYTE_SIZE;
    }

    close(staging_fd);
    close(fd);
    munmap(staging_ptr, DIRECT_WRITE_BUFFER_SIZE);
    staging_ptr = NULL;
    return;
}

/**
 * @brief remove test file
 *
 * @param idx test index
 * @param isDirectWrite is direct write
 */
void BasicWriteUtil::RemoveTestFile(uint32_t idx, bool use_buffer)
{
    string input_path = RAW_DATA_FILE_PREFIX + to_string(idx);
    string staging_path = STAGING_DATA_FILE_PREFIX + to_string(idx);
    int ret = RETURN_OK;

    if (use_buffer) {
        ret = remove(input_path.c_str());
        if (ret != 0) {
            ZUORU_LOGGING(ERROR_LOG_LEVEL, "unable to remove test file %s\n",
                input_path.c_str());
        }
    } else {
        ret = remove(input_path.c_str());
        if (ret != 0) {
            ZUORU_LOGGING(ERROR_LOG_LEVEL, "unable to remove test file %s\n",
                input_path.c_str());
        }

        ret = remove(staging_path.c_str());
        if (ret != 0) {
            ZUORU_LOGGING(ERROR_LOG_LEVEL, "unable to remove test file %s\n",
                input_path.c_str());
        }
    }

    return;
}
