#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "proccessor.h"
#include "assembler.h"
#include "stack.h"

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
        printf("%d\n", cmd);

        if (cmd == Push)
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
        }

        else if (cmd == Add)
        {
            int val_1 = 0, val_2 = 0;
            stackPop(&stk, &val_1);
            stackPop(&stk, &val_2);

            stackPush(&stk, val_1 + val_2);
            printf("Add: %d\n", val_1 + val_2);
        }

        else if (cmd == Sub)
        {
            int val_1 = 0, val_2 = 0;
            stackPop(&stk, &val_1);
            stackPop(&stk, &val_2);

            stackPush(&stk, val_2 - val_1);
            printf("Sub: %d\n", val_2 - val_1);
        }

        else if (cmd == Mul)
        {
            int val_1 = 0, val_2 = 0;
            stackPop(&stk, &val_1);
            stackPop(&stk, &val_2);

            stackPush(&stk, val_1 * val_2);
            printf("Mul: %d\n", val_1 * val_2);
        }

        else if (cmd == Div)
        {
            int val_1 = 0, val_2 = 0;
            stackPop(&stk, &val_1);
            stackPop(&stk, &val_2);

            stackPush(&stk, val_2 / val_1);
            printf("Div: %d\n", val_2 / val_1);
        }

        else if (cmd == Out)
        {
            int val = 0;
            stackPop(&stk, &val);
            printf("Elem from stack: %d\n", val);
        }

        else if (cmd == Hlt)
        {
            fclose(file_code);
            break;
        }

        else
            printf("Unknow command:(\n");
    }
    stackDtor(&stk);
}
