/**
 * @file basic_io_w.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief basic io with buffer
 * @version 0.1
 * @date 2023-06-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef OPEN_CODEBASE_BASIC_IO_W_H
#define OPEN_CODEBASE_BASIC_IO_W_H

#include "../../../common_include/cpp_include.h"
#include "../../../common_include/my_log.h"
#include "../../../common_include/define_const.h"
#include "../../../common_include/my_util.h"

#define WRITE_ONCE_BYTE_SIZE (4096)
#define WRITE_IO_COUNT (1024 * 1024ULL)
#define DIRECT_WRITE_BUFFER_SIZE (WRITE_ONCE_BYTE_SIZE * 4)

const char syn_data[WRITE_ONCE_BYTE_SIZE] __attribute__((aligned(WRITE_ONCE_BYTE_SIZE))) = {'a'};

class BasicWriteUtil {
    private:

    public:
        /**
         * @brief Construct a new Basic I O Util object
         *
         */
        BasicWriteUtil();

        /**
         * @brief Destroy the Basic IO Util object
         *
         */
        ~BasicWriteUtil();

        /**
         * @brief write operation with buffer
         *
         * @param idx test index
         */
        void WriteWithBuf(uint32_t idx);

        /**
         * @brief remove test file
         *
         * @param idx test index
         * @param isDirectWrite is direct write
         */
        void RemoveTestFile(uint32_t idx, bool isDirectWrite);

        /**
         * @brief write operation without buffer
         *
         * @param idx test index
         */
        void WriteWithoutBuf(uint32_t idx);
};

#endif