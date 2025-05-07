#include "lexer.h"
#include<stdio.h>
int error_check(char* filename)
{
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    char ch, prev = '\0';
    while ((ch = getc(fptr)) != EOF)
    {
        prev = ch;
        while (ch != '\n' && ch != EOF)
        {
            printf("%c++>\n", ch);
            prev = ch;
            ch = getc(fptr);
        }

        if (prev != ';')
        {
            printf("Line does not end with semicolon: ends with '%c'\n", prev);
            fclose(fptr);
            return 0;
        }
    }

    fclose(fptr);
    return 1;
}
