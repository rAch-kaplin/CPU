#ifndef _HASSEMBLER
#define _HASSEMBLER

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "common.h"


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


void CheckArgsAsm(int argc, char *argv[], Assem *Asm);
int NumberCommands(FILE *file_asm, Assem *Asm);
int FindLabel(Assem *Asm, char *cmd);
const char* Assembler(Assem *Asm);

#endif //HASSEMBLER
