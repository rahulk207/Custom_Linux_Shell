#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

int main(int argc, char *args[])
{
    if (args[1] == NULL)
    {
        time_t now;
        time(&now);
        printf("IST ");
        printf(ctime(&now));
    }
    else if (strcmp(args[1], "-u") == 0)
    {
        time_t orig;
        time(&orig);
        printf("UCT "); 
        printf(asctime(gmtime(&orig)));
    }
    else if (strcmp(args[1], "-r") == 0)
    {
        struct stat filestat;
        int e = stat(args[2],&filestat);
        if(e==-1){
            perror("No such file");
            exit(1);
        }
        printf("IST "); 
        printf(ctime(&filestat.st_mtime));
    }
    else
    {
        printf("Invalid command");
        printf("\n");
    }
}