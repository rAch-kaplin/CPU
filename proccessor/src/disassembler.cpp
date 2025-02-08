#include "proccessor.h"

const char* CommandToString(int cmd)
{
    switch (cmd)
    {
        case CMD_PUSH: return "push";
        case CMD_ADD: return "add";
        case CMD_SUB: return "sub";
        case CMD_OUT: return "out";
        case CMD_DIV: return "div";
        case CMD_MUL: return "mul";
        case CMD_HLT: return "hlt";
        case CMD_PUSHR: return "pushr";
        case CMD_POPR: return "popr";
        case CMD_JMP: return "jmp";
        case CMD_JA: return "ja";

        //TODO: Дописать return

        default: return "Unknown";
    }
}

