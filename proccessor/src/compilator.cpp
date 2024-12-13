#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "proccessor.h"

void Compilator()
{
    FILE *file_asm = fopen("Programm_asm.txt", "r");
    if (file_asm == nullptr)
    {
        printf("file_asm == nullptr");
        assert(0);
    }

    FILE *file_code = fopen("Programm_code.txt", "w");
        if (file_code == nullptr)
    {
        printf("file_code == nullptr");
        assert(0);
    }

    while(true)
    {
        char cmd[20] = "";
        if (fscanf(file_asm, "%s", cmd) != 1)
        {
            printf("the string incorrectly\n");
            break;
        }
        printf("cmd = <%s>\n", cmd);

        if (strcmp(cmd, "Push") == 0)
        {
            fprintf(file_code, "1 ");
            int value = 0;
            fscanf(file_asm, "%d", &value);
            fprintf(file_code, "%d\n", value);
        }

        else if (strcmp(cmd, "Add") == 0)
        {
            fprintf(file_code, "2\n");
        }

        else if (strcmp(cmd, "Sub") == 0)
        {
            fprintf(file_code, "3\n");
        }

        else if (strcmp(cmd, "Out") == 0)
        {
            fprintf(file_code, "4\n");
        }

        else if (strcmp(cmd, "Div") == 0)
        {
            fprintf(file_code, "5\n");
        }

        else if (strcmp(cmd, "Mul") == 0)
        {
            fprintf(file_code, "6\n");
        }

        else if (strcmp(cmd, "Hlt") == 0)
        {
            fprintf(file_code, "-1\n");
            break;
        }
    }
    fclose(file_asm);
    fclose(file_code);
}
