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

#define CONDITIONAL_JMP(condition)                        \
    do                                                    \
    {                                                     \
        stackElem val_1 = 0, val_2 = 0;                   \
        GetProcInstruction(cmd, &proc);                   \
        LOG(LOGL_DEBUG, "");                              \
                                                          \
        stackPop(&stk, &val_1);                           \
        stackPop(&stk, &val_2);                           \
                                                          \
        if ((val_1) condition (val_2))                    \
        {                                                 \
            proc.IP += 1;                                 \
        }                                                 \
        else                                              \
        {                                                 \
            proc.IP += 2;                                 \
        }                                                 \
    } while(0)

const char* Run()
{
    struct stack stk = {NULL, 0, 0};
    stackCtor(&stk, 8);

    struct CPU proc = {};

    FillingCodeArray(&proc);
    bool next = true;

    while (next)
    {
        stackElem cmd = proc.code[proc.IP];

        switch (cmd)
        {
            case CMD_PUSH:
            {
                stackElem value = proc.code[proc.IP + 1];

                GetProcInstruction(cmd, &proc, value);
                LOG(LOGL_DEBUG, "");
                stackPush(&stk, value);
                proc.IP += 2;
                break;
            }

            case CMD_PUSHR:
            {
                stackElem value = proc.registers[proc.code[proc.IP + 1]];

                GetProcInstruction(cmd, &proc, value);
                LOG(LOGL_DEBUG, "");
                stackPush(&stk, value);
                proc.IP += 2;
                break;
            }

            case CMD_POPR:
            {
                stackElem value = 0;
                GetProcInstruction(cmd, &proc, value);
                LOG(LOGL_DEBUG, "");
                stackPop(&stk, &value);
                proc.registers[proc.code[proc.IP + 1]] = value;
                proc.IP += 2;
                break;
            }

            case CMD_ADD:
            {
                GetProcInstruction(cmd, &proc);
                LOG(LOGL_DEBUG, "");
                stackElem val_1 = 0, val_2 = 0;
                stackPop(&stk, &val_1);
                stackPop(&stk, &val_2);

                stackPush(&stk, val_1 + val_2);
                proc.IP += 1;

                break;
            }

            case CMD_SUB:
            {
                GetProcInstruction(cmd, &proc);
                TwoElemStackOperation(&stk, [](stackElem val1, stackElem val2) { return val2 - val1;} );
                proc.IP += 1;

                break;
            }

            case CMD_MUL:
            {
                GetProcInstruction(cmd, &proc);
                TwoElemStackOperation(&stk, [](stackElem val1, stackElem val2) { return val2 * val1;} );
                proc.IP += 1;

                break;
            }

            case CMD_DIV:
            {
                GetProcInstruction(cmd, &proc);
                TwoElemStackOperation(&stk, [](stackElem val1, stackElem val2) { return val2 / val1;} );
                proc.IP += 1;

                break;
            }

            case CMD_SQRT:
            {
                GetProcInstruction(cmd, &proc);
                SingleStackOperation(&stk, sqrt);
                proc.IP += 1;

                break;
            }

            case CMD_SIN:
            {
                GetProcInstruction(cmd, &proc);
                SingleStackOperation(&stk, sin);
                proc.IP += 1;

                break;
            }

            case CMD_COS:
            {
                GetProcInstruction(cmd, &proc);
                SingleStackOperation(&stk, cos);
                proc.IP += 1;

                break;
            }

            case CMD_OUT:
            {
                GetProcInstruction(cmd, &proc);
                LOG(LOGL_DEBUG, "");
                stackElem val = 0;
                stackPop(&stk, &val);
                proc.IP += 1;

                break;
            }

            case CMD_JMP:
            {
                proc.IP = proc.code[proc.IP + 1];
                GetProcInstruction(cmd, &proc, proc.IP);
                LOG(LOGL_DEBUG, "JMP to %d ", proc.code[proc.IP + 1]);

                break;
            }

            case CMD_JB:
            {
                CONDITIONAL_JMP(<);
                break;
            }

            case CMD_JBE:
            {
                CONDITIONAL_JMP(<=);
                break;
            }

            case CMD_JA:
            {
                CONDITIONAL_JMP(>);
                break;
            }

            case CMD_JAE:
            {
                CONDITIONAL_JMP(>+);
                break;
            }

            case CMD_JE:
            {
                CONDITIONAL_JMP(==);
                break;
            }

            case CMD_JNE:
            {
                CONDITIONAL_JMP(!=);
                break;
            }

            case CMD_HLT:
            {
                break;
            }

            default:
            {
                //const char * cmd_code = CommandToString(int cmd);
                return "Unknow command:(";
                break;
            }
        }

        if (cmd == CMD_HLT)
        {
            GetProcInstruction(cmd, &proc);
            LOG(LOGL_DEBUG, "");
            break;
        }
    }
    free(proc.code);
    stackDtor(&stk);
    return NULL;
}

void SingleStackOperation(stack *stk, double (*operation)(double))
{
    stackElem value = 0;
    LOG(LOGL_DEBUG, "");
    stackPop(stk, &value);
    stackPush(stk, (stackElem)operation(value));
}

void TwoElemStackOperation(stack *stk, stackElem (*operation)(stackElem val1, stackElem val2))
{
    LOG(LOGL_DEBUG, "");
    stackElem val_1 = 0, val_2 = 0;
    stackPop(stk, &val_1);
    stackPop(stk, &val_2);
    stackPush(stk, operation(val_1, val_2));
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
        //printf("ZZZZ ---- %d ", proc->code[i]);
    }
    //printf("\n");
    fclose(file_code);
}


