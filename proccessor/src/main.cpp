#include <stdio.h>
#include "color.h"
#include "proccessor.h"
#include "stack.h"
#include "logger.h"

//показать логгер, мейкфайл, хеш, процессор

int main()
{
    loggerInit(LOGL_DEBUG, "stack.log");
    DBG_PRINTF(COLOR_GREEN "Start CPU\n" COLOR_RESET);

    Compilator();
    Run();

    loggerDeinit();
    DBG_PRINTF(COLOR_GREEN "End of main!\n" COLOR_RESET);
    return 0;
}
