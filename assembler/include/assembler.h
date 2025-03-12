#ifndef _HASSEMBLER
#define _HASSEMBLER

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "common.h"
#include "proccessor.h"


const int LABELS_SIZE = 128;
const size_t LABEL_NAME = 20;

typedef struct
{
        char name[LABEL_NAME];
        int value;
} Label;

typedef struct Assem
{
    int *code = NULL;
    int CODE_SIZE;
    const char *file_name;
    int label_count = 0;
    char *listing = NULL;

    Label Labels[LABELS_SIZE];
} Assem;

CodeError AssemblyLabels(char **buffer, FILE *file_code, Assem *Asm, int cmd_code);
void CtorAssembly(FILE **file_asm, FILE **file_code, Assem *Asm, char **buffer, size_t *file_size);
void DtorAssembly(FILE *file_code);
int ReadCommand(FILE *file_asm, char *cmd);
int GetCommandCode(const char *cmd, size_t count_command);
void CheckArgsAsm(int argc, char *argv[], Assem *Asm);
int FirstPassFile(char *buffer, Assem *Asm);
int FindLabel(Assem *Asm, char *cmd);
const char* Assembler(Assem *Asm);
void FillBufferCode(Assem *Asm, FILE *file_code);
void WriteBinFile(Assem *Asm);
CodeError AssemblyArgType(Assem *Asm, char **buffer, FILE *file_code, int cmd_code);
void CheckLabels(char *cmd, Assem *Asm, int CODE_SIZE);
int FindFunc(Assem *Asm, char *cmd);
void ReadFileToBuffer(FILE *file_asm, char **buffer, size_t *file_size);
char* SkipSpace(char* current_pos);
void RemoveSpaces(char* str);
CodeError HandleMemoryAccess(FILE* file_code, char* arg);
bool IsComplexArgument(const char *arg);

#endif //HASSEMBLER
