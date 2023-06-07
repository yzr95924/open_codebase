/**
 * @file my_util.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief
 * @version 0.1
 * @date 2023-05-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MY_UTIL_H
#define MY_UTIL_H

#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <bits/stdc++.h>

#include "define_const.h"

inline double ZUORU_GetTimeDiff(struct timeval start_time, struct timeval end_time)
{
    double total_sec = 0;
    total_sec = static_cast<double>(end_time.tv_sec - start_time.tv_sec) * SEC_2_US +
        (end_time.tv_usec - start_time.tv_usec);
    total_sec /= SEC_2_US;
    return total_sec;
}

inline void ZUORU_PrintBinaryBuf(const uint8_t *buf, size_t buf_size)
{
    for (size_t i = 0; i < buf_size; i++) {
        fprintf(stdout, "%02x", buf[i]);
    }
    fprintf(stdout, "\n");
    return ;
}

inline uint64_t ZUORU_GetStrongSeed()
{
    uint64_t a = clock();
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    uint64_t b = currentTime.tv_sec * SEC_2_US + currentTime.tv_usec;
    uint64_t c = getpid();

    // Robert Jenkins' 96 bit Mix Function
    a = a - b;  a = a - c;  a = a ^ (c >> 13);
    b = b - c;  b = b - a;  b = b ^ (a << 8);
    c = c - a;  c = c - b;  c = c ^ (b >> 13);
    a = a - b;  a = a - c;  a = a ^ (c >> 12);
    b = b - c;  b = b - a;  b = b ^ (a << 16);
    c = c - a;  c = c - b;  c = c ^ (b >> 5);
    a = a - b;  a = a - c;  a = a ^ (c >> 3);
    b = b - c;  b = b - a;  b = b ^ (a << 10);
    c = c - a;  c = c - b;  c = c ^ (b >> 15);

    return c;
}

inline uint64_t ZUORU_GetMemUsage()
{
    const char *stat_file_path = "/proc/self/statm";
    FILE *stat_file_hdl = NULL;
    uint64_t total_vm_size;
    uint64_t total_vmrss_size;
    uint64_t page_size_KB = 0;

    stat_file_hdl = fopen(stat_file_path, "r");
    if (stat_file_hdl == NULL) {
        fprintf(stdout, "cannot open the stat file.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(stat_file_hdl, "%lu %lu", &total_vm_size, &total_vmrss_size);
    page_size_KB = sysconf(_SC_PAGESIZE) / 1024;
    fclose(stat_file_hdl);
    return (total_vmrss_size * page_size_KB);
}

inline void ZUORU_GenRandomStr(uint8_t *buf, size_t buf_size)
{
    uint8_t *pos;
    for (size_t idx = 0; idx < buf_size; idx++) {
        pos = buf + idx;
        *pos = (uint8_t)ALPHABET[rand() % sizeof(ALPHABET)];
    }
    return ;
}

#endif
