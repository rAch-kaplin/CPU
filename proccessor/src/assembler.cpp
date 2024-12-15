#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "assembler.h"

int GetCommandCode(const char *cmd)
{
    if (strcmp(cmd, "Push") == 0) return CMD_PUSH;
    if (strcmp(cmd, "Add") == 0) return CMD_ADD;
    if (strcmp(cmd, "Sub") == 0) return CMD_SUB;
    if (strcmp(cmd, "Out") == 0) return CMD_OUT;
    if (strcmp(cmd, "Div") == 0) return CMD_DIV;
    if (strcmp(cmd, "Mul") == 0) return CMD_MUL;
    if (strcmp(cmd, "Hlt") == 0) return CMD_HLT;
    return 0;
}


void Assembler()
{
    FILE *file_asm = fopen("Programm_asm.txt", "r");
    if (file_asm == nullptr)
    {
        printf("file_asm == nullptr");
        assert(0);
    }

    FILE *file_code = fopen("Programm_code.txt", "w");
        if (file_code == nullptr)
    {
        printf("file_code == nullptr");
        assert(0);
    }

    while(true)
    {
        char cmd[20] = "";
        if (fscanf(file_asm, "%s", cmd) != 1)
        {
            printf("!!!!!!%s\n", cmd);
            printf("the string incorrectly\n");
            break;
        }
        //printf("<----%s\n", cmd);
        int cmd_code = GetCommandCode(cmd);

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

            case CMD_ADD:
            {
                fprintf(file_code, "%d\n", cmd_code);
                break;
            }

            case CMD_SUB:
            {
                fprintf(file_code, "%d\n", cmd_code);
                break;
            }

            case CMD_OUT:
            {
                fprintf(file_code, "%d\n", cmd_code);
                break;
            }

            case CMD_DIV:
            {
                fprintf(file_code, "%d\n", cmd_code);
                break;
            }

            case CMD_MUL:
            {
                fprintf(file_code, "%d\n", cmd_code);
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
    fclose(file_asm);
    fclose(file_code);
}
