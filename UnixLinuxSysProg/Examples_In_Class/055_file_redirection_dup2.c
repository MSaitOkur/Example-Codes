#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    int fd;
    if ((fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH)) == -1)
        exit_sys("open");

    // 1 numarali betimleyici fd'nin gosterdigi dosyaya baglanmadan once atomik olarak 
    // kapatilir. Sonra hemen 1'in fd ile duplicate edilmesi saglanir.
    if (dup2(fd, 1) == -1)
        exit_sys("dup2");
    close(fd);

    // 1 numarali betimleyici su anda fd'nin kapatilmadan onceki halini gosteriyor.
    // Yani burada 1 numarali betimleyici(stdout) fd ile acilan dosyaya yaziyor.
    for (int i = 0; i < 10; ++i)
        fprintf(stdout, "Number: %d\n", i); // yazma islemi test.txt dosyasina yapilacak
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}


//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    int fd;
    if ((fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH)) == -1)
        exit_sys("open");

    // 1 numarali betimleyici fd'nin gosterdigi dosyaya baglanmadan once atomik olarak
    // kapatilir. Sonra hemen 1'in fd ile duplicate edilmesi saglanir.
    if (dup2(fd, 1) == -1)
        exit_sys("dup2");
    close(fd);

    // 1 numarali betimleyici su anda fd'nin kapatilmadan onceki halini gosteriyor.
    // Yani burada 1 numarali betimleyici(stdout) fd ile acilan dosyaya yaziyor.
    for (int i = 0; i < 10; ++i)
        fprintf(stdout, "Number: %d\n", i);

    // bu cagri ihtiyactir. Nedeni ileride aciklanacaktir.
    fflush(stdout);

    // burada hala 2 standart outputa bagli. Bu nedenle eger stdout dosyasini terminal 
    // aygit surucusune baglamak icin dup2 cagrilmalidir.
    if (dup2(2, 1) == -1)
        exit_sys("dup2");

    // Burada printf ekran terminal aygit surucusune yazma yapilmistir.
    for (int i = 0; i < 10; ++i)
        printf("Number: %d\n", i);
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    int fd;
    if ((fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH)) == -1)
        exit_sys("open");

    // Buradaki dup'in sebebi eger 1 ve 2 numarali betimleyiciler ileride yonlendirmelerden
    // dolayi kaybedilirse yedekte bulunsun amacidir.
    int fd_stdout;
    if ((fd_stdout = dup(1)) == -1)
        exit_sys("dup");

    if (dup2(fd, 1) == -1)
        exit_sys("dup2");
    if (dup2(fd, 2) == -1)
        exit_sys("dup2");
    close(fd);

    // Burada ekran terminal aygit surucusu 1 ve 2 den kaybedilmistir.
    // Ancak daha oncesinde tedbiren yapilan dup sonucunda elde edilen ve ekran
    // terminal aygit surucusunu gosteren fd_stdout ile ekrana yazma yapilabilir.
    FILE *f_fd_stdout = fdopen(fd_stdout, "wb"); // ekran terminal aygit surucusu

    for (int i = 0; i < 10; ++i)
    {
        fprintf(stdout, "Number: %d\n", i); // test.txt'ye yazar.
        fflush(stdout);
        fprintf(stderr, "Number: %d\n", i); // test.txt'ye yazar.
        fflush(stderr);
        fprintf(f_fd_stdout, "Number: %d\n", i); // test.txt'ye yazar.
        fflush(f_fd_stdout);
    }
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    int fd;
    if ((fd = open("test.txt", O_RDONLY)) == -1)
        exit_sys("open");

    // klavye terminal surucusu yani 0 numarali surucu fd ile acilan dosyaya yonlendirilmistir.
    // Artik stdin den yapilacak okumalar, test.txt den okunmaktadir.
    if (dup2(fd, 0) == -1)
        exit_sys("dup2");
    close(fd);

    int val;
    while (scanf("%d", &val) == 1)
        fprintf(stdout, "%d\n", val);
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}
