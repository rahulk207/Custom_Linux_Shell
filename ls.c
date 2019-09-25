#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>

int main(int argc, char *args[])
{
    if (args[1] == NULL)
    {
        DIR *cur_folder;
        cur_folder = opendir(".");
        if (cur_folder == NULL)
        {
            perror("Unable to read directory");
            exit(1);
        }

        struct dirent *temp;
        int c = 0;
        while (1)
        {
            temp = readdir(cur_folder);
            if (temp == NULL)
            {
                break;
            }
            printf(temp->d_name);
            printf("      ");
        }
        printf("\n");
    }
    else
    {
        args[0] = "/bin/ls";
        execvp(args[0], args);
    }
}