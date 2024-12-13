#include <stdbool.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include "logger.h"
#include "color.h"
#include "debug.h"


Logger* GetLogger()
{
    static Logger logger = {LOGL_DEBUG, NULL, {0}};
    return &logger;
}

int loggerInit(LogLevel levelLogger, const char *log_file_name)
{
    Logger *log = GetLogger();
    log->levelLogger = levelLogger;
    log->logFile = fopen(log_file_name, "w+");

    if (log->logFile == NULL)
    {
        fprintf(stderr, "logFile failed open\n");
        return -100;
    }

    return 0;
}

bool shouldLog(LogLevel levelMsg)
{
    return GetLogger()->levelLogger <= levelMsg;
}


const char* ColorLogMsg(const enum LogLevel levelMsg)
{
    switch (levelMsg)
    {
        case LOGL_DEBUG:
            return "[DEBUG]";
            break;

        case LOGL_INFO:
            return "[INFO]";
            break;

        case LOGL_ERROR:
            return "[ERROR]";
            break;

        default:
            break;
    }
    return "UNKNOW";
}


void log(LogLevel levelMsg, const char *file, size_t line, const char *func,  const char *fmt, ...)
{
    Logger *log = GetLogger();
    time_t time_now = time(NULL);
    struct tm *now = localtime(&time_now);
    char time_info[30] = {};
    strftime(time_info, sizeof(time_info), "%Y-%m-%d %H:%M:%S", now);

    if (!log->logFile)
    {
        fprintf(stderr, "logFile is NULL\n");
        return;
    }

    va_list args;
    va_start(args, fmt);
    fprintf(log->logFile, "[%s]%s[%s][%zu:%s]: ", time_info, ColorLogMsg(levelMsg), file , line, func);
    vfprintf(log->logFile, fmt, args);
    va_end(args);
}

void loggerDeinit()
{
    fclose(GetLogger()->logFile);
    GetLogger()->logFile = NULL;
}

void getStackState(stack* stk)
{
    stkNullCheck(stk);

    int current_len = sprintf(GetLogger()->stack_state,
                 "\tstack pointer = %p\n"
                 "\tCapacity: %zu\n"
                 "\tSize: %zd\n"
                 "\tData pointer: %p\n"
                 "\tData: ",
                 stk, stk->capacity, stk->size, stk->data);

    for (size_t i = 0; i < stk->capacity + 2; i++)
    {
        current_len += sprintf(GetLogger()->stack_state + current_len, " " STACK_ELEM_FORMAT, stk->data[i]);
    }
}


