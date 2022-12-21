#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(void)
{

    char buffer[4096];
    if (getcwd(buffer, 4096) == NULL)
        exit_sys("getcwd");

    int fddir;
    if ((fddir = open(buffer, O_RDONLY)) == -1)
        exit_sys("open");

    int fd;
    if ((fd = openat(fddir, "test.txt", O_RDONLY)) == -1)
        exit_sys("open");
    // openat fonksiyonu test.txt dosyasini fddir dizin dosya
    // betimleyicisinde arayacakve bulursa basarili bulamazsa
    // basarisiz olacak

    fprintf(stdout, "OK.\n");

    close(fd);

    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}
