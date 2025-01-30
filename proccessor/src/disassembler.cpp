#include "proccessor.h"

const char* CommandToString(int cmd)
{
    switch (cmd)
    {
        case CMD_PUSH: return "Push";
        case CMD_ADD: return "Add";
        case CMD_SUB: return "Sub";
        case CMD_OUT: return "Out";
        case CMD_DIV: return "Div";
        case CMD_MUL: return "Mul";
        case CMD_HLT: return "Hlt";
        default: return "Unknown";
    }
}

