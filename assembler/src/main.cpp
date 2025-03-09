#include <stdio.h>
#include <string.h>
#include <assert.h>
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
        free(Asm.code);
        return ASSEM_ERROR;
    }

    WriteBinFile(&Asm);

    printf(COLOR_GREEN "End of main_assembler!\n" COLOR_RESET);
    return 0;
}

void WriteBinFile(Assem *Asm)
{
    FILE *bin_file = fopen("programms/bin_code.txt", "wb");
    assert(bin_file);

    fwrite(Asm->code, sizeof(int), (size_t)Asm->CODE_SIZE, bin_file);
    free(Asm->code);
    fclose(bin_file);
}

void CheckArgsAsm(int argc, char *argv[], Assem *Asm)
{
    Asm->file_name = "programms/kvadrat.asm";

    for (int i = 1; i < argc; i++)
    {
        if ((strcmp(argv[i], "--file") || strcmp(argv[i], "-f") == 0) && i + 1 < argc)
        {
            Asm->file_name = argv[i + 1];
            i++;
        }
    }
}
