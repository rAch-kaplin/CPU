#ifndef COMMON_H
#define COMMON_H

enum CodeError
{
    FILE_NOT_OPEN = 10,
    ITS_OK = 0
};

const int SIZE_BUFFER2 = 8192;

typedef struct ServiceLines
{
    char stack_state[SIZE_BUFFER2];
    char proc_instruction[SIZE_BUFFER2];
} ServiceLines;

ServiceLines* GetServiceLines();

#endif // COMMON_H

