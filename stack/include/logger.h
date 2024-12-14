#ifndef _HLOGGER
#define _HLOGGER

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

enum LogLevel
{
    LOGL_DEBUG = 0,
    LOGL_INFO  = 1,
    LOGL_ERROR = 2
};


typedef struct Logger {
    LogLevel levelLogger;
    FILE *logFile;
    char stack_state[4096];
} Logger;

// typedef struct Logger Logger;
Logger* GetLogger();
bool shouldLog(LogLevel levelMsg);
int loggerInit(LogLevel levelLogger, const char *log_file_name);
void getStackState(stack* stk);
void loggerDeinit();
const char* ColorLogMsg(const enum LogLevel levelMsg);
void log(LogLevel levelMsg, const char *file, size_t line, const char *func,  const char *fmt, ...);

#define LOG(levelMsg, fmt, ...)                   \
    do {                                          \
        LOG_BEGIN(levelMsg, fmt, ##__VA_ARGS__);  \
        LOG_MSG(fmt);                             \
        LOG_END();                                \
    } while(0)

#define LOG_BEGIN(levelMsg, fmt, ...)                                         \
    do {                                                                      \
        if (shouldLog(levelMsg))                                              \
        {                                                                     \
            log(levelMsg, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__);  \
        }                                                                     \
    } while(0)

#define LOG_MSG(fmt, ...)                                                     \
    do {                                                                      \
        getStackState(stk);                                                   \
        fprintf(GetLogger()->logFile, "\n%s", GetLogger()->stack_state);      \
    } while(0)

#define LOG_END()                                                               \
    do {                                                                        \
        fprintf(GetLogger()->logFile, "\n");                                    \
        memset(GetLogger()->stack_state, 0, sizeof(GetLogger()->stack_state));  \
        fflush(GetLogger()->logFile);                                           \
    } while(0)

#endif
