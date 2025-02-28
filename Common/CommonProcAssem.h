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

    //CMD_PUSHR =    11,
    CMD_POP =     12,

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

    CMD_FUNC =     50,
    CMD_RET =      51,

    CMD_IN = 60,

    CMD_HLT =      -1
};

enum REG_T
{
    ax = 0,
    bx = 1,
    cx = 2,
    dx = 3
};

typedef struct
{
    const char *reg_name;
    int number_reg;
} Registers;

typedef struct
{
    const char *cmd_name;
    const int cmd_code;
    int quantity_args;
} CommandCode;

static const CommandCode command_code[] = { {"push",    CMD_PUSH,  2},
                                            {"add",     CMD_ADD,   0},
                                            {"sub",     CMD_SUB,   0},
                                            {"out",     CMD_OUT,   0},
                                            {"div",     CMD_DIV,   0},
                                            {"mul",     CMD_MUL,   0},
                                            {"hlt",     CMD_HLT,   0},
                                            {"pop",     CMD_POP,   2},
                                            {"jmp",     CMD_JMP,   1},
                                            {"sqrt",    CMD_SQRT,  0},
                                            {"sin",     CMD_SIN,   0},
                                            {"cos",     CMD_COS,   0},
                                            {"jb",      CMD_JB,    1},
                                            {"jbe",     CMD_JBE,   1},
                                            {"ja",      CMD_JA,    1},
                                            {"jae",     CMD_JAE,   1},
                                            {"je",      CMD_JE,    1},
                                            {"jne",     CMD_JNE,   1},
                                            {"call",    CMD_FUNC,  1},
                                            {"ret",     CMD_RET,   0},
                                            {"in",      CMD_IN,    0}};

int CompileArg(const char *str);

#endif //HCOMMON_PROC_ASSEM
