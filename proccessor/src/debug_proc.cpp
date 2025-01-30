#include <stdio.h>
#include <stdarg.h>
#include "logger.h"
#include "proccessor.h"
#include "debug_proc.h"
#include "color.h"
#include "common.h"

void AddArgsToCommand(Logger *log, int *current_len, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    if (log->color_mode == COLOR_MODE)
    {
        *current_len += snprintf(log->proc_instruction + *current_len, SIZE_BUFFER - (size_t)*current_len, COLOR_RED);
        *current_len += vsnprintf(log->proc_instruction + *current_len, SIZE_BUFFER - (size_t)*current_len, fmt, args);
        *current_len += snprintf(log->proc_instruction + *current_len, SIZE_BUFFER - (size_t)*current_len, COLOR_RESET);
    }
    else
    {
        *current_len += vsnprintf(log->proc_instruction + *current_len, SIZE_BUFFER - (size_t)*current_len, fmt, args);
    }
    va_end(args);
}

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
            stackElem value = va_arg(args, stackElem);
            AddArgsToCommand(log, &current_len, " %d", value);
            break;
        }
#if 1
        case CMD_ADD:
        {
            stackElem val1 = va_arg(args, stackElem);
            stackElem val2 = va_arg(args, stackElem);
            AddArgsToCommand(log, &current_len, " (%d + %d)", val1, val2);
            break;
        }
        case CMD_SUB:
        {
            stackElem val1 = va_arg(args, stackElem);
            stackElem val2 = va_arg(args, stackElem);
            AddArgsToCommand(log, &current_len, " (%d - %d)", val1, val2);
            break;
        }
        case CMD_MUL:
        {
            stackElem val1 = va_arg(args, stackElem);
            stackElem val2 = va_arg(args, stackElem);
            AddArgsToCommand(log, &current_len, " (%d * %d)", val1, val2);
            break;
        }
        case CMD_DIV:
        {
            stackElem val1 = va_arg(args, stackElem);
            stackElem val2 = va_arg(args, stackElem);
            AddArgsToCommand(log, &current_len, " (%d / %d)", val1, val2);
            break;
        }

        case CMD_OUT:
        {
            stackElem value = va_arg(args, stackElem);
            AddArgsToCommand(log, &current_len, " %d", value);
            break;
        }
#endif

        default:
            break;
    }

    va_end(args);
}



