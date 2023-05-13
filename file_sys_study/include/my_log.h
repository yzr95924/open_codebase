/**
 * @file my_log.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief my log implement
 * @version 0.1
 * @date 2023-05-14
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MY_LOG_H
#define MY_LOG_H

#include <time.h>
#include <stdio.h>
#include <string.h>

typedef enum {
    NO_LOG_LEVEL = 0,
    ERROR_LOG_LEVEL = 1,
    INFO_LOG_LEVEL = 2,
    DEBUG_LOG_LEVEL = 3
} LOG_LEVEL_TYPE_T;

#ifndef LOG_LEVEL
#define LOG_LEVEL DEBUG_LOG_LEVEL
#endif

#define LOG_TIME_BUF_SIZE (64)

#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__
#define LOG_FMT "%s | %s | %s | %s | %s:%d | %s"
#define LOG_ARGS(TIME_BUF, LOG_TAG, MODULE_NAME) TIME_BUF, LOG_TAG, MODULE_NAME, _FILE, __FUNCTION__, __LINE__
#define ERROR_LOG_TAG "ERROR"
#define INFO_LOG_TAG "INFO"
#define DEBUG_LOG_TAG "DEBUG"

static inline void TimeNow(char *inputBuf)
{
    time_t rawTime;
    struct tm *timeInfo;
    struct tm tmpTime;

    time(&rawTime);
    timeInfo = localtime_r(&rawTime, &tmpTime);

    strftime(inputBuf, LOG_TIME_BUF_SIZE, "%Y-%m-%d %H:%M:%S", timeInfo);
    return;
}

static inline void Logging(LOG_LEVEL_TYPE_T logType, const char *logModule, const char *fmt, ...)
{
    char inputTimeBuf[LOG_TIME_BUF_SIZE] = { 0 };
    char msgBuf[BUFSIZ] = { 0 };
    if (logType > LOG_LEVEL) {
        return;
    }

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(msgBuf, BUFSIZ, fmt, ap);
    va_end(ap);

    TimeNow(inputTimeBuf);
    switch (logType) {
        case NO_LOG_LEVEL:
            return;
        case ERROR_LOG_LEVEL:
            fprintf(stderr, LOG_FMT, LOG_ARGS(inputTimeBuf, ERROR_LOG_TAG, logModule), msgBuf);
            break;
        case INFO_LOG_LEVEL:
            fprintf(stderr, LOG_FMT, LOG_ARGS(inputTimeBuf, INFO_LOG_TAG, logModule), msgBuf);
            break;
        case DEBUG_LOG_LEVEL:
            fprintf(stderr, LOG_FMT, LOG_ARGS(inputTimeBuf, DEBUG_LOG_TAG, logModule), msgBuf);
            break;
    }
    return;
}

#endif
