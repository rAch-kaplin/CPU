#include <stdio.h>
#include "logger.h"
#include "assembler.h"
#include "debug_proc.h"

void GetProcInstruction(int cmd)
{
    /*int current_len = */snprintf(GetLogger()->proc_instruction, SIZE_BUFFER,
                " Enter command: %s", CommandToString(cmd));
}

// Почитать про snprintf и может заменить всё на него для безопасности.

