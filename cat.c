#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>

int main(int argc, char *args[])
{
    if (args[2] == NULL)
    {
        if (args[1] == NULL)
        {
            printf("Name of file is not defined");
        }
        FILE *fptr;
        fptr = fopen(args[1], "r");
        if (fptr == NULL)
        {
            printf("File doesn't exist");
            exit(1);
        }
        char c;
        while ((c = getc(fptr)) != EOF)
        {
            printf("%c", c);
        }
        fclose(fptr);
    }

    else if (strcmp(args[2], ">") == 0)
    {
        if (args[3] == NULL)
        {
            printf("Name of file is not defined");
        }
        FILE *fptr1, *fptr2;
        fptr1 = fopen(args[1], "r");
        if (fptr1 == NULL)
        {
            printf("File 1 doesn't exist");
            exit(1);
        }
        fptr2 = fopen(args[3], "w");
        char c;
        while ((c = getc(fptr1)) != EOF)
        {
            putc(c, fptr2);
        }
    }
    else if (strcmp(args[1], "-E") == 0)
    {
        args[0] = "/bin/cat";
        execvp(args[0], args);
    }
    else if (strcmp(args[1], "-n") == 0)
    {
        args[0] = "/bin/cat";
        execvp(args[0], args);
    }
    else
    {
        int i = 1;
        FILE *fptr;
        while (args[i] != NULL)
        {
            fptr = fopen(args[i], "r");
            if (fptr == NULL)
            {
                printf("File doesn't exist");
                exit(1);
            }
            char c;
            while ((c = getc(fptr)) != EOF)
            {
                printf("%c", c);
            }
            i++;
            fclose(fptr);
        }
    }
}