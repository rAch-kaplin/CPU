#include <stdio.h>
#include "logger.h"
#include "assembler.h"

void GetProcInstruction(int cmd)
{
    int current_len = sprintf(GetLogger()->proc_instruction,
                "\tEnter command: %s", CommandToString(cmd));
}

// Исправить распечатку в лог-файл, продумать как это делать лучше всего!!!
// Почитать про snprintf и может заменить всё на него для безопасности.
// Исправить состояние стека, вынести getStackState() из-под stackAssert()
// Убрать лишние распечатки состояния стека!

