#ifndef _HDEBUG_PROC
#define _HDEBUG_PROC

#include "logger.h"

void AddArgsToCommand(Logger *log, int *current_len, const char *fmt, ...);
void GetProcInstruction(int cmd, ...);

#endif
