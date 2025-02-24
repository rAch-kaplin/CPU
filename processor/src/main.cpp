#include <stdio.h>
#include <string.h>
#include "color.h"
#include "stack.h"
#include "logger.h"
#include "proccessor.h"
#include "common.h"
#include "CommonProcAssem.h"

ServiceLines* GetServiceLines()
{
    static ServiceLines service = {"",""};
    return &service;
}

int main(int argc, char *argv[])
{
    CheckArgsProc(argc, argv);

    loggerInit(LOGL_DEBUG, "logfile.log");

    const char* error_run = Run();
    if (error_run != NULL)
    {
        printf("ERROR! from Run ^\n");
        return 1;
    }

    loggerDeinit();
    printf(COLOR_GREEN "End of main!\n" COLOR_RESET);
    return 0;
}

void CheckArgsProc(int argc, char *argv[])
{
    GetLogger()->color_mode = DEFAULT_MODE;

    const char* color_mode = NULL;

    for (int i = 1; i < argc; i++)
    {

        if (strcmp(argv[i], "-mode") == 0 && i + 1 < argc)
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
