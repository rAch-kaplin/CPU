#ifndef _HPROCCESSOR
#define _HPROCCESSOR

#define DBG
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "common.h"

#ifdef DBG
    #define DBG_PRINTF(...) printf(__VA_ARGS__)
#else
    #define DBG_PRINTF(...) ((void)0)
#endif

const int SIZE_REGISTERS = 10;
const int LABELS_SIZE = 128;
const size_t LABEL_NAME = 20;

typedef struct
{
        char name[LABEL_NAME];
        int value;
} Label;

typedef struct Assem
{
    const char *file_name;
    int label_count = 0;
    Label Labels[LABELS_SIZE];
} Assem;

typedef struct CPU
{
    stackElem *code;
    int IP;
    stackElem registers[SIZE_REGISTERS] = {0};
} CPU;

void FillingCodeArray(CPU *proc);
int CompileArg(const char *str);
int NumberCommands(FILE *file_asm, Assem *Asm);
int FindLabel(Assem *Asm, char *cmd);


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

const char* Assembler(Assem *Asm);
int GetCommandCode(const char *cmd);
const char* CommandToString(int cmd);
const char* Run();
void SingleStackOperation(stack *stk, double (*operation)(double));
void TwoElemStackOperation(stack *stk, stackElem (*operation)(stackElem a, stackElem b));

#endif //HPROCCESSOR
