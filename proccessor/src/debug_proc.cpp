#include <stdio.h>
#include <stdarg.h>
#include "logger.h"
#include "assembler.h"
#include "debug_proc.h"
#include "color.h"
#include "common.h"

#define COLOR

#ifdef COLOR
    #define SNPRINTF(buffer, SIZE_BUFFER, COLOR, fmt, ...) snprintf(buffer, SIZE_BUFFER, COLOR fmt COLOR_RESET, ##__VA_ARGS__)
#else
    #define SNPRINTF(buffer, SIZE_BUFFER, COLOR, fmt, ...) snprintf(buffer, SIZE_BUFFER,  fmt, ##__VA_ARGS__)
#endif

void GetProcInstruction(int cmd, ...)
{
    va_list args;
    va_start(args, cmd);

    Logger * log = GetLogger();


    int current_len = snprintf(GetLogger()->proc_instruction, SIZE_BUFFER,
                COLOR_BLUE "Enter command: %s" COLOR_RESET, CommandToString(cmd));

    switch (cmd)
    {
        case CMD_PUSH:
        {
            int value = va_arg(args, int);
            SNPRINTF(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, COLOR_RED, " %d", value);
            break;
        }

        case CMD_ADD:
        {
            int val1 = va_arg(args, int);
            int val2 = va_arg(args, int);
            SNPRINTF(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, COLOR_RED, " (%d + %d)", val1, val2);
            break;
        }
        case CMD_SUB:
        {
            int val1 = va_arg(args, int);
            int val2 = va_arg(args, int);
            SNPRINTF(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, COLOR_RED, " (%d - %d)", val1, val2);
            break;
        }
        case CMD_MUL:
        {
            int val1 = va_arg(args, int);
            int val2 = va_arg(args, int);
            SNPRINTF(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, COLOR_RED, " (%d * %d)", val1, val2);
            break;
        }
        case CMD_DIV:
        {
            int val1 = va_arg(args, int);
            int val2 = va_arg(args, int);
            SNPRINTF(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, COLOR_RED, " (%d / %d)", val1, val2);
            break;
        }

        case CMD_OUT:
        {
            int value = va_arg(args, int);
            SNPRINTF(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, COLOR_RED, " %d", value);
            break;
        }

        default:
            break;
    }

    va_end(args);
}
