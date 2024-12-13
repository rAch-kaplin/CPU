#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "proccessor.h"
#include "assembler.h"
#include "stack.h"

const char* CommandToString(int cmd)
{
    switch (cmd)
    {
        case CMD_PUSH: return "Push";
        case CMD_ADD: return "Add";
        case CMD_SUB: return "Sub";
        case CMD_OUT: return "Out";
        case CMD_DIV: return "Div";
        case CMD_MUL: return "Mul";
        case CMD_HLT: return "Hlt";
        default: return "Unknown";
    }
}

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
        printf("Enter command: ");
        if (fscanf(file_code, "%d\n", &cmd) != 1)
        {
            printf("%d\n", cmd);
            printf("the command incorrectly\n");
            assert(0);
        }
        printf("%s\n", CommandToString(cmd));

        switch (cmd)
        {
            case CMD_PUSH:
            {
                int value = 0;
                printf("Enter value: ");
                if (fscanf(file_code, "%d\n", &value) != 1)
                {
                    printf("the number incorrectly\n");
                    assert(0);
                }
                printf("%d\n", value);
                stackPush(&stk, value);
                break;
            }

            case CMD_ADD:
            {
                int val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                stackPush(&stk, val_1 + val_2);
                printf("Add: %d\n", val_1 + val_2);
                break;
            }

            case CMD_SUB:
            {
                int val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                stackPush(&stk, val_2 - val_1);
                printf("Sub: %d\n", val_2 - val_1);
                break;
            }

            case CMD_MUL:
            {
                int val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                stackPush(&stk, val_1 * val_2);
                printf("Mul: %d\n", val_1 * val_2);
                break;
            }

            case CMD_DIV:
            {
                int val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                stackPush(&stk, val_2 / val_1);
                printf("Div: %d\n", val_2 / val_1);
                break;
            }
            case CMD_OUT:
            {
                int val = 0;
                stackPop(&stk, &val);
                printf("Elem from stack: %d\n", val);
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
