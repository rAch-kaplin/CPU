#ifndef _HPROCCESSOR
#define _HPROCCESSOR

//#define DBG

#ifdef DBG
    #define DBG_PRINTF(...) printf(__VA_ARGS__)
#else
    #define DBG_PRINTF(...) ((void)0)
#endif

enum command
{
    CMD_PUSH =      1,
    CMD_ADD =       2,
    CMD_SUB =       3,
    CMD_OUT =       4,
    CMD_DIV =       5,
    CMD_MUL =       6,

    CMD_PUSHR =    11,
    CMD_POPR =     12,

    CMD_JMP =      21,
    CMD_SQRT =     31,
    CMD_SIN =      32,
    CMD_COS =      33,

    CMD_JB =       41,
    CMD_JBE =      42,
    CMD_JA =       43,
    CMD_JAE =      44,
    CMD_JE =       45,
    CMD_JNE =      46,

    CMD_HLT =      -1
};

enum REG_T
{
    RAX = 0,
    RBX = 1,
    RCX = 2,
    RDX = 3
};

void Assembler();
int GetCommandCode(const char *cmd);
const char* CommandToString(int cmd);
void Run();

#endif
