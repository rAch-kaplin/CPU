#ifndef _HPROCCESSOR
#define _HPROCCESSOR

#define ONDBG

#ifdef ONDBG
    #define DBG_PRINTF(...) printf(__VA_ARGS__)
#else
    #define DBG_PRINTF(...) ((void)0)
#endif

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

void Assembler();
int GetCommandCode(const char *cmd);
const char* CommandToString(int cmd);
void Run();

#endif
