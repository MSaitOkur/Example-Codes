#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    int fd1;
    if ((fd1 = open(argv[1], O_RDONLY)) == -1)
        exit_sys("open");

    int fd2;
    if ((fd2 = dup2(fd1, strtol(argv[2], NULL, 10))) == -1)
        exit_sys("dup");

    fprintf(stdout, "fd1 = %d, fd2 = %d\n", fd1, fd2);

    char buffer[64] = "";
    int result;
    if ((result = read(fd1, buffer, 10)) == -1)
        exit_sys("read");
    buffer[result] = '\0';

    puts(buffer);

    if ((result = read(fd2, buffer, 10)) == -1)
        exit_sys("read");
    buffer[result] = '\0';

    puts(buffer);

    close(fd2);
    close(fd1);
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}