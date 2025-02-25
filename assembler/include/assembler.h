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
    int *code;
    int CODE_SIZE;
    const char *file_name;
    int label_count = 0;
    Label Labels[LABELS_SIZE];
} Assem;

typedef struct
{
    const char *cmd_name;
    const int cmd_code;
} CommandCode;

static const CommandCode command_code[] = { {"push",    CMD_PUSH},
                                            {"add",     CMD_ADD},
                                            {"sub",     CMD_SUB},
                                            {"out",     CMD_OUT},
                                            {"div",     CMD_DIV},
                                            {"mul",     CMD_MUL},
                                            {"hlt",     CMD_HLT},
                                            {"pop",     CMD_POP},
                                            {"pushr",   CMD_PUSHR},
                                            {"popr",    CMD_POPR},
                                            {"jmp",     CMD_JMP},
                                            {"sqrt",    CMD_SQRT},
                                            {"sin",     CMD_SIN},
                                            {"cos",     CMD_COS},
                                            {"jb",      CMD_JB},
                                            {"jbe",     CMD_JBE},
                                            {"ja",      CMD_JA},
                                            {"jae",     CMD_JAE},
                                            {"je",      CMD_JE},
                                            {"jne",     CMD_JNE} };

void CtorAssembly(FILE **file_asm, FILE **file_code, Assem *Asm);
void DtorAssembly(FILE *file_asm, FILE *file_code);
int ReadingCommand(FILE *file_asm, char *cmd);
int GetCommandCode(const char *cmd, size_t count_command);
void CheckArgsAsm(int argc, char *argv[], Assem *Asm);
int FirstPassFile(FILE *file_asm, Assem *Asm);
int FindLabel(Assem *Asm, char *cmd);
const char* Assembler(Assem *Asm);
void FillBufferCode(Assem *Asm, FILE *file_code);
void WriteBinFile(Assem *Asm);

#endif //HASSEMBLER
