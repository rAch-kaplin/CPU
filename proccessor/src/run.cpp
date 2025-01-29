#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "color.h"
#include "assembler.h"
#include "stack.h"
#include "debug_proc.h"
#include "logger.h"

struct CPU
{
    int *code;
    int IP;
    int *registers;
};

const int SIZE_CODE_BUFFER = 20;

void FillingCodeArray(CPU *proc);

void Run()
{
    struct stack stk = {NULL, 0, 0};
    stackCtor(&stk, 8);

    struct CPU proc = {};

    FillingCodeArray(&proc);
    int next = 1;

    while (next)
    {
        int cmd = proc.code[proc.IP];

        DBG_PRINTF(COLOR_MAGENTA "%s\n" COLOR_RESET, CommandToString(cmd));

        switch (cmd)
        {
            case CMD_PUSH:
            {
                int value = proc.code[proc.IP + 1];

                DBG_PRINTF(COLOR_CYAN "Enter value: " COLOR_RESET);
                DBG_PRINTF(COLOR_MAGENTA "%d\n" COLOR_RESET, value);

                GetProcInstruction(cmd, value);
                LOG(LOGL_DEBUG, "");
                stackPush(&stk, value);
                proc.IP += 2;
                break;
            }

            case CMD_ADD:
            {
                int val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);
                GetProcInstruction(cmd, val_1, val_2);
                LOG(LOGL_DEBUG, "");
                stackPush(&stk, val_1 + val_2);
                proc.IP += 1;
                DBG_PRINTF(COLOR_MAGENTA "Add: %d\n" COLOR_RESET, val_1 + val_2);

                break;
            }

            case CMD_SUB:
            {
                int val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);
                GetProcInstruction(cmd, val_2, val_1);
                LOG(LOGL_DEBUG, "");
                stackPush(&stk, val_2 - val_1);
                DBG_PRINTF(COLOR_MAGENTA "Sub: %d\n" COLOR_RESET, val_2 - val_1);
                proc.IP += 1;

                break;
            }

            case CMD_MUL:
            {
                int val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);
                GetProcInstruction(cmd, val_1, val_2);
                LOG(LOGL_DEBUG, "");
                stackPush(&stk, val_1 * val_2);
                DBG_PRINTF(COLOR_MAGENTA "Mul: %d\n" COLOR_RESET, val_1 * val_2);
                proc.IP += 1;

                break;
            }

            case CMD_DIV:
            {
                int val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);
                GetProcInstruction(cmd, val_2, val_1);
                LOG(LOGL_DEBUG, "");
                stackPush(&stk, val_2 / val_1);
                DBG_PRINTF(COLOR_MAGENTA "Div: %d\n" COLOR_RESET, val_2 / val_1);
                proc.IP += 1;

                break;
            }
            case CMD_OUT:
            {
                int val = 0;
                stackPop(&stk, &val);
                DBG_PRINTF(COLOR_MAGENTA "Elem from stack: %d\n" COLOR_RESET, val);
                GetProcInstruction(cmd, val);
                LOG(LOGL_DEBUG, "");
                proc.IP += 1;

                break;
            }

            case CMD_HLT:
            {
                break;
            }

            default:
            {
                printf("Unknow command:(\n");
                break;
            }
        }

        if (cmd == CMD_HLT)
        {
            GetProcInstruction(cmd);
            LOG(LOGL_DEBUG, "");
            proc.IP += 1;

            break;
        }
    }
    free(proc.code);
    stackDtor(&stk);
}

void FillingCodeArray(CPU *proc)
{
    FILE *file_code = fopen("Programm_code.txt", "r");
    if (file_code == nullptr)
    {
        printf("Error: file_code == nullptr\n");
        assert(0);
    }

    proc->code = (int*)calloc(SIZE_CODE_BUFFER, sizeof(int));

    for (int i = 0; i < 20; i++)
    {
        fscanf(file_code, "%d", &proc->code[i]);
    }

    fclose(file_code);
}
