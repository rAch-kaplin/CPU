#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "color.h"
#include "common.h"
#include "CommonProcAssem.h"
#include "assembler.h"

typedef struct
{
    const char *cmd_name;
    const int cmd_code;
} CommandCode;

int GetCommandCode(const char *cmd)
{
    CommandCode command_code[] = {  {"push",    CMD_PUSH},
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

    int count_command = sizeof(command_code) / sizeof(command_code[0]);

    for (int i = 0; i < count_command; i++)
    {
        if (strcmp(cmd, command_code[i].cmd_name) == 0)
        {
            return command_code[i].cmd_code;
        }
    }

    return 0;
}

const char* Assembler(Assem *Asm)
{
    FILE *file_asm = fopen(Asm->file_name, "r");
    if (file_asm == nullptr)
    {
        return "invalid file_asm couldn't be opened: ";
    }

    FILE *file_code = fopen("programms/code.txt", "w+");
        if (file_code == nullptr)
    {
        return "file_code can't open";
    }

    const int CODE_SIZE = NumberCommands(file_asm, Asm);
    fseek(file_asm, 0, SEEK_SET);

    fprintf(file_code, "%d\n", CODE_SIZE);

    while (true)
    {
        char cmd[20] = "";
        if (fscanf(file_asm, "%19s", cmd) != 1)
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
                break;
                //TODO: make func
            }

            case CMD_POP:
            {
                fprintf(file_code, "%d\n", cmd_code);
                int value = 0;
                fscanf(file_asm, "%d", &value);
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

    // for (int i = 0; i < CODE_SIZE; i++)
    // {
    //     printf("&&&& --- %d\n", Asm->labels[i]);
    // }

    fclose(file_asm);
    fclose(file_code);
    return NULL;
}



int CompileArg(const char *str)
{
    if (strcmp(str, "ax") == 0) return 0;
    if (strcmp(str, "bx") == 0) return 1;
    if (strcmp(str, "cx") == 0) return 2;
    if (strcmp(str, "dx") == 0) return 3;

    return -1;
}

int NumberCommands(FILE *file_asm, Assem *Asm)
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
