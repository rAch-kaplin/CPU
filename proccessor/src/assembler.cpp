#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "proccessor.h"

int GetCommandCode(const char *cmd)
{
    if (strcmp(cmd, "push") == 0) return CMD_PUSH;
    if (strcmp(cmd, "add") == 0) return CMD_ADD;
    if (strcmp(cmd, "sub") == 0) return CMD_SUB;
    if (strcmp(cmd, "out") == 0) return CMD_OUT;
    if (strcmp(cmd, "div") == 0) return CMD_DIV;
    if (strcmp(cmd, "mul") == 0) return CMD_MUL;
    if (strcmp(cmd, "hlt") == 0) return CMD_HLT;
    if (strcmp(cmd, "pushr") == 0) return CMD_PUSHR;
    if (strcmp(cmd, "popr") == 0) return CMD_POPR;
    if (strcmp(cmd, "jmp") == 0) return CMD_JMP;
    if (strcmp(cmd, "sqrt") == 0) return CMD_SQRT;
    if (strcmp(cmd, "sin") == 0) return CMD_SIN;
    if (strcmp(cmd, "cos") == 0) return CMD_COS;
    if (strcmp(cmd, "jb") == 0) return CMD_JB;
    if (strcmp(cmd, "jbe") == 0) return CMD_JBE;
    if (strcmp(cmd, "ja") == 0) return CMD_JA;
    if (strcmp(cmd, "jae") == 0) return CMD_JAE;
    if (strcmp(cmd, "je") == 0) return CMD_JE;
    if (strcmp(cmd, "jne") == 0) return CMD_JNE;

    return 0;
}

int CompileArg(const char *str);

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

    int CODE_SIZE = 0;

    //FILE *temp_file = fopen("temp_file.txt", "w");


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

    //printf("%d\n",  CODE_SIZE);

    //fprintf(temp_file, "%d\n", CODE_SIZE);
    // char ch;
    // while ((ch = fgetc(file_code)) != EOF)
    // {
    //     fputc(ch, temp_file);
    // }

    //fclose(temp_file);
    fclose(file_asm);
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
