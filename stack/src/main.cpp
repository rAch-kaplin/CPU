#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include "stack.h"
#include "logger.h"
#include "color.h"
#include "debug.h"

int main()
{
    loggerInit(LOGL_DEBUG, "stack.log");

    struct stack stk = {NULL, 0, 0};
    stackElem elem_from_stack = 0;

    stackCtor(&stk, 5);

    for (int i = 0; i < 11; i++)
    {
        stackPush(&stk, (i + 1) * 10);
    }

    while(stk.size > 0)
    {
        stackPop(&stk, &elem_from_stack);
        DBG_PRINTF(COLOR_GREEN "elem_from_stack = " STACK_ELEM_FORMAT " \n\n" COLOR_RESET, elem_from_stack);
    }
    capacityOptimization(&stk);

    stackDtor(&stk);
    loggerDeinit();

    printf("End of main!\n");
    return 0;
}
