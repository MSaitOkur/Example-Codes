#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(void)
{
    int fd;

    umask(0);

    if ((fd = open("x.dat", O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
        exit_sys("open");

    printf("success...\n");

    close(fd);

    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}