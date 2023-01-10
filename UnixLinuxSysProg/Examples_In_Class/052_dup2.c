#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    int fd1;
    if ((fd1 = open(argv[1], O_RDONLY)) == -1)
        exit_sys("open");

    int fd2;
    if ((fd2 = dup(fd1)) == -1)
        exit_sys("dup");

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