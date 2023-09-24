/**
 * @file mkfs_simple.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief
 * @version 0.1
 * @date 2023-09-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <linux/fs.h>

#include "../../../common_include/c_include.h"
#include "../../../common_include/define_const.h"
#include "../../../common_include/my_log.h"

#include "../../include/my_fs/my_simple_fs.h"

#define MODULE_NAME "MKFS_SIMPLE"

int main(int argc, char *argv[])
{
    int ret = RETURN_OK;
    if (argc != 2) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME, "Usage: %s disk\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // open disk image
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME,
            "cannot open the disk image: %s, errno(%s)\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    // get image size
    struct stat stat_buf;
    ret = fstat(fd, &stat_buf);
    if (ret != RETURN_OK) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME,
            "get file stat failed, errno(%s)\n", strerror(errno));
        ret = EXIT_FAILURE;
        goto tag_close_file;
    }

    // get block device size
    if (S_ISBLK(stat_buf.st_mode)) {
        int64_t blk_size = 0;
        ret = ioctl(fd, BLKGETSIZE64, &blk_size);
        if (ret != RETURN_OK) {
            ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME,
                "get dev size failed, errno(%s)\n", strerror(errno));
            goto tag_close_file;
        }
        stat_buf.st_size = blk_size;
    }
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME,
        "get img/dev(%s) size: %ld\n", argv[0], stat_buf.st_size);

    // check if image/dev is large enough
    int64_t min_required_size = 1000 * MY_SIMPLE_BLOCK_SIZE;
    if (stat_buf.st_size < min_required_size) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME,
            "img/dev is not large enough(%ld), min(%ld)\n",
            stat_buf.st_size, min_required_size);
        ret = EXIT_FAILURE;
        goto tag_close_file;
    }

tag_close_file:
    close(fd);

    return ret;
}
