#include <stdio.h>
#include "logger.h"

void GetProcInstruction(LogLevel DepthMsg, int *cmd)
{
    int current_len = sprintf(GetLogger()->stack_state,
                "\tEnter command: %d\n", &cmd);
}
