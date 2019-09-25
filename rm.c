#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *args[])
{
    int status;
    if (args[2] == NULL)
    {
        if (args[1] == NULL)
        {
            printf("Cannot remove a file with no name");
            exit(1);
        }
        status = remove(args[1]);
        if (status == 0)
        {
            printf("File deleted successfully\n");
        }
        else
        {
            perror("Error ");
            exit(1);
        }
    }
    else if (strcmp(args[1], "-f") == 0)
    {
        if (args[2] == NULL)
        {
            printf("Cannot remove a file with no name");
            exit(1);
        }
        int i = 2;
        while (args[i] != NULL)
        {
            remove(args[i]);
            i++;
        }
    }
    else if (strcmp(args[1], "-i") == 0)
    {
        if (args[2] == NULL)
        {
            printf("Cannot remove a file with no name");
            exit(1);
        }
        int i = 2;
        char *choice;
        while (args[i] != NULL)
        {
            printf("Sure you want to delete the file(Y/N) ");
            printf(args[i]);
            printf("\n");
            scanf("%s", choice);
            if (strcmp(choice, "y") == 0)
            {
                status = remove(args[i]);
                if (status == 0)
                {
                    printf("File deleted successfully\n");
                }
                else
                {
                    perror("Error ");
                }
            }
            i++;
        }
    }
    else if (strcmp(args[1], "-r") == 0)
    {
        if (args[2] == NULL)
        {
            printf("No such directory");
            exit(1);
        }
        DIR *rm_folder;
        rm_folder = opendir(args[2]);
        if (rm_folder == NULL)
        {
            perror("Unable to read directory");
            exit(1);
        }
        struct dirent *temp;
        while (1)
        {

            temp = readdir(rm_folder);
            if (temp == NULL)
            {
                break;
            }
            char *name = temp->d_name;
            chdir(args[2]);
            status = remove(name);
            chdir("..");
        }
    }
    else
    {
        int i = 1;
        while (args[i] != NULL)
        {
            status = remove(args[i]);
            if (status == 0)
            {
                printf("File deleted successfully\n");
            }
            else
            {
                perror("Error ");
            }
        i++;
        }
    }
}