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

typedef struct CPU
{
    stackElem *code;
    int IP;
    stackElem registers[SIZE_REGISTERS] = {0};
} CPU;

void FillingCodeArray(CPU *proc);
const char* CommandToString(int cmd);
const char* Run();
void SingleStackOperation(stack *stk, double (*operation)(double));
void TwoElemStackOperation(stack *stk, stackElem (*operation)(stackElem a, stackElem b));

#endif //HPROCCESSOR
