#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *args[])
{

    int check;
    if (args[2] == NULL)
    {
        if (args[1] == NULL)
        {
            printf("Cannot create a blank directory");
            exit(1);
        }

        check = mkdir(args[1]);
        if (check == -1)
        {
            perror("Error ");
        }
    }
    else if (strcmp(args[1], "-v") == 0)
    {
        if (args[2] == NULL)
        {
            printf("Cannot create a blank directory");
            exit(1);
        }
        int i = 2;
        while (args[i] != NULL)
        {
            check = mkdir(args[i]);
            if (check == 0)
            {
                printf("Created directory ");
                printf(args[i]);
            }
            else
            {
                perror("Error ");
            }
            i++;
        }
    }
    else if (strcmp(args[1], "-p") == 0)
    {
        args[0] = "/bin/mkdir";
        execvp(args[0], args);
    }
    else
    {
        int i = 1;
        while (args[i] != NULL)
        {
            check = mkdir(args[i]);
            if(check==-1)
            {
                perror("Error ");
            }
            i++;
        }
    }
}