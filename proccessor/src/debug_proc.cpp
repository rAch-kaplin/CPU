#include <stdio.h>
#include <stdarg.h>
#include "logger.h"
#include "proccessor.h"
#include "debug_proc.h"
#include "color.h"
#include "common.h"

void GetProcInstruction(int cmd, ...)
{
    va_list args;
    va_start(args, cmd);

    Logger * log = GetLogger();

    int current_len = 0;

    if (GetLogger()->color_mode == COLOR_MODE)
    {
        current_len += snprintf(GetLogger()->proc_instruction, SIZE_BUFFER,
                COLOR_BLUE "Enter command: %s" COLOR_RESET, CommandToString(cmd));
    }
    else
    {
        current_len += snprintf(GetLogger()->proc_instruction, SIZE_BUFFER,
                "Enter command: %s", CommandToString(cmd));
    }

    switch (cmd)
    {
        case CMD_PUSH:
        {
            int value = va_arg(args, int);
            if (GetLogger()->color_mode == COLOR_MODE)
            {
                snprintf(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, COLOR_RED " %d" COLOR_RESET, value);
            }
            else
            {
                snprintf(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, " %d", value);
            }
            break;
        }

        case CMD_ADD:
        {
            int val1 = va_arg(args, int);
            int val2 = va_arg(args, int);

            if (GetLogger()->color_mode == COLOR_MODE)
            {
                snprintf(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, COLOR_RED " (%d + %d)" COLOR_RESET, val1, val2);
            }
            else
            {
                snprintf(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, " (%d + %d)", val1, val2);
            }

            break;
        }
        case CMD_SUB:
        {
            int val1 = va_arg(args, int);
            int val2 = va_arg(args, int);
            if (GetLogger()->color_mode == COLOR_MODE)
            {
                snprintf(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, COLOR_RED " (%d - %d)" COLOR_RESET, val1, val2);
            }
            else
            {
                snprintf(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, " (%d - %d)", val1, val2);
            }
            break;
        }
        case CMD_MUL:
        {
            int val1 = va_arg(args, int);
            int val2 = va_arg(args, int);

            if (GetLogger()->color_mode == COLOR_MODE)
            {
                snprintf(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, COLOR_RED " (%d * %d)" COLOR_RESET, val1, val2);
            }
            else
            {
                snprintf(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, " (%d * %d)", val1, val2);
            }
            break;
        }
        case CMD_DIV:
        {
            int val1 = va_arg(args, int);
            int val2 = va_arg(args, int);

            if (GetLogger()->color_mode == COLOR_MODE)
            {
                snprintf(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, COLOR_RED " (%d / %d)" COLOR_RESET, val1, val2);
            }
            else
            {
                snprintf(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, " (%d / %d)", val1, val2);
            }
            break;
        }

        case CMD_OUT:
        {
            int value = va_arg(args, int);

            if (GetLogger()->color_mode == COLOR_MODE)
            {
                snprintf(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, COLOR_RED " %d" COLOR_RESET, value);
            }
            else
            {
                snprintf(log->proc_instruction + current_len, SIZE_BUFFER - (size_t)current_len, " %d", value);
            }
            break;
        }

        default:
            break;
    }
    va_end(args);
}
