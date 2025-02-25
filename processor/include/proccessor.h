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


void CheckArgsProc(int argc, char *argv[]);
int FillingCodeArray(CPU *proc);
const char* CommandToString(int cmd);
const char* Run();
size_t GetBinFileSize(FILE *bin_file);
void IpCounter(CPU *proc, stackElem cmd, int count_command);
void SingleStackOperation(stack *stk, double (*operation)(double));
void TwoElemStackOperation(stack *stk, stackElem (*operation)(stackElem a, stackElem b));

#endif //HPROCCESSOR
