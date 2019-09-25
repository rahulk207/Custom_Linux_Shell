#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    char *user_input = NULL, *cur_dir;
    size_t input_size = 0;
    size_t number_characters = 0;
    char *cur_history[100];
    char s[1000] = "";
    int command_id = 0;
    FILE *fptr;
    fptr = fopen("history.txt", "w+");
    if (fptr == NULL)
    {
        printf("History file not found");
    }

    while (1)
    {
        cur_dir = getcwd(NULL, 0);
        if (cur_dir == NULL)
        {
            perror("Could not load the current directory");
            exit(1);
        }
        else
        {
            char dir_output[100];
            strcpy(dir_output, cur_dir);
            strcat(dir_output, " : ");
            printf(dir_output);
        }

        number_characters = getline(&user_input, &input_size, stdin);
        char *input[1000];
        int i = 0;

        input[0] = strtok(user_input, " \n");
        strcat(s, input[0]);
        strcat(s, " ");
        while (input[i] != NULL)
        {
            input[++i] = strtok(NULL, " \n");
            if (input[i] != NULL)
            {
                strcat(s, input[i]);
                strcat(s, " ");
            }
        }

        cur_history[command_id] = s;
        cur_history[command_id + 1] = NULL;
        command_id++;

        if (strcmp(input[0], "cd") == 0)
        {
            char *new_dir = input[1];
            int c = chdir(new_dir);
            if (c == -1)
            {
                perror("Error ");
            }
        }
        else if (strcmp(input[0], "echo") == 0)
        {
            if (strcmp(input[1], "-e") == 0)
            {
                if (input[2] == NULL)
                {
                    printf("\n");
                }
                else
                {
                    printf(input[2]);
                    printf("\n");
                }
            }
            else
            {
                char output[number_characters];
                int i = 0;
                while (input[i] != NULL)
                {
                    strcat(output, input[i]);
                    strcat(output, " ");
                    i++;
                }
                system(output);
            }
        }
        else if (strcmp(input[0], "pwd") == 0)
        {
            if ((strcmp(input[1], "-L") == 0 || strcmp(input[1], "-P") == 0 || input[1] == NULL) && input[2] == NULL)
            {
                printf(cur_dir);
                printf("\n");
            }
            else
            {
                printf("Arguments not recognized\n");
            }
        }
        else if (strcmp(input[0], "exit") == 0)
        {
            if(input[1]==NULL){
                exit(0);
            }
            else if (input[1] != NULL && (strcmp(input[1],"0")==0 || strcmp(input[1],"1")==0 || strcmp(input[1],"2")==0 || strcmp(input[1],"3")==0
            || strcmp(input[1],"4")==0 || strcmp(input[1],"5")==0 || strcmp(input[1],"6")==0 || strcmp(input[1],"7")==0 || strcmp(input[1],"8")==0
            || strcmp(input[1],"9")==0))
            {
                if (input[2] == NULL)
                {
                    exit(input[1]);
                }
                else
                {
                    printf("Error : Too many arguments");
                }
            }
            else{
                exit(input[1]);
            }
        }
        else if (strcmp(input[0], "history") == 0)
        {
            if (input[1] == NULL)
            {
                rewind(fptr);
                char c;
                while ((c = getc(fptr)) != EOF)
                {
                    printf("%c", c);
                }
            }
            else if (strcmp(input[1], "-w") == 0)
            {
                if (cur_history[0] == NULL)
                {
                    printf("The history list is empty");
                }
                else
                {
                    int i = 0;
                    fputs(cur_history[i], fptr);
                }
            }
            else if (strcmp(input[1], "-c") == 0)
            {
                int i = 0;
                while (cur_history[i] != NULL)
                {
                    cur_history[i] = NULL;
                    i++;
                }
            }
        }
        else if (strcmp(input[0], "ls") == 0)
        {
            char *args[1000];
            args[0] = "/home/rahul/Desktop/ls";
            int i = 1;
            while (input[i] != NULL)
            {
                args[i] = input[i];
                i++;
            }
            args[i] = NULL;
            callChildProcess(args);
        }
        else if (strcmp(input[0], "cat") == 0)
        {
            char *args[1000];
            args[0] = "/home/rahul/Desktop/cat";
            int i = 1;
            while (input[i] != NULL)
            {
                args[i] = input[i];
                i++;
            }
            args[i] = NULL;
            callChildProcess(args);
        }
        else if (strcmp(input[0], "date") == 0)
        {
            char *args[1000];
            args[0] = "/home/rahul/Desktop/date";
            int i = 1;
            while (input[i] != NULL)
            {
                args[i] = input[i];
                i++;
            }
            args[i] = NULL;
            callChildProcess(args);
        }
        else if (strcmp(input[0], "rm") == 0)
        {
            char *args[1000];
            args[0] = "/home/rahul/Desktop/rm";
            int i = 1;
            while (input[i] != NULL)
            {
                args[i] = input[i];
                i++;
            }
            args[i] = NULL;
            callChildProcess(args);
        }
        else if (strcmp(input[0], "mkdir") == 0)
        {
            char *args[1000];
            args[0] = "/home/rahul/Desktop/mkdir";
            int i = 1;
            while (input[i] != NULL)
            {
                args[i] = input[i];
                i++;
            }
            args[i] = NULL;
            callChildProcess(args);
        }
        else
        {
            printf("Invalid command.\n");
        }
    }
    fclose(fptr);

    return 0;
}

int callChildProcess(char *args[])
{
    pid_t pid = fork();
    int status;
    if (pid == -1)
    {
        perror("Error while forking child process");
    }
    else if (pid == 0)
    {
        int p_error = execvp(args[0], args);
        if (p_error < 0)
        {
            perror("Error while executing the file");
        }
    }
    else
    {
        do
        {
            pid_t wpid = wait(&status);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}
