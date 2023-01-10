#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    close(STDOUT_FILENO);
    int fd;
    if ((fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH)) == -1)
        exit_sys("open");

    // burada fprintf standart outputa yazmak istediginde stdout fd'yi gosterdigi icin 
    // fd olan dosyaya yazdi.
    for(int i = 0; i < 10; ++i)
        fprintf(stdout, "Number : %d\n", i);
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}