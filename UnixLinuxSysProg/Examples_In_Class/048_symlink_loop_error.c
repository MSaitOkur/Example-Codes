#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void exit_sys(const char *err_msg);

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Wrong number of arguments!....\n");
        exit(EXIT_FAILURE);
    }

    if (symlink(argv[1], argv[2]) == -1)
        exit_sys("symlink");

    if (symlink(argv[2], argv[1]) == -1)
        exit_sys("symlink");

    if (open(argv[1], O_RDONLY) == -1)
        exit_sys("open");

    fprintf(stdout, "Ok.\n");
}

void exit_sys(const char *err_msg)
{
    perror(err_msg);
    exit(EXIT_FAILURE);
}
