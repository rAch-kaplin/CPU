#ifndef _HPROCCESSOR
#define _HPROCCESSOR

enum command
{
    CMD_PUSH = 1,
    CMD_ADD = 2,
    CMD_SUB = 3,
    CMD_OUT = 4,
    CMD_DIV = 5,
    CMD_MUL = 6,
    CMD_HLT = -1
};

void Compilator();
int GetCommandCode(const char *cmd);
const char* CommandToString(int cmd);
void Run();

#endif
