#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    if (mkdir(argv[1], S_IRWXU | S_IRWXG | S_IRWXO) == -1)
        exit_sys("mkdir");

    printf("success...\n");

    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}