#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "color.h"
#include "assembler.h"
#include "stack.h"
#include "debug_proc.h"
#include "logger.h"


void Run()
{
    struct stack stk = {NULL, 0, 0};

    stackCtor(&stk, 8);

    FILE *file_code = fopen("Programm_code.txt", "r");
    if (file_code == nullptr)
    {
        printf("Error: file_code == nullptr\n");
        assert(0);
    }

    while(true)
    {
        int cmd = 0;
        DBG_PRINTF(COLOR_CYAN "Enter command: " COLOR_RESET);
        if (fscanf(file_code, "%d\n", &cmd) != 1)
        {
            printf("%d\n", cmd);
            printf("the command incorrectly\n");
            assert(0);
        }
        //printf("!!!!!!!!!!\n%s\n", GetLogger()->stack_state);
        //GetProcInstruction(cmd);
        LOG(LOGL_DEBUG, "\tEnter command: %s", CommandToString(cmd));
        DBG_PRINTF(COLOR_MAGENTA "%s\n" COLOR_RESET, CommandToString(cmd));

        switch (cmd)
        {
            case CMD_PUSH:
            {
                int value = 0;
                DBG_PRINTF(COLOR_CYAN "Enter value: " COLOR_RESET);
                if (fscanf(file_code, "%d\n", &value) != 1)
                {
                    printf("the number incorrectly\n");
                    assert(0);
                }
                DBG_PRINTF(COLOR_MAGENTA "%d\n" COLOR_RESET, value);
                //LOG(LOGL_DEBUG, "Push\n");
                stackPush(&stk, value);
                break;
            }

            case CMD_ADD:
            {
                int val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                stackPush(&stk, val_1 + val_2);
                DBG_PRINTF(COLOR_MAGENTA "Add: %d\n" COLOR_RESET, val_1 + val_2);
                break;
            }

            case CMD_SUB:
            {
                int val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                stackPush(&stk, val_2 - val_1);
                DBG_PRINTF(COLOR_MAGENTA "Sub: %d\n" COLOR_RESET, val_2 - val_1);
                break;
            }

            case CMD_MUL:
            {
                int val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                stackPush(&stk, val_1 * val_2);
                DBG_PRINTF(COLOR_MAGENTA "Mul: %d\n" COLOR_RESET, val_1 * val_2);
                break;
            }

            case CMD_DIV:
            {
                int val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                stackPush(&stk, val_2 / val_1);
                DBG_PRINTF(COLOR_MAGENTA "Div: %d\n" COLOR_RESET, val_2 / val_1);
                break;
            }
            case CMD_OUT:
            {
                int val = 0;
                stackPop(&stk, &val);
                DBG_PRINTF(COLOR_MAGENTA "Elem from stack: %d\n" COLOR_RESET, val);
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
            fclose(file_code);
            break;
        }
    }
    stackDtor(&stk);
}
