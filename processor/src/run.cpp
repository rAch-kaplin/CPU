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
#include "CommonProcAssem.h"

const char* Run(stack *stk, stack *retAddrStk, CPU *proc)
{
    CtorProc(stk, retAddrStk);

    int size_buffer = FillingCodeArray(proc);
    size_t count_command = sizeof(command_code) / sizeof(command_code[0]);

    for (int i = 0; i < size_buffer; i++)
    {
        printf(COLOR_MAGENTA "%d " COLOR_RESET, proc->code[i]);
    }
    printf("\n");

    bool next = true;
    while (next)
    {
        stackElem cmd = proc->code[proc->IP];

        switch (cmd)
        {
            case CMD_FUNC:
            {
                GetProcInstruction(cmd, proc);
                ProcessingFuncs(retAddrStk, proc, true, false);
                break;
            }

            case CMD_RET:
            {
                GetProcInstruction(cmd, proc);
                ProcessingFuncs(retAddrStk, proc, false, true);
                break;
            }

            case CMD_PUSH:
            case CMD_POP:
            {
                ProcessingStackCommands(proc, stk, cmd);
                break;
            }

            case CMD_ADD:
            {
                GetProcInstruction(cmd, proc);
                TwoElemStackOperation(stk, [](stackElem val1, stackElem val2) { return val2 + val1;} );
                break;
            }

            case CMD_SUB:
            {
                GetProcInstruction(cmd, proc);
                TwoElemStackOperation(stk, [](stackElem val1, stackElem val2) { return val2 - val1;} );
                break;
            }

            case CMD_MUL:
            {
                GetProcInstruction(cmd, proc);
                TwoElemStackOperation(stk, [](stackElem val1, stackElem val2) { return val2 * val1;} );
                break;
            }

            case CMD_DIV:
            {
                GetProcInstruction(cmd, proc);
                TwoElemStackOperation(stk, [](stackElem val1, stackElem val2) { return val2 / val1;} );
                break;
            }

            case CMD_SQRT:
            {
                GetProcInstruction(cmd, proc);
                SingleStackOperation(stk, sqrt);
                break;
            }

            case CMD_SIN:
            {
                GetProcInstruction(cmd, proc);
                SingleStackOperation(stk, sin);
                break;
            }

            case CMD_COS:
            {
                GetProcInstruction(cmd, proc);
                SingleStackOperation(stk, cos);
                break;
            }

            case CMD_IN:
            {
                GetProcInstruction(cmd, proc);
                ProcessingInputOut(stk, proc, true, false);
                break;
            }

            case CMD_OUT:
            {
                GetProcInstruction(cmd, proc);
                ProcessingInputOut(stk, proc, false, true);
                break;
            }

            case CMD_JMP:
            {
                DoJmp(proc, cmd);
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
                CONDITIONAL_JMP(>=);
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
                return "Unknow command:(";
                break;
            }
        }

        IpCounter(proc, cmd,  (int)count_command);

        if (cmd == CMD_HLT)
        {
            GetProcInstruction(cmd, proc);
            LOG(LOGL_DEBUG, "");
            break;
        }
    }

    free(proc->code);
    stackDtor(stk);
    stackDtor(retAddrStk);
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

int FillingCodeArray(CPU *proc)
{
    FILE* bin_file = fopen("programms/bin_code.txt", "rb");
    assert(bin_file != NULL);

    size_t file_size = GetBinFileSize(bin_file);
    size_t num_elements = file_size / sizeof(int);

    proc->code = (int*)calloc(num_elements + 1, sizeof(int));
    assert(proc->code);

    size_t elements_read = fread(proc->code, sizeof(int), num_elements, bin_file);
    if (elements_read != num_elements)
    {
        fprintf(stderr, "Error: read %zu elements, expected %zu\n", elements_read, num_elements);
    }

    // for (size_t i = 0; i < num_elements; i++)
    // {
    //     printf(COLOR_BLUE "%d " COLOR_RESET, proc->code[i]);
    // }
    // printf("\n");

    fclose(bin_file);
    return (int)num_elements;
}

size_t GetBinFileSize(FILE *bin_file)
{
    fseek(bin_file, 0, SEEK_END);
    long file_size = ftell(bin_file);
    rewind(bin_file);

    return (size_t)file_size;
}

void IpCounter(CPU *proc, stackElem cmd, int count_command)
{
    for (int i = 0; i < count_command; i++)
    {
        if (cmd == command_code[i].cmd_code)
        {
            switch (cmd)
            {
                case CMD_FUNC:
                case CMD_RET:
                case CMD_JMP:
                case CMD_JB:
                case CMD_JBE:
                case CMD_JA:
                case CMD_JAE:
                case CMD_JE:
                case CMD_JNE:
                    return;

                default:
                    proc->IP += 1 + command_code[i].quantity_args;
                    break;
            }
        }
    }
}

int ProcessingStackCommands(CPU *proc, stack *stk, int cmd)
{
    int TypeArgPush = proc->code[proc->IP + 1];
    bool IsPush = false, IsPushr = false, IsPopr = false;

    if (cmd == CMD_PUSH)
    {
        switch (TypeArgPush)
        {
            case 1:
                IsPush = true;
                break;
            case 2:
                IsPushr = true;
                break;
            default:
                break;
        }
    }

    if (IsPush)
    {
        stackElem value = proc->code[proc->IP + 2];
        GetProcInstruction(cmd, proc, value);
        LOG(LOGL_DEBUG, "");
        stackPush(stk, value);
    }

    else if (IsPushr)
    {
        stackElem value = proc->registers[proc->code[proc->IP + 2]];
        GetProcInstruction(cmd, proc, value);
        LOG(LOGL_DEBUG, "");
        stackPush(stk, value);
    }

    if (cmd == CMD_POP)
    {
        IsPopr = true;
    }
    if (IsPopr)
    {
        stackElem value = 0;
        GetProcInstruction(cmd, proc, value);
        LOG(LOGL_DEBUG, "");
        stackPop(stk, &value);
        proc->registers[proc->code[proc->IP + 2]] = value;
    }
    return 0;
}

void ProcessingInputOut(stack *stk, CPU *proc, bool Input, bool Out)
{
    LOG(LOGL_DEBUG, "");

    if (Input)
    {
                stackElem input_value = 0;
                printf("Enter a value: ");
                scanf("%d", &input_value);
                proc->registers[ax] = input_value;
    }

    else if (Out)
    {
                stackElem val = 0;
                stackPop(stk, &val);
                printf("Out: %d\n", val);
    }
}

void DoJmp(CPU *proc, int cmd)
{
    proc->IP = proc->code[proc->IP + 1];
    GetProcInstruction(cmd, proc, proc->IP);
    LOG(LOGL_DEBUG, "JMP to %d ", proc->code[proc->IP + 1]);
}

void ProcessingFuncs(stack *retAddrStk, CPU *proc, bool call, bool ret)
{
    LOG(LOGL_DEBUG, "");

    if (call)
    {
        stackPush(retAddrStk, proc->IP + 2);
        proc->IP = proc->code[proc->IP + 1];
    }

    else if (ret)
    {
        int retAddr = 0;
        stackPop(retAddrStk, &retAddr);
        proc->IP = retAddr;
    }
}

int CtorProc(stack *stk, stack *retAddrStk)
{
    stackCtor(stk, 8);
    stackCtor(retAddrStk, 8);
    return 0;
}
