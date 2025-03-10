//------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "logger.h"
#include "color.h"
#include "common.h"
#include "CommonProcAssem.h"
#include "assembler.h"

void RemoveSpaces(char* str);
CodeError HandleMemoryAccess(FILE* file_code, char* arg);

const char* Assembler(Assem *Asm)
{
    char *buffer = NULL;
    size_t file_size = 0;

    FILE *file_asm = NULL, *file_code = NULL;
    CtorAssembly(&file_asm, &file_code, Asm, &buffer, &file_size);

    const size_t count_command = sizeof(command_code) / sizeof(command_code[0]);
    char *current_pos = buffer;
    while (true)
    {
        current_pos = SkipSpace(current_pos);

        if (*current_pos == '\0')
        {
            break;
        }

        char cmd[30] = "";
        if (sscanf(current_pos, "%29s", cmd) != 1)
        {
            printf("the string incorrectly\n");
            return NULL;
        }

        current_pos += strlen(cmd);

        int cmd_code = GetCommandCode(cmd, count_command);

        switch (cmd_code)
        {
            case CMD_PUSH:
            case CMD_POP:
            {
                CodeError error = AssemblyArgType(current_pos, file_code, cmd_code);
                if (error == ARG_TYPE_ERROR)
                {
                    free(buffer);
                    return COLOR_RED "not correct arg" COLOR_RESET;
                }
                break;
            }

            case CMD_RET:
            case CMD_ADD:
            case CMD_SUB:
            case CMD_OUT:
            case CMD_DIV:
            case CMD_MUL:
            case CMD_HLT:
            case CMD_IN:
            case CMD_SQRT:
            {
                fprintf(file_code, "%d\n", cmd_code);
                break;
            }

            case CMD_FUNC:
            case CMD_JMP:
            case CMD_JA:
            case CMD_JAE:
            case CMD_JB:
            case CMD_JBE:
            case CMD_JE:
            case CMD_JNE:
            {
                CodeError error = AssemblyLabels(current_pos, file_code, Asm, cmd_code);
                if (error)
                {
                    return "LABEL ERROR!";
                }
                break;
            }

            default:
                break;
        }
    }

    fseek(file_code, 0, SEEK_SET);
    FillBufferCode(Asm, file_code);
    free(buffer);
    DtorAssembly(file_code);
    return NULL;
}

CodeError AssemblyLabels(char *buffer, FILE *file_code, Assem *Asm, int cmd_code)
{
    fprintf(file_code, "%d ", cmd_code);

    char *current_pos = buffer;

    current_pos = SkipSpace(current_pos);

    char label[30] = "";
    if (sscanf(current_pos, "%29s", label) != 1)
    {
        printf("the string incorrectly\n");
        return ARG_TYPE_ERROR;
    }

    printf(COLOR_GREEN "%s\n" COLOR_RESET, label);

    int label_index = FindLabel(Asm, label);
    if (label_index != -1)
    {
        fprintf(file_code, "%d\n", label_index);
    }
    else
    {
        printf(COLOR_RED "Error: Label not found\n" COLOR_RESET);
        return UNKNOW_LABEL;
    }

    current_pos += strlen(label);

    return ITS_OK;
}

void DtorAssembly(FILE *file_code)
{
    fclose(file_code);
}

void FillBufferCode(Assem *Asm, FILE *file_code)
{
    for (int i = 0; i < Asm->CODE_SIZE; i++)
    {
        fscanf(file_code, "%d", &Asm->code[i]);
    }

    for (int i = 0; i < Asm->CODE_SIZE + 1; i++)
    {
        printf("%d ", Asm->code[i]);
    }
        printf("\n");
}


int CompileArg(const char *str)
{
    Registers ArrayRegs[] = { {"ax", 0},
                              {"bx", 1},
                              {"cx", 2},
                              {"dx", 3}};

    int count_regs = sizeof(ArrayRegs) / sizeof(ArrayRegs[0]);
    for (int i = 0; i < count_regs; i++)
    {
        if (strcmp(str, ArrayRegs[i].reg_name) == 0)
        {
            return ArrayRegs[i].number_reg;
        }
    }
    return -1;
}

int GetCommandCode(const char *cmd, size_t count_command)
{
    for (size_t i = 0; i < count_command; i++)
    {
        if (strcmp(cmd, command_code[i].cmd_name) == 0)
        {
            return command_code[i].cmd_code;
        }
    }

    return 0;
}

void CtorAssembly(FILE **file_asm, FILE **file_code, Assem *Asm, char **buffer, size_t *file_size)
{
    *file_asm = fopen(Asm->file_name, "r");
    assert(*file_asm != nullptr);

    *file_code = fopen("programms/code.txt", "w+");
    assert(*file_code != nullptr);
    ReadFileToBuffer(*file_asm, buffer, file_size);

    // for (size_t i = 0; i < *file_size; i++)
    // {
    //     printf("%s ", buffer[i]);
    // }

    Asm->CODE_SIZE = FirstPassFile(*buffer, Asm);

    Asm->code = (int*)calloc((size_t)Asm->CODE_SIZE + 1, sizeof(int));
}

int ReadCommand(FILE *file_asm, char *cmd)
{
    if (fscanf(file_asm, "%19s", cmd) != 1)
    {
        if (feof(file_asm))
        {
            return -1;
        }

        return FILE_READ_ERROR;
    }
    return ITS_OK;
}

int FirstPassFile(char *buffer, Assem *Asm)
{
    int CODE_SIZE = 0;
    char *current_pos = buffer;
    while(true)
    {
        current_pos = SkipSpace(current_pos);

        if (*current_pos == '\0')
        {
            break;
        }

        char cmd[30] = "";
        if (sscanf(current_pos, "%29s", cmd) != 1)
        {
            printf("the string incorrectly\n");
            return -1;
        }

        current_pos += strlen(cmd);

        size_t count_command = sizeof(command_code) / sizeof(command_code[0]);
        int cmd_code = GetCommandCode(cmd, count_command);

        switch (cmd_code)
        {
            case CMD_PUSH:
            case CMD_POP:
            {
                CODE_SIZE += 4;
                break;
            }

            case CMD_SQRT:
            case CMD_ADD:
            case CMD_SUB:
            case CMD_OUT:
            case CMD_DIV:
            case CMD_MUL:
            case CMD_RET:
            case CMD_HLT:
            case CMD_IN:
            {
                CODE_SIZE += 1;
                break;
            }
            case CMD_FUNC:
            case CMD_JA:
            case CMD_JAE:
            case CMD_JB:
            case CMD_JBE:
            case CMD_JE:
            case CMD_JNE:
            case CMD_JMP:
            {
                char label[30] = "";
                sscanf(current_pos, "%s", label);
                current_pos += strlen(label) + 1;
                CODE_SIZE += 2;
                break;
            }

            default:
            {
                break;
            }
        }

        CheckLabels(&cmd[0], Asm, CODE_SIZE);
    }

    return CODE_SIZE;
}

void CheckLabels(char *cmd, Assem *Asm, int CODE_SIZE)
{
    if (strcmp(&cmd[strlen(cmd) - 1], ":") == 0)
    {
        cmd[strlen(cmd) - 1] = '\0';
        strcpy(Asm->Labels[Asm->label_count].name, cmd);
        Asm->Labels[Asm->label_count].value = CODE_SIZE;
        Asm->label_count++;
    }
}

int FindLabel(Assem *Asm, char *cmd)
{
    cmd[strlen(cmd) - 1] = '\0';
    for (int i = 0; i < LABELS_SIZE; i++)
    {
        if (strcmp(Asm->Labels[i].name, cmd) == 0)
        {
            return Asm->Labels[i].value;
        }
    }
    return -1;
}

int FindFunc(Assem *Asm, char *cmd)
{
    for (int i = 0; i < LABELS_SIZE; i++)
    {
        if (strcmp(Asm->Labels[i].name, cmd) == 0)
        {
            return Asm->Labels[i].value;
        }
    }
    return -10;
}


CodeError AssemblyArgType(char *buffer, FILE *file_code, int cmd_code)
{
    fprintf(file_code, "%d ", cmd_code);

    char *current_pos = buffer;
    current_pos = SkipSpace(current_pos);

    char arg[30] = "";
    char type_arg[30] = "";
    // if (sscanf(current_pos, "%29s", arg) != 1)
    // {
    //     printf("the string incorrectly\n");
    //     return ARG_TYPE_ERROR;
    // }
    sscanf(current_pos, "%29s", type_arg);

    if (strchr(type_arg, '['))
    {
        if (sscanf(current_pos, "%29[^\n]", arg) != 1)
        {
            printf("the string incorrectly\n");
            return ARG_TYPE_ERROR;
        }
    }

    else
    {
        if (sscanf(current_pos, "%29s", arg) != 1)
        {
            printf("the string incorrectly\n");
            return ARG_TYPE_ERROR;
        }
    }

    current_pos += strlen(arg);

    size_t size_arg = strlen(arg);

    if (arg[0] == '-' && size_arg > 1 && isdigit(arg[1]))
    {
        fprintf(file_code, "%d ", 1);
        fprintf(file_code, "%d\n", atoi(arg));
    }

    else if (isdigit(arg[0]))
    {
        fprintf(file_code, "%d ", 1);
        fprintf(file_code, "%d\n", atoi(arg));
    }

    else if ((arg[0] == '[' || arg[size_arg - 1] == ']'))
    {
        printf("<<%s>>\n", arg);
        CodeError error = HandleMemoryAccess(file_code, &arg[0]);
        if (error != ITS_OK)
        {
            return ARG_TYPE_ERROR;
        }
    }

    else if (!isdigit(arg[0]) && !isdigit(arg[1]))
    {
        int reg = CompileArg(arg);
        if (reg == -1)
        {
            return ARG_TYPE_ERROR;
        }
        fprintf(file_code, "%d ", 2);
        fprintf(file_code, "%d\n", reg);
    }

    return ITS_OK;
}

void ReadFileToBuffer(FILE *file_asm, char **buffer, size_t *file_size)
{
    fseek(file_asm, 0, SEEK_END);
    *file_size = (size_t)ftell(file_asm);
    fseek(file_asm, 0, SEEK_SET);

    *buffer = (char*)calloc(*file_size + 1, sizeof(char));
    if (*buffer == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for file buffer.\n");
        exit(1);
    }

    fread(*buffer, 1, *file_size, file_asm);
    fclose(file_asm);
}

char* SkipSpace(char* current_pos)
{
    while (*current_pos == ' ' || *current_pos == '\t' || *current_pos == '\n') {
        current_pos++;
    }
    return current_pos;
}

CodeError HandleMemoryAccess(FILE* file_code, char* arg)
{
    size_t size_arg = strlen(arg);
    printf(COLOR_BLUE "<%s>\n" COLOR_RESET, arg);

    arg[size_arg - 1] = '\0';
    char inner_arg[20];
    strncpy(inner_arg, arg + 1, size_arg - 2);
    inner_arg[size_arg - 2] = '\0';
    RemoveSpaces(inner_arg);

    printf(COLOR_YELLOW "<%s>\n" COLOR_RESET, inner_arg);

    char* plus_pos = strchr(inner_arg, '+');
    if (plus_pos)
    {
        *plus_pos = '\0';
        char* left_part = inner_arg;
        char* right_part = plus_pos + 1;

        int reg = CompileArg(left_part);
        int num = atoi(right_part);

        if (reg != -1)
        {
            printf("<<<%d|%d\n", reg, num);
            fprintf(file_code, "%d ", 7);
            fprintf(file_code, "%d %d\n", reg, num);
            return ITS_OK;
        }

        reg = CompileArg(right_part);
        num = atoi(left_part);

        if (reg != -1)
        {
            printf("<<<%d|%d\n", reg, num);
            fprintf(file_code, "%d ", 7);
            fprintf(file_code, "%d %d\n", reg, num);
            return ITS_OK;
        }
    }

    else
    {
        int reg = CompileArg(inner_arg);
        if (reg != -1)
        {
            fprintf(file_code, "%d ", 6);
            fprintf(file_code, "%d\n", reg);
            return ITS_OK;
        }

        int num = atoi(inner_arg);
        fprintf(file_code, "%d ", 6);
        fprintf(file_code, "%d\n", num);
        return ITS_OK;

    }
    return ARG_TYPE_ERROR;
}

void RemoveSpaces(char* str)
{
    char* dest = str;
    for (char* src = str; *src != '\0'; src++)
    {
        if (*src != ' ')
        {
            *dest = *src;
            dest++;
        }
    }
    *dest = '\0';
}

