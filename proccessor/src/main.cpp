#include <stdio.h>
#include <string.h>
#include "color.h"
#include "stack.h"
#include "logger.h"
#include "proccessor.h"
#include "common.h"
#include "CommonProcAssem.h"
#include "assembler.h"


void CheckArgs(int argc, char *argv[], Assem *Asm);

ServiceLines* GetServiceLines()
{
    static ServiceLines service = {"",""};
    return &service;
}

int main(int argc, char *argv[])
{
    struct Assem Asm = {};

    CheckArgs(argc, argv, &Asm);

    loggerInit(LOGL_DEBUG, "logfile.log");
    DBG_PRINTF(COLOR_GREEN "Start CPU\n" COLOR_RESET);


    const char* error_asm = Assembler(&Asm);
    if (error_asm != NULL)
    {
        printf("ERROR! from Assembler: %s \n", error_asm);
        return 1;
    }

    const char* error_run = Run();
    if (error_run != NULL)
    {
        printf("ERROR! from Run ^\n");
        return 1;
    }

    loggerDeinit();
    DBG_PRINTF(COLOR_GREEN "End of main!\n" COLOR_RESET);
    return 0;
}

void CheckArgs(int argc, char *argv[], Assem *Asm)
{
    GetLogger()->color_mode = DEFAULT_MODE;
    Asm->file_name = "kvadrat.asm";

    const char* color_mode = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-file") == 0 && i + 1 < argc)
        {
            Asm->file_name = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-mode") == 0 && i + 1 < argc)
        {
            color_mode = argv[i + 1];
            if (strcmp(color_mode, "COLOR_MODE") == 0)
            {
                GetLogger()->color_mode = COLOR_MODE;
            }
            i++;
        }
    }

}
