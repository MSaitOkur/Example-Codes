#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(void)
{
    int fddir;
    if ((fddir = open("/usr/include", O_RDONLY)) == -1)
        exit_sys("open");

    int fd;
    if ((fd = openat(fddir, "/home/sait/Desktop/GitSoftwareStudy/C-Programs/test.txt", O_RDONLY)) == -1)
        exit_sys("open");
    // openat fonksiyonuna mutlak yol ifadesi gonderilirse bu durumda
    // 1. parametreye gonderilen dizin dosya betimleyicisinin hicbir
    // anlami kalmaz. openat aynen open gibi mutlak yol ifadesinde
    // test.txt dosyasini arayacak ve bulursa basari olacak.

    fprintf(stdout, "OK.\n");

    close(fd);

    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}
