#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "color.h"
#include "common.h"
#include "CommonProcAssem.h"
#include "assembler.h"

const char* Assembler(Assem *Asm)
{
    FILE *file_asm = NULL, *file_code = NULL;
    CtorAssembly(&file_asm, &file_code, Asm);

    while (true)
    {
        char cmd[20] = "";
        ReadingCommand(file_asm, &cmd[0]);

        size_t count_command = sizeof(command_code) / sizeof(command_code[0]);
        int cmd_code = GetCommandCode(cmd, count_command);

        switch (cmd_code)
        {
            case CMD_PUSH:
            {
                fprintf(file_code, "%d ", cmd_code);
                int value = 0;
                fscanf(file_asm, "%d", &value);
                fprintf(file_code, "%d\n", value);
                break;
            }

            case CMD_PUSHR:
            case CMD_POPR:
            {
                fprintf(file_code, "%d ", cmd_code);
                char reg[10] = {0};
                fscanf(file_asm, "%s", reg);
                fprintf(file_code, "%d\n", CompileArg(reg));
                break;
            }

            case CMD_POP:
            case CMD_ADD:
            case CMD_SUB:
            case CMD_OUT:
            case CMD_DIV:
            case CMD_MUL:
            {
                fprintf(file_code, "%d\n", cmd_code);
                break;
            }

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

        if (cmd_code == CMD_HLT)
        {
            fprintf(file_code, "%d\n", cmd_code);
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
    if (label_index != -10)
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
    if (strcmp(str, "ax") == 0) return 0;
    if (strcmp(str, "bx") == 0) return 1;
    if (strcmp(str, "cx") == 0) return 2;
    if (strcmp(str, "dx") == 0) return 3;

    return -1;
}  //FIXME: struct

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
            printf("!!!!!!%s\n", cmd);
            return -5;
        }
        return 0;
}

int FirstPassFile(FILE *file_asm, Assem *Asm)
{
    int CODE_SIZE = 0;
    while(true)
        {
            char cmd[20] = "";
            if (fscanf(file_asm, "%s", cmd) != 1)
            {
                printf("the string incorrectly\n");
                return -1;
            }

            size_t count_command = sizeof(command_code) / sizeof(command_code[0]);
            int cmd_code = GetCommandCode(cmd, count_command);

            switch (cmd_code)
            {
                case CMD_PUSH:
                case CMD_PUSHR:
                case CMD_POPR:
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
                {
                    CODE_SIZE += 1;
                    break;
                }
                case CMD_JA:
                case CMD_JAE:
                case CMD_JB:
                case CMD_JBE:
                case CMD_JE:
                case CMD_JNE:
                {
                    fscanf(file_asm, "%s", cmd);
                    CODE_SIZE += 2;
                    break;
                }

                default:
                {
                    if (strcmp(&cmd[strlen(cmd) - 1], ":") == 0)
                    {
                        cmd[strlen(cmd) - 1] = '\0';
                        strcpy(Asm->Labels[Asm->label_count].name, cmd);
                        Asm->Labels[Asm->label_count].value = CODE_SIZE;
                        Asm->label_count++;
                    }

                    break;
                }
            }

            if (cmd_code == CMD_HLT)
            {
                CODE_SIZE += 1;
                break;
            }
        }

    return CODE_SIZE;
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

    return -10;
}


