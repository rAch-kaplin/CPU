#include <stdio.h>
#include <string.h>
#include "color.h"
#include "common.h"
#include "CommonProcAssem.h"
#include "assembler.h"

int main(int argc, char *argv[])
{
    struct Assem Asm = {};

    CheckArgsAsm(argc, argv, &Asm);

    const char* error_asm = Assembler(&Asm);
    if (error_asm != NULL)
    {
        printf("ERROR! from Assembler: %s \n", error_asm);
        return 1;
    }

    printf(COLOR_GREEN "End of main_assembler!\n" COLOR_RESET);
    return 0;
}

void CheckArgsAsm(int argc, char *argv[], Assem *Asm)
{
    Asm->file_name = "kvadrat.asm";

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-file") == 0 && i + 1 < argc)
        {
            Asm->file_name = argv[i + 1];
            i++;
        }
    }
}
