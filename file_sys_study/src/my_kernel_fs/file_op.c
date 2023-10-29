/**
 * @file file_op.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief inode file ops interface implementation
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/my_simplefs/file_op.h"

#include <linux/mpage.h>
#include <linux/buffer_head.h>
#include <linux/minmax.h>

#include "../../include/my_simplefs/extent.h"
#include "../../include/my_simplefs/bitmap.h"

/**
 * @brief map the buffer_head passed in argument with iblock-th block of
 * the file with the given inode; if the requested block is not allocated
 * and create flag is true --> allocate a new block on disk and map it to
 * the given buffer_head
 *
 * @param inode file inode
 * @param iblock target block index
 * @param bh_result return bh
 * @param create create flag
 * @return int result
 */
static int simplefs_file_get_block(struct inode *inode, sector_t iblock,
    struct buffer_head *bh_result, int create)
{
    struct super_block *l_sb = inode->i_sb;
    simplefs_sb_info *l_sb_info = l_sb->s_fs_info;
    simplefs_inode_info *l_inode_info = SIMPLEFS_GET_INODE_INFO_FROM_INODE(inode);
    simplefs_file_ei_block *index = NULL;
    struct buffer_head *bh_index = NULL;
    int ret = 0;
    int block_idx = 0;
    int extent_idx = 0;

    ZUORU_ENTRY;

    // if block number exceeds filesize --> failed
    if (iblock >= SIMPLEFS_MAX_BLOCK_PER_EXTENT * SIMPLEFS_MAX_EXTENTS) {
        ZUORU_KO_LOG_ERR("block num exceeds filesize\n");
        return -EFBIG;
    }

    bh_index = sb_bread(l_sb, l_inode_info->i_extent_block);
    if (!bh_index) {
        ZUORU_KO_LOG_ERR("read extent index block failed\n");
        return -EIO;
    }
    index = (simplefs_file_ei_block*) bh_index->b_data;

    // find the extent contain the iblock-th block
    extent_idx = simplefs_ext_search_blk(index, iblock);
    if (extent_idx == -1) {
        ZUORU_KO_LOG_ERR("target block out of extent index block\n")
        ret = -EFBIG;
        goto out_release_bh_index;
    }

    // check if iblock is already allocated
    // if not and create flag is true --> allocate it
    // else --> get the physical block number
    if (index->extents[extent_idx].e_p_block == 0) {
        if (create == 0) {
            return 0;
        }
        block_idx = get_free_blocks(l_sb_info, 8);
        if (!block_idx) {
            ZUORU_KO_LOG_ERR("get free blocks failed\n");
            ret = -ENOSPC;
            goto out_release_bh_index;
        }
        index->extents[extent_idx].e_p_block = block_idx;
        index->extents[extent_idx].e_len = 8;
        if (extent_idx == 0) {
            index->extents[extent_idx].e_l_block = 0;
        } else {
            index->extents[extent_idx].e_l_block =
                index->extents[extent_idx - 1].e_l_block +
                index->extents[extent_idx - 1].e_len;
        }
    } else {
        // ZUORU: ???
        block_idx = index->extents[extent_idx].e_p_block + iblock -
            index->extents[extent_idx].e_l_block;
    }

    // map the physical block to the given buffer_head
    map_bh(bh_result, l_sb, block_idx);
    brelse(bh_index);

    ZUORU_EXIT;
    return ret;

out_release_bh_index:
    brelse(bh_index);
    return ret;
}

/**
 * @brief called by the page cache to read a page from the physical
 * disk and map it in memory
 *
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0)
static void simplefs_readahead(struct readahead_control *rac)
{
    ZUORU_ENTRY;
    ZUORU_EXIT;
    mpage_readahead(rac, simplefs_file_get_block);
}
#else
static int simplefs_readpage(struct file *file, struct page *page)
{
    ZUORU_ENTRY;
    ZUORU_EXIT;
    return mpage_readpage(page, simplefs_file_get_block);
}
#endif

/**
 * @brief called by the vfs when a write() syscall occurs on file
 * before writing the data in the page cache; check if the write
 * will be able to complete and allocate the necessary blocks through
 * block_write_begin()
 *
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0)
static int simplefs_write_begin(struct file *file, struct address_space *mapping,
    loff_t pos, unsigned int len, struct page **pagep, void **fsdata)
#else
static int simplefs_write_begin(struct file *file, struct address_space *mapping,
    loff_t pos, unsigned int len, unsigned int flags, struct page **pagep, void **fsdata)
{
    simplefs_sb_info *l_sb_info = file->f_inode->i_sb->s_fs_info;
    int ret = 0;
    uint32_t total_alloc_block_num = 0;

    ZUORU_ENTRY;
    // check if the write can be completed (enough space?)
    if (pos + len > SIMPLEFS_MAX_FILE_SIZE) {
        ZUORU_KO_LOG_ERR("write pos exceeds the max file size\n");
        return -ENOSPC;
    }

    // ZUORU:???
    total_alloc_block_num = max(pos + len, file->f_inode->i_size) / SIMPLEFS_BLOCK_SIZE;
    if (total_alloc_block_num > file->f_inode->i_blocks - 1) {
        total_alloc_block_num -= file->f_inode->i_blocks - 1;
    } else {
        total_alloc_block_num = 0;
    }

    if (total_alloc_block_num > l_sb_info->free_block_num) {
        ZUORU_KO_LOG_ERR("not enough free blocks to write\n");
        return -ENOSPC;
    }

    // prepare the write
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0)
    ret = block_write_begin(mapping, pos, len, pagep, simplefs_file_get_block);
#else
    ret = block_write_begin(mapping, pos, len, flags, pagep, simplefs_file_get_block);
#endif

    // if this failed, reclaim newly allocated blocks
    if (ret < 0) {
        ZUORU_KO_LOG_ERR("newly allocated blocks reclaim not implemented yet\n");
    }

    ZUORU_EXIT;
    return ret;
}
#endif

static int simplefs_write_end(struct file *file, struct address_space *mapping,
    loff_t pos, unsigned int len, unsigned int copied, struct page *page, void *fsdata)
{
    struct inode *l_inode = file->f_inode;
    simplefs_inode_info *l_inode_info = SIMPLEFS_GET_INODE_INFO_FROM_INODE(l_inode);
    struct super_block *l_sb = l_inode->i_sb;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 5, 0)
    struct timespec64 cur_time;
#endif
    uint32_t total_block_old = 0;
    int ret = 0;
    struct buffer_head *bh_index = NULL;
    simplefs_file_ei_block *index_block = NULL;
    int first_ext;

    ZUORU_ENTRY;
    // complete the write()
    ret = generic_write_end(file, mapping, pos, len, copied, page, fsdata);
    if (ret < len) {
        ZUORU_KO_LOG_ERR("write less than requested\n");
        return ret;
    }

    // update inode metadata
    total_block_old = l_inode->i_blocks;
    l_inode->i_blocks = l_inode->i_size / SIMPLEFS_BLOCK_SIZE + 2; // ZUORU: ???, +2?

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 5, 0)
    cur_time = current_time(inode);
    l_inode->i_mtime = cur_time;
    inode_set_ctime_to_ts(l_inode, cur_time);
#else
    l_inode->i_mtime = l_inode->i_ctime = current_time(l_inode);
#endif

    mark_inode_dirty(l_inode); // ZUORU: ???, mark dirty later?

    // if file is smaller than before, free unused blocks
    if (total_block_old > l_inode->i_blocks) {
        // free unused blocks from page cache
        truncate_pagecache(l_inode, l_inode->i_size);

        // read ei_block to remove unused blocks
        bh_index = sb_bread(l_sb, l_inode_info->i_extent_block);
        if (!bh_index) {
            ZUORU_KO_LOG_ERR("truncating read index block failed %s, lost %llu blocks\n",
                file->f_path.dentry->d_name.name, total_block_old - l_inode->i_blocks);
            goto out_end;
        }
        index_block = (simplefs_file_ei_block*)bh_index->b_data;

        first_ext = simplefs_ext_search_blk(index_block, l_inode->i_blocks - 1);
        // reserve unused block in last extent
        if (l_inode->i_blocks - 1 != index_block->extents[first_ext].e_p_block) {
            first_ext++; // ZUORU: ???
        }

        for (int i = first_ext; i < SIMPLEFS_MAX_EXTENTS; i++) {
            if (!index_block->extents[i].e_p_block) {
                break;
            }
            put_blocks(l_sb->s_fs_info, index_block->extents[i].e_p_block,
                index_block->extents[i].e_len);
            memset(&index_block->extents[i], 0, sizeof(simplefs_extent));
        }
        mark_buffer_dirty(bh_index);
        brelse(bh_index);
    }

out_end:
    ZUORU_EXIT;
    return ret;
}

/**
 * @brief called by the page cache to write a dirty page to
 * the physical disk (when sync is called or when memory is needed)
 *
 * @param page ptr to the page
 * @param wbc writeback control
 * @return int ret
 */
static int simplefs_writepage(struct page *page, struct writeback_control *wbc)
{
    ZUORU_ENTRY;
    ZUORU_EXIT;
    return block_write_full_page(page, simplefs_file_get_block, wbc);
}

const struct address_space_operations simplefs_address_ops = {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0)
    .readahead = simplefs_readahead,
#else
    .readpage = simplefs_readpage,
#endif
    .writepage = simplefs_writepage,
    .write_begin = simplefs_write_begin,
    .write_end = simplefs_write_end,
};

const struct file_operations simplefs_file_ops = {
    .owner = THIS_MODULE,
    .llseek = generic_file_llseek,
    .read_iter = generic_file_read_iter,
    .write_iter = generic_file_write_iter,
    .fsync = generic_file_fsync,
};

const struct file_operations* simplefs_get_inode_file_op(void)
{
    return &simplefs_file_ops;
}

const struct address_space_operations* simplefs_get_address_op(void)
{
    return &simplefs_address_ops;
}
