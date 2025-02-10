#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "proccessor.h"


int GetCommandCode(const char *cmd)
{
    if (strcmp(cmd, "push") == 0)   return CMD_PUSH;
    if (strcmp(cmd, "add") == 0)    return CMD_ADD;
    if (strcmp(cmd, "sub") == 0)    return CMD_SUB;
    if (strcmp(cmd, "out") == 0)    return CMD_OUT;
    if (strcmp(cmd, "div") == 0)    return CMD_DIV;
    if (strcmp(cmd, "mul") == 0)    return CMD_MUL;
    if (strcmp(cmd, "hlt") == 0)    return CMD_HLT;
    if (strcmp(cmd, "pushr") == 0)  return CMD_PUSHR;
    if (strcmp(cmd, "popr") == 0)   return CMD_POPR;
    if (strcmp(cmd, "jmp") == 0)    return CMD_JMP;
    if (strcmp(cmd, "sqrt") == 0)   return CMD_SQRT;
    if (strcmp(cmd, "sin") == 0)    return CMD_SIN;
    if (strcmp(cmd, "cos") == 0)    return CMD_COS;
    if (strcmp(cmd, "jb") == 0)     return CMD_JB;
    if (strcmp(cmd, "jbe") == 0)    return CMD_JBE;
    if (strcmp(cmd, "ja") == 0)     return CMD_JA;
    if (strcmp(cmd, "jae") == 0)    return CMD_JAE;
    if (strcmp(cmd, "je") == 0)     return CMD_JE;
    if (strcmp(cmd, "jne") == 0)    return CMD_JNE;

    return 0;
}

void Assembler()
{
    FILE *file_asm = fopen("kvadrat.txt", "r");
    if (file_asm == nullptr)
    {
        printf("file_asm == nullptr");
        assert(0);
    }

    FILE *file_code = fopen("code.txt", "w+");
        if (file_code == nullptr)
    {
        printf("file_code == nullptr");
        assert(0);
    }

    int CODE_SIZE = NumberCommands(file_asm);

    fprintf(file_code, "%d\n", CODE_SIZE);

    while(true)
    {
        char cmd[20] = "";
        if (fscanf(file_asm, "%s", cmd) != 1)
        {
            printf("!!!!!!%s\n", cmd);
            printf("the string incorrectly\n");
            break;
        }

        int cmd_code = GetCommandCode(cmd);

        switch (cmd_code)
        {
            case CMD_PUSH:
            {
                fprintf(file_code, "%d ", cmd_code);
                int value = 0;
                fscanf(file_asm, "%d", &value);
                fprintf(file_code, "%d\n", value);
                CODE_SIZE += 2;
                break;
            }

            case CMD_PUSHR:
            {
                fprintf(file_code, "%d ", cmd_code);
                char reg[10] = {0};
                fscanf(file_asm, "%s", reg);
                fprintf(file_code, "%d\n", CompileArg(reg));
                CODE_SIZE += 2;
                break;
            }

            case CMD_POPR:
            {
                fprintf(file_code, "%d ", cmd_code);
                char reg[10] = {0};
                fscanf(file_asm, "%s", reg);
                fprintf(file_code, "%d\n", CompileArg(reg));
                CODE_SIZE += 2;
                break;
            }

            case CMD_ADD:
            {
                fprintf(file_code, "%d\n", cmd_code);
                CODE_SIZE += 1;
                break;
            }

            case CMD_SUB:
            {
                fprintf(file_code, "%d\n", cmd_code);
                CODE_SIZE += 1;
                break;
            }

            case CMD_OUT:
            {
                fprintf(file_code, "%d\n", cmd_code);
                CODE_SIZE += 1;
                break;
            }

            case CMD_DIV:
            {
                fprintf(file_code, "%d\n", cmd_code);
                CODE_SIZE += 1;
                break;
            }

            case CMD_MUL:
            {
                fprintf(file_code, "%d\n", cmd_code);
                CODE_SIZE += 1;
                break;
            }

            case CMD_JMP:
            {
                fprintf(file_code, "%d ", cmd_code);

                int next = 0;
                fscanf(file_asm, "%d", &next);
                fprintf(file_code, "%d\n", next);

                CODE_SIZE += 2;
                break;
            }

            case CMD_JA:
            {
                fprintf(file_code, "%d\n", cmd_code);
                CODE_SIZE += 1;
                break;
            }

            case CMD_JB:
            {
                fprintf(file_code, "%d\n", cmd_code);
                CODE_SIZE += 1;
                break;
            }

            default:
                break;
        }

        if (cmd_code == CMD_HLT)
        {
            fprintf(file_code, "%d\n", cmd_code);
            CODE_SIZE += 1;
            break;
        }
    }

    fclose(file_asm);
    fclose(file_code);
}

void FillingCodeArray(CPU *proc)
{
    FILE *file_code = fopen("code.txt", "r");
    if (file_code == nullptr)
    {
        printf("Error: file_code == nullptr\n");
        assert(0);
    }

    int CODE_SIZE_BUFFER = 0;
    fscanf(file_code, "%d", &CODE_SIZE_BUFFER);

    proc->code = (int*)calloc((size_t)CODE_SIZE_BUFFER + 1, sizeof(int));

    for (int i = 0; i < CODE_SIZE_BUFFER + 1; i++)
    {
        fscanf(file_code, "%d", &proc->code[i]);
        //printf("%d ", proc->code[i]);
    }
    //printf("\n");
    fclose(file_code);
}


int CompileArg(const char *str)
{
    if (strcmp(str, "ax") == 0) return 0;
    if (strcmp(str, "bx") == 0) return 1;
    if (strcmp(str, "cx") == 0) return 2;
    if (strcmp(str, "dx") == 0) return 3;

    return -1;
}


int NumberCommands(FILE *file_asm)
{
    int CODE_SIZE = 0;
    while(true)
        {
            char cmd[20] = "";
            if (fscanf(file_asm, "%s", cmd) != 1)
            {
                printf("!!!!!!%s\n", cmd);
                printf("the string incorrectly\n");
                break;
            }

            int cmd_code = GetCommandCode(cmd);

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
                case CMD_JA:
                case CMD_JB:
                {
                    CODE_SIZE += 1;
                    break;
                }

                default:
                    break;
            }

            if (cmd_code == CMD_HLT)
            {
                CODE_SIZE += 1;
                break;
            }
        }
    fseek(file_asm, 0, SEEK_SET);

    return CODE_SIZE;
}
