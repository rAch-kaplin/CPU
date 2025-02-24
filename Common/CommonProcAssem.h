#ifndef _HCOMMON_PROC_ASSEM
#define _HCOMMON_PROC_ASSEM

enum command
{
    CMD_PUSH =      1,
    CMD_ADD =       2,
    CMD_SUB =       3,
    CMD_OUT =       4,
    CMD_DIV =       5,
    CMD_MUL =       6,
    CMD_POP =       7,

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
    ax = 0,
    bx = 1,
    cx = 2,
    dx = 3
};

int CompileArg(const char *str);
int GetCommandCode(const char *cmd);


#endif //HCOMMON_PROC_ASSEM
