#ifndef _HLOGGER
#define _HLOGGER

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

const int SIZE_BUFFER = 4096;

enum LogLevel
{
    LOGL_DEBUG = 30,
    LOGL_INFO  = 100,
    LOGL_ERROR = 200
};

typedef struct Logger {
    LogLevel levelLogger;
    FILE *logFile;
    char stack_state[SIZE_BUFFER];
    char proc_instruction[SIZE_BUFFER];
} Logger;

Logger* GetLogger();
bool shouldLog(LogLevel levelMsg);
int loggerInit(LogLevel levelLogger, const char *log_file_name);
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
        fprintf(GetLogger()->logFile, "\n%s", GetLogger()->stack_state);      \
        fprintf(GetLogger()->logFile, "\n%s", GetLogger()->proc_instruction); \
    } while(0)

#define LOG_END()                                                               \
    do {                                                                        \
        fprintf(GetLogger()->logFile, "\n");                                    \
        memset(GetLogger()->stack_state, 0, sizeof(GetLogger()->stack_state));  \
        fflush(GetLogger()->logFile);                                           \
    } while(0)

#endif //_HLOGGER
