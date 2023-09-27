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
#include "../../../common_include/my_util.h"

#include "../../include/my_fs/my_simple_fs.h"

#define MODULE_NAME "MKFS_SIMPLE"

typedef struct {
    simplefs_sb_info info;
    uint8_t pad[SIMPLE_FS_BLOCK_SIZE - sizeof(simplefs_sb_info)];
} __attribute__((packed)) simplefs_sb;

/**
 * @brief write superblock to the dev/img
 *
 * @param fd file descriptor
 * @param stat_buf stat buffer
 * @return simplefs_sb* superblock buffer
 */
static simplefs_sb* write_superblock(int fd, struct stat *stat_buf)
{
    simplefs_sb *sb = calloc(1, sizeof(simplefs_sb));
    if (!sb) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME, "alloc superblock failed\n");
        return NULL;
    }

    uint32_t total_block_num = stat_buf->st_size / SIMPLE_FS_BLOCK_SIZE;
    uint32_t total_inode_num = total_block_num;
    uint32_t mod = total_inode_num % SIMPLE_FS_INODE_PER_BLOCK;
    if (mod) {
        total_inode_num += SIMPLE_FS_INODE_PER_BLOCK - mod;
    }
    uint32_t inode_store_block_num = ZUORU_DivCeil(total_inode_num,
        SIMPLE_FS_INODE_PER_BLOCK);
    uint32_t inode_free_bitmap_block_num = ZUORU_DivCeil(total_inode_num,
        SIMPLE_FS_BLOCK_SIZE * 8);
    uint32_t block_free_bitmap_block_num = ZUORU_DivCeil(total_block_num,
        SIMPLE_FS_BLOCK_SIZE * 8);
    uint32_t free_block_num =
        total_block_num - inode_store_block_num - inode_free_bitmap_block_num -
            block_free_bitmap_block_num;

    sb->info.magic = SIMPLE_FS_MAGIC;
    sb->info.total_block_num = total_block_num;
    sb->info.total_inode_num = total_inode_num;
    sb->info.inode_store_block_num = inode_store_block_num;
    sb->info.inode_free_bitmap_block_num = inode_free_bitmap_block_num;
    sb->info.block_free_bitmap_block_num = block_free_bitmap_block_num;
    sb->info.free_inode_num = total_inode_num - 1;
    sb->info.free_block_num = free_block_num - 1;

    int ret = write(fd, sb, sizeof(simplefs_sb));
    if (ret != sizeof(simplefs_sb)) {
        free(sb);
        return NULL;
    }

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME,
        "write superblock: size=%ld, magic=%#x, total_block_num=%u, "
        "total_inode_num=%u, inode_store_block_num=%u, "
        "inode_free_bitmap_block_num=%u, block_free_bitmap_block_num=%u, "
        "free_inode_num=%u, free_block_num=%u\n", sizeof(simplefs_sb), sb->info.magic,
        sb->info.total_block_num, sb->info.total_inode_num, sb->info.inode_store_block_num,
        sb->info.inode_free_bitmap_block_num, sb->info.block_free_bitmap_block_num,
        sb->info.free_inode_num, sb->info.free_block_num);

    return sb;
}

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
        goto out_close_file;
    }

    // get block device size
    if (S_ISBLK(stat_buf.st_mode)) {
        int64_t blk_size = 0;
        ret = ioctl(fd, BLKGETSIZE64, &blk_size);
        if (ret != RETURN_OK) {
            ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME,
                "get dev size failed, errno(%s)\n", strerror(errno));
            goto out_close_file;
        }
        stat_buf.st_size = blk_size;
    }
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME,
        "get img/dev (%s) size: %ld, blk size: %ld\n", argv[1], stat_buf.st_size,
        stat_buf.st_blksize);

    // check if image/dev is large enough
    int64_t min_required_size = 1000 * SIMPLE_FS_BLOCK_SIZE;
    if (stat_buf.st_size < min_required_size) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME,
            "img/dev is not large enough(%ld), min(%ld)\n",
            stat_buf.st_size, min_required_size);
        ret = EXIT_FAILURE;
        goto out_close_file;
    }

    // write superblock (block 0)
    simplefs_sb *sb = NULL;
    sb = write_superblock(fd, &stat_buf);
    if (!sb) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME,
            "write superblock failed\n");
        ret = EXIT_FAILURE;
        goto out_close_file;
    }

out_close_file:
    close(fd);

    return ret;
}
