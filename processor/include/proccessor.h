#ifndef _HPROCCESSOR
#define _HPROCCESSOR

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "common.h"


const int SIZE_REGISTERS = 10;

typedef struct CPU
{
    stackElem *code;
    int IP = 0;
    stackElem registers[SIZE_REGISTERS] = {0};
} CPU;

#define CONDITIONAL_JMP(condition)                        \
    do                                                    \
    {                                                     \
        stackElem val_1 = 0, val_2 = 0;                   \
        GetProcInstruction(cmd, &proc);                   \
        LOG(LOGL_DEBUG, "");                              \
                                                          \
        stackPop(&stk, &val_1);                           \
        stackPop(&stk, &val_2);                           \
                                                          \
        if ((val_2) condition (val_1))                    \
        {                                                 \
            proc.IP = proc.code[proc.IP + 1];             \
        }                                                 \
        else                                              \
        {                                                 \
            proc.IP += 2;                                 \
        }                                                 \
    } while(0)

void CheckArgsProc(int argc, char *argv[]);
int FillingCodeArray(CPU *proc);
const char* CommandToString(int cmd);
const char* Run();
size_t GetBinFileSize(FILE *bin_file);
void IpCounter(CPU *proc, stackElem cmd, int count_command);
void SingleStackOperation(stack *stk, double (*operation)(double));
void TwoElemStackOperation(stack *stk, stackElem (*operation)(stackElem a, stackElem b));
int ProcessingStackCommands(CPU *proc, stack *stk, int cmd, bool IsPush, bool IsPushr, bool IsPopr);

#endif //HPROCCESSOR
