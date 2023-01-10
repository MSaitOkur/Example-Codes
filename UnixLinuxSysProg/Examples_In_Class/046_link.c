#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exit_sys(const char *err_msg);

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Wrong number of arguments!....\n");
        exit(EXIT_FAILURE);
    }

    if (link(argv[1], argv[2]) == -1)
        exit_sys("link");
}

void exit_sys(const char *err_msg)
{
    perror(err_msg);
    exit(EXIT_FAILURE);
}
