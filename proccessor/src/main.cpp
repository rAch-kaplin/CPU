#include <stdio.h>
#include <string.h>
#include "color.h"
#include "stack.h"
#include "logger.h"
#define DBG
#include "proccessor.h"
#include "common.h"

OutputMode CheckArgs(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    if (CheckArgs(argc, argv) == COLOR_MODE)
    {
        printf(COLOR_MAGENTA "COLOR_MODE ON\n" COLOR_RESET);
        GetLogger()->color_mode = COLOR_MODE;
    }

    loggerInit(LOGL_DEBUG, "logfile.log");
    DBG_PRINTF(COLOR_GREEN "Start CPU\n" COLOR_RESET);

    Assembler();
    Run();

    loggerDeinit();
    DBG_PRINTF(COLOR_GREEN "End of main!\n" COLOR_RESET);
    return 0;
}


OutputMode CheckArgs(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "COLOR_MODE") == 0)
    {
        return COLOR_MODE;
    }
    else
    {
        return DEFAULT_MODE;
    }

    return DEFAULT_MODE;
}
