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

#include "../../../common_include/c_include.h"
#include "../../../common_include/define_const.h"
#include "../../../common_include/my_log.h"
#include "../../../common_include/my_util.h"
#include "../../include/my_simplefs/simplefs.h"

#include <linux/fs.h>

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

    sb->info.magic = htole32(SIMPLE_FS_MAGIC);
    sb->info.total_block_num = htole32(total_block_num);
    sb->info.total_inode_num = htole32(total_inode_num);
    sb->info.inode_store_block_num = htole32(inode_store_block_num);
    sb->info.inode_free_bitmap_block_num = htole32(inode_free_bitmap_block_num);
    sb->info.block_free_bitmap_block_num = htole32(block_free_bitmap_block_num);
    sb->info.free_inode_num = htole32(total_inode_num - 1);
    sb->info.free_block_num = htole32(free_block_num - 1);

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

/**
 * @brief write the block to store inodes
 *
 * @param fd file descriptor
 * @param sb simplefs superblock
 * @return int ret value
 */
static int write_inode_store_block(int fd, simplefs_sb *sb)
{
    int ret = RETURN_OK;
    uint8_t *block = (uint8_t*)calloc(1, SIMPLE_FS_BLOCK_SIZE);
    if (!block) {
        return RETURN_ERROR;
    }

    // root inode
    simplefs_inode *inode = (simplefs_inode*)block;
    // skip the inode 0
    // glibc: readdir will skip inode 0, vfs also avoids using inode 0;
    inode += 1;

    uint32_t first_data_block = 1 +
        le32toh(sb->info.inode_store_block_num) +
        le32toh(sb->info.inode_free_bitmap_block_num) +
        le32toh(sb->info.block_free_bitmap_block_num);

    inode->i_mode = htole32(S_IFDIR | S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR |
        S_IWGRP | S_IWOTH | S_IXUSR | S_IXGRP | S_IXOTH); // 777
    inode->i_uid = 0;
    inode->i_gid = 0;
    inode->i_size = htole32(SIMPLE_FS_BLOCK_SIZE);
    inode->i_ctime = inode->i_atime = inode->i_mtime = 0;
    inode->i_block = htole32(1);
    inode->i_nlink = htole32(2);
    inode->i_extent_block = htole32(first_data_block);

    // write inode to file
    ret = write(fd, block, SIMPLE_FS_BLOCK_SIZE);
    if (ret != SIMPLE_FS_BLOCK_SIZE) {
        ret = RETURN_ERROR;
        goto out;
    }

    // reset the block to all 0
    memset(block, 0, SIMPLE_FS_BLOCK_SIZE);
    for (int idx = 1; idx < le32toh(sb->info.inode_store_block_num); idx++) {
        ret = write(fd, block, SIMPLE_FS_BLOCK_SIZE);
        if (ret != SIMPLE_FS_BLOCK_SIZE) {
            ret = RETURN_ERROR;
            goto out;
        }
    }

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME,
        "write inode store block: %u, inode size=%ld\n",
        le32toh(sb->info.inode_store_block_num),
        sizeof(simplefs_inode));
    ret = RETURN_OK;
out:
    free(block);
    return ret;
}

static int write_inode_free_bitmap_block(int fd, simplefs_sb *sb)
{
    int ret = RETURN_OK;
    uint8_t *block = calloc(1, SIMPLE_FS_BLOCK_SIZE);
    if (!block) {
        return RETURN_ERROR;
    }

    uint64_t *inode_free_bitmap = (uint64_t*)block;
    memset(inode_free_bitmap, 0xff, SIMPLE_FS_BLOCK_SIZE);

    inode_free_bitmap[0] = htole64(0xfffffffffffffffc);
    // have used two inodes: 0xc: 1100: skip inode 0, inode 1 for root inode
    ret = write(fd, inode_free_bitmap, SIMPLE_FS_BLOCK_SIZE);
    if (ret != SIMPLE_FS_BLOCK_SIZE) {
        ret = RETURN_ERROR;
        goto out;
    }

    inode_free_bitmap[0] = 0xffffffffffffffff;
    for (int idx = 1; idx < le32toh(sb->info.inode_free_bitmap_block_num); idx++) {
        ret = write(fd, inode_free_bitmap, SIMPLE_FS_BLOCK_SIZE);
        if (ret != SIMPLE_FS_BLOCK_SIZE) {
            ret = RETURN_ERROR;
            goto out;
        }
    }
    ret = RETURN_OK;
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "write inode free bitmap block: %u\n",
        le32toh(sb->info.inode_free_bitmap_block_num));
out:
    free(block);
    return ret;
}

static int write_block_free_bitmap_block(int fd, simplefs_sb *sb)
{
    int ret = RETURN_OK;
    // first block: sb + inode_store_block + inode_free_bitmap_block +
    // block_free_bitmap_block + first_block for root inode
    uint32_t used_block_num = 1+ le32toh(sb->info.inode_store_block_num) +
        le32toh(sb->info.inode_free_bitmap_block_num) +
        le32toh(sb->info.block_free_bitmap_block_num) + 1;

    uint8_t *block = calloc(1, SIMPLE_FS_BLOCK_SIZE);
    if (!block) {
        return RETURN_ERROR;
    }

    uint64_t *block_free_bitmap = (uint64_t*)block;
    memset(block_free_bitmap, 0xff, SIMPLE_FS_BLOCK_SIZE);
    uint32_t used_bitmap_cnt = 0;
    uint32_t write_block_cnt = 0;
    while (used_block_num) {
        uint64_t cur_line = 0xffffffffffffffff;
        for (uint64_t mask = 0x1; mask; mask <<= 1) {
            cur_line &= ~mask;
            used_block_num--;
            if (used_block_num == 0) {
                break;
            }
        }
        block_free_bitmap[used_bitmap_cnt] = htole64(cur_line);
        used_bitmap_cnt++;
        if (used_bitmap_cnt * sizeof(uint64_t) == SIMPLE_FS_BLOCK_SIZE) {
            ret = write(fd, block_free_bitmap, SIMPLE_FS_BLOCK_SIZE);
            if (ret != SIMPLE_FS_BLOCK_SIZE) {
                ret = RETURN_ERROR;
                goto out;
            }
            write_block_cnt++;
            memset(block_free_bitmap, 0xff, SIMPLE_FS_BLOCK_SIZE);
            used_bitmap_cnt = 0;
        }
    }

    if (used_bitmap_cnt != 0) {
        ret = write(fd, block_free_bitmap, SIMPLE_FS_BLOCK_SIZE);
        if (ret != SIMPLE_FS_BLOCK_SIZE) {
            ret = RETURN_ERROR;
            goto out;
        }
        write_block_cnt++;
    }

    memset(block_free_bitmap, 0xff, SIMPLE_FS_BLOCK_SIZE);
    for (int idx = write_block_cnt; idx < le32toh(sb->info.block_free_bitmap_block_num); idx++) {
        ret = write(fd, block_free_bitmap, SIMPLE_FS_BLOCK_SIZE);
        if (ret != SIMPLE_FS_BLOCK_SIZE) {
            ret = RETURN_ERROR;
            goto out;
        }
    }

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "init write block free bitmap block: %u\n",
        write_block_cnt);
    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "total write block free bitmap block: %u\n",
        le32toh(sb->info.block_free_bitmap_block_num));
    ret = RETURN_OK;
out:
    free(block);
    return ret;
}

static int write_data_blocks(int fd, simplefs_sb *sb)
{
    // TODO: can be implemented in the future
    return RETURN_OK;
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
    int64_t min_required_size = 100 * SIMPLE_FS_BLOCK_SIZE;
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

    // write inode store blocks (from block 1)
    ret = write_inode_store_block(fd, sb);
    if (ret) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME,
            "write inode store block failed\n");
        ret = EXIT_FAILURE;
        goto out_free_sb;
    }

    // write inode free bitmap blocks
    ret = write_inode_free_bitmap_block(fd, sb);
    if (ret) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME,
            "write inode free bitmap block failed\n");
        ret = EXIT_FAILURE;
        goto out_free_sb;
    }

    // write block free bitmap blocks
    ret = write_block_free_bitmap_block(fd, sb);
    if (ret) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME,
            "write block free bitmap block failed\n");
        ret = EXIT_FAILURE;
        goto out_free_sb;
    }

    // write the data block section
    ret = write_data_blocks(fd, sb);
    if (ret) {
        ZUORU_LOGGING(ERROR_LOG_LEVEL, MODULE_NAME,
            "write data blocks failed\n");
        ret = EXIT_FAILURE;
        goto out_free_sb;
    }

    ZUORU_LOGGING(INFO_LOG_LEVEL, MODULE_NAME, "finish the formatting of "
        "%s\n", argv[1]);

out_free_sb:
    free(sb);
out_close_file:
    close(fd);

    return ret;
}
