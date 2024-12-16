#include <stdio.h>
#include "color.h"
#include "assembler.h"
#include "stack.h"
#include "logger.h"


int main()
{
    loggerInit(LOGL_DEBUG, "logFile.log");
    DBG_PRINTF(COLOR_GREEN "Start CPU\n" COLOR_RESET);

    Assembler();
    Run();

    loggerDeinit();
    DBG_PRINTF(COLOR_GREEN "End of main!\n" COLOR_RESET);
    return 0;
}
