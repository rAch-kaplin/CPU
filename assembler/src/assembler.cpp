#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "color.h"
#include "common.h"
#include "CommonProcAssem.h"
#include "assembler.h"

CodeError AssemblyArgType(FILE *file_asm, FILE *file_code, int cmd_code);
void CheckLabels(char *cmd, Assem *Asm, int CODE_SIZE);
int FindFunc(Assem *Asm, char *cmd);

const char* Assembler(Assem *Asm)
{
    FILE *file_asm = NULL, *file_code = NULL;
    CtorAssembly(&file_asm, &file_code, Asm);

    for (int i = 0; i < LABELS_SIZE; i++)
    {
        printf("%s ", Asm->Labels[i].name);
    }
    printf("\n");

    while (true)
    {
        char cmd[30] = "";
        int result = ReadingCommand(file_asm, &cmd[0]);
        if (result == -1)
        {
            break;
        }

        size_t count_command = sizeof(command_code) / sizeof(command_code[0]);
        int cmd_code = GetCommandCode(cmd, count_command);
        switch (cmd_code)
        {
            case CMD_PUSH:
            case CMD_POP:
            {
                CodeError error = AssemblyArgType(file_asm, file_code, cmd_code);
                if (error == ARG_TYPE_ERROR)
                {
                    return "not correct arg";
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
                CodeError error = AssemblyLabels(file_asm, file_code, Asm, cmd_code);
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

    DtorAssembly(file_asm, file_code);
    return NULL;
}

CodeError AssemblyLabels(FILE *file_asm, FILE *file_code, Assem *Asm, int cmd_code)
{
    fprintf(file_code, "%d ", cmd_code);
    char label[20] = "";
    fscanf(file_asm, "%s", label);
    int label_index = FindLabel(Asm, label);
    if (label_index != -1)
    {
        fprintf(file_code, "%d\n", label_index);
    }
    else
    {
        fprintf(file_code, "Error: Label not found\n");
        return UNKNOW_LABEL;
    }
    return ITS_OK;
}

void DtorAssembly(FILE *file_asm, FILE *file_code)
{
    fclose(file_asm);
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

void CtorAssembly(FILE **file_asm, FILE **file_code, Assem *Asm)
{
    *file_asm = fopen(Asm->file_name, "r");
    assert(*file_asm != nullptr);

    *file_code = fopen("programms/code.txt", "w+");
    assert(*file_code != nullptr);

    Asm->CODE_SIZE = FirstPassFile(*file_asm, Asm);
    fseek(*file_asm, 0, SEEK_SET);

    Asm->code = (int*)calloc((size_t)Asm->CODE_SIZE + 1, sizeof(int));
}

int ReadingCommand(FILE *file_asm, char *cmd)
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

int FirstPassFile(FILE *file_asm, Assem *Asm)
{
    int CODE_SIZE = 0;
    while(true)
    {
        char cmd[30] = "";
        if (fscanf(file_asm, "%29s", cmd) != 1)
        {
            if (feof(file_asm))
            {
                break;
            }

            printf("the string incorrectly\n");
            return -1;
        }

        size_t count_command = sizeof(command_code) / sizeof(command_code[0]);
        int cmd_code = GetCommandCode(cmd, count_command);

        switch (cmd_code)
        {
            case CMD_PUSH:
            case CMD_POP:
            {
                CODE_SIZE += 3;
                break;
            }
            case CMD_JMP:
            {
                CODE_SIZE += 2;
                break;
            }
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
            {
                char label[30] = "";
                fscanf(file_asm, "%s", label);
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


CodeError AssemblyArgType(FILE *file_asm, FILE *file_code, int cmd_code)
{
    fprintf(file_code, "%d ", cmd_code);

    char arg[10] = "";
    fscanf(file_asm, "%9s", arg);

    if (isdigit(arg[0]))
    {
        fprintf(file_code, "%d ", 1);
        fprintf(file_code, "%d\n", atoi(arg));
    }

    else if (!isdigit(arg[0]))
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
