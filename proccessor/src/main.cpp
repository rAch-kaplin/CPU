#include <stdio.h>
#include <string.h>
#include "color.h"
#include "stack.h"
#include "logger.h"
#define DBG
#include "proccessor.h"
#include "common.h"

OutputMode CheckArgs(int argc, char *argv[]);

//TODO:  7) make another logging depth
//TODO:  11) maybe to do advanced push


int main(int argc, char *argv[])
{
    if (CheckArgs(argc, argv) == COLOR_MODE)
    {
        printf(COLOR_MAGENTA "COLOR_MODE ON\n" COLOR_RESET);
        GetLogger()->color_mode = COLOR_MODE;
    }

    loggerInit(LOGL_DEBUG, "logfile.log");
    DBG_PRINTF(COLOR_GREEN "Start CPU\n" COLOR_RESET);

    struct Assem Asm = {"0",{0}, {{"next",  7},
                            {"ded" , 32} }};
    CodeError error = Assembler(&Asm);
    if (error != ITS_OK)
    {
        printf("ERROR! from Assembler\n");
        return 1;
    }
    
    Run(&Asm);

    loggerDeinit();
    DBG_PRINTF(COLOR_GREEN "End of main!\n" COLOR_RESET);
    return 0;
}


OutputMode CheckArgs(int argc, char *argv[])
{
    OutputMode mode = DEFAULT_MODE;
    if (argc > 1 && strcmp(argv[1], "COLOR_MODE") == 0)
    {
        mode = COLOR_MODE;
        return COLOR_MODE;
    }
#if 0
    OutputMode mode = GetLogger()->color_mode;
    switch (mode)
    {
        case DEFAULT_MODE:
        {
            Assem.file_name = argv[1];
            break;
        }

        case COLOR_MODE:
        {
            Asm->file_name = argv[2];
            break;
        }

        default:
            break;
    }
#endif
    return mode;
}
