#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "color.h"
#include "proccessor.h"
#include "stack.h"
#include "debug_proc.h"
#include "logger.h"

const int SIZE_CODE_BUFFER = 20;
const int SIZE_REGISTERS = 4;

typedef struct CPU
{
    stackElem *code;
    int IP;
    stackElem registers[SIZE_REGISTERS] = {};
} CPU;

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
        stackElem cmd = proc.code[proc.IP];

        DBG_PRINTF(COLOR_MAGENTA "%s\n" COLOR_RESET, CommandToString(cmd));

        switch (cmd)
        {
            case CMD_PUSH:
            {
                stackElem value = proc.code[proc.IP + 1];

                DBG_PRINTF(COLOR_CYAN "Enter value: " COLOR_RESET);
                DBG_PRINTF(COLOR_MAGENTA "%d\n" COLOR_RESET, value);

                GetProcInstruction(cmd, value);
                LOG(LOGL_DEBUG, "");
                stackPush(&stk, value);
                proc.IP += 2;
                break;
            }

            case CMD_PUSHR:
            {
                stackElem value = proc.registers[RDX];

                GetProcInstruction(cmd, value);
                LOG(LOGL_DEBUG, "");
                stackPush(&stk, value);

                break;
            }

            case CMD_POPR:
            {
                stackElem value = 0;
                stackPop(&stk, &value);
                proc.registers[RDX] = value;
                GetProcInstruction(cmd, value);
                LOG(LOGL_DEBUG, "");

                break;
            }

            case CMD_ADD:
            {
                stackElem val_1 = 0, val_2 = 0;
                GetProcInstruction(cmd);
                LOG(LOGL_DEBUG, "");

                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                stackPush(&stk, val_1 + val_2);

                proc.IP += 1;
                DBG_PRINTF(COLOR_MAGENTA "Add: %d\n" COLOR_RESET, val_1 + val_2);

                break;
            }

            case CMD_SUB:
            {
                GetProcInstruction(cmd);
                LOG(LOGL_DEBUG, "");
                stackElem val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                stackPush(&stk, val_2 - val_1);
                DBG_PRINTF(COLOR_MAGENTA "Sub: %d\n" COLOR_RESET, val_2 - val_1);
                proc.IP += 1;

                break;
            }

            case CMD_MUL:
            {
                GetProcInstruction(cmd);
                LOG(LOGL_DEBUG, "");
                stackElem val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                stackPush(&stk, val_1 * val_2);
                DBG_PRINTF(COLOR_MAGENTA "Mul: %d\n" COLOR_RESET, val_1 * val_2);
                proc.IP += 1;

                break;
            }

            case CMD_DIV:
            {
                GetProcInstruction(cmd);
                LOG(LOGL_DEBUG, "");
                stackElem val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                stackPush(&stk, val_2 / val_1);
                DBG_PRINTF(COLOR_MAGENTA "Div: %d\n" COLOR_RESET, val_2 / val_1);
                proc.IP += 1;

                break;
            }

            case CMD_SQRT:
            {
                GetProcInstruction(cmd);
                LOG(LOGL_DEBUG, "");
                stackElem value = 0;
                stackPop(&stk, &value);

                stackPush(&stk, stackElem(sqrt(value)));
                proc.IP += 1;

                break;
            }

            case CMD_SIN:
            {
                stackElem value = 0;
                GetProcInstruction(cmd);
                LOG(LOGL_DEBUG, "");

                stackPop(&stk, &value);
                stackPush(&stk, (stackElem)sin(value));
                proc.IP += 1;

                break;
            }

            case CMD_COS:
            {
                stackElem value = 0;
                GetProcInstruction(cmd);
                LOG(LOGL_DEBUG, "");

                stackPop(&stk, &value);
                stackPush(&stk, (stackElem)cos(value));
                proc.IP += 1;

                break;
            }

            case CMD_OUT:
            {
                GetProcInstruction(cmd);
                LOG(LOGL_DEBUG, "");
                stackElem val = 0;
                stackPop(&stk, &val);
                DBG_PRINTF(COLOR_MAGENTA "Elem from stack: %d\n" COLOR_RESET, val);

                proc.IP += 1;

                break;
            }

            case CMD_JMP:
            {
                proc.IP = proc.code[proc.IP + 1];
                GetProcInstruction(cmd, proc.IP);
                LOG(LOGL_DEBUG, "JMP to ");

                break;
            }

            case CMD_JB:
            {
                stackElem val_1 = 0, val_2 = 0;
                GetProcInstruction(cmd);
                LOG(LOGL_DEBUG, "");

                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                if (val_1 < val_2)
                {
                    proc.IP = proc.code[proc.IP + 1];
                }
                else
                {
                    proc.IP = proc.code[proc.IP + 2];
                }
                break;
            }

            case CMD_JBE:
            {
                stackElem val_1 = 0, val_2 = 0;
                GetProcInstruction(cmd);
                LOG(LOGL_DEBUG, "");

                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                if (val_1 <= val_2)
                {
                    proc.IP = proc.code[proc.IP + 1];
                }
                else
                {
                    proc.IP = proc.code[proc.IP + 2];
                }
                break;
            }

            case CMD_JA:
            {
                stackElem val_1 = 0, val_2 = 0;
                GetProcInstruction(cmd);
                LOG(LOGL_DEBUG, "");

                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                if (val_1 > val_2)
                {
                    proc.IP = proc.code[proc.IP + 1];
                }
                else
                {
                    proc.IP = proc.code[proc.IP + 2];
                }
                break;
            }

            case CMD_JAE:
            {
                stackElem val_1 = 0, val_2 = 0;
                GetProcInstruction(cmd);
                LOG(LOGL_DEBUG, "");

                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                if (val_1 >= val_2)
                {
                    proc.IP = proc.code[proc.IP + 1];
                }
                else
                {
                    proc.IP = proc.code[proc.IP + 2];
                }
                break;
            }

            case CMD_JE:
            {
                stackElem val_1 = 0, val_2 = 0;
                GetProcInstruction(cmd);
                LOG(LOGL_DEBUG, "");

                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                if (val_1 == val_2)
                {
                    proc.IP = proc.code[proc.IP + 1];
                }
                else
                {
                    proc.IP = proc.code[proc.IP + 2];
                }
                break;
            }

            case CMD_JNE:
            {
                stackElem val_1 = 0, val_2 = 0;
                GetProcInstruction(cmd);
                LOG(LOGL_DEBUG, "");

                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                if (val_1 != val_2)
                {
                    proc.IP = proc.code[proc.IP + 1];
                }
                else
                {
                    proc.IP = proc.code[proc.IP + 2];
                }
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
            break;
        }
    }
    free(proc.code);
    stackDtor(&stk);
}

void FillingCodeArray(CPU *proc)
{
    FILE *file_code = fopen("code.txt", "r");
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
