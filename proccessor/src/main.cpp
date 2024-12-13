#include <stdio.h>
#include "proccessor.h"
#include "stack.h"
#include "logger.h"

int main()
{
    loggerInit(LOGL_DEBUG, "stack.log");
    printf("Start CPU\n");

    Compilator();
    Run();

    loggerDeinit();
    printf("End of main!\n");
    return 0;
}