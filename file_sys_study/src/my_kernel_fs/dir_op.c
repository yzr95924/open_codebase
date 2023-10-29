/**
 * @file dir_op.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief my simplefs dir operation
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/my_simplefs/dir_op.h"

#include <linux/buffer_head.h>

/**
 * @brief called when the VFS needs to read the dir contents
 *
 * @param dir dir file
 * @param ctx iterate ctx
 * @return int ret value
 */
static int simplefs_dir_iterate_shared(struct file *dir, struct dir_context *ctx)
{
    struct inode *l_vfs_inode = file_inode(dir);
    simplefs_inode_info *l_simplefs_inode_info =
        SIMPLEFS_GET_INODE_INFO_FROM_INODE(l_vfs_inode);
    struct super_block *l_superblock = l_vfs_inode->i_sb;
    struct buffer_head *dir_index_block_bh = NULL;
    struct buffer_head *block_bh = NULL;
    simplefs_file_ei_block *l_eblock = NULL;
    simplefs_dir_block *l_dir_block = NULL;
    simplefs_file *l_file = NULL;
    uint32_t extent_idx = 0;
    uint32_t block_idx = 0;
    uint32_t file_idx = 0;
    int ret = 0;

    ZUORU_ENTRY;

    if (!S_ISDIR(l_vfs_inode->i_mode)) {
        ZUORU_KO_LOG_ERR("it is not dir\n");
        return -ENOTDIR;
    }

    if (ctx->pos > SIMPLEFS_MAX_SUB_FILES + 2) {
        return 0;
    }

    // commit . and .. to ctx
    if (!dir_emit_dots(dir, ctx)) {
        return 0;
    }

    // read the dir index block from disk
    dir_index_block_bh = sb_bread(l_superblock, l_simplefs_inode_info->i_extent_block);
    if (!dir_index_block_bh) {
        ZUORU_KO_LOG_ERR("read dir index block failed\n");
        return -EIO;
    }
    l_eblock = (simplefs_file_ei_block*)dir_index_block_bh->b_data;

    extent_idx = (ctx->pos - 2) / SIMPLEFS_FILES_PER_EXT;
    block_idx = ((ctx->pos - 2) % SIMPLEFS_FILES_PER_EXT) / SIMPLEFS_FILES_PER_BLOCK;
    file_idx = (ctx->pos - 2) % SIMPLEFS_FILES_PER_BLOCK;

    // iterate over the index block and commit the sub-files
    for (; extent_idx < SIMPLEFS_MAX_EXTENTS; extent_idx++) {
        if (l_eblock->extents[extent_idx].e_p_block == 0) {
            break;
        }
        // iterate over blocks in one extent
        for (; block_idx < l_eblock->extents[extent_idx].e_len; block_idx++) {
            block_bh = sb_bread(l_superblock, l_eblock->extents[extent_idx].e_p_block + block_idx);
            if (!block_bh) {
                ret = -EIO;
                goto out_release_bh;
            }
            l_dir_block = (simplefs_dir_block*)block_bh->b_data;
            if (l_dir_block->files[0].inode == 0) {
                break;
            }

            // iterate over every file in one block
            for (; file_idx < SIMPLEFS_FILES_PER_BLOCK; file_idx++) {
                l_file = &l_dir_block->files[file_idx];
                if (l_file->inode && !dir_emit(ctx, l_file->filename, SIMPLEFS_MAX_FILENAME_LEN,
                    l_file->inode, DT_UNKNOWN)) { // cannot support returning the type of the file
                    break;
                }
                ctx->pos++;
            }
            brelse(block_bh);
            block_bh = NULL;
        }
    }

    brelse(dir_index_block_bh);

    ZUORU_EXIT;
    return ret;

out_release_bh:
    brelse(dir_index_block_bh);
    return ret;
}

const struct file_operations simplefs_dir_ops = {
    .owner = THIS_MODULE,
    .iterate_shared = simplefs_dir_iterate_shared,
};

const struct file_operations* simplefs_get_inode_dir_op(void)
{
    return &simplefs_dir_ops;
}