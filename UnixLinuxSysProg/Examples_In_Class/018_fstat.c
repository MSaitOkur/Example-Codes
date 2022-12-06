/*--------------------------------------------------------------------------------------------------------------------------
    fstat fonksiyonu stat fonksiyonunun yol ifadesi değil dosya betimleyicisi alan biçimidir. Prototipi şöyledir:

    int fstat(int fd, struct stat *buf);

    Genel olarak işletim sisteminin dosya betimleyicisinden hareketle i-node bilgilerine erişmesi yol ifadesinden hareketle
    erişmesinden daha hızlı olmaktadır. Çünkü open fonksiyonunda zaten open dosyanın i-node bilgilerine erişip onu dosya nesnesinin
    içerisine almaktadır. Tabii önce dosyayı açıp sonra fstat uygulamak anlamsız bir yöntemdir. Ancak zaten biz bir dosyayı
    başka amaçla açmışsak onun bilgilerini fstat ile daha hızlı elde edebiliriz.
---------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define LS_BUFSIZE 4096

void exit_sys(const char *msg);
char *get_ls(struct stat *finfo, const char *name);

int main(void)
{
    int fd;
    struct stat finfo;

    if ((fd = open("sample.c", O_RDONLY)) == -1)
        exit_sys("open");

    /* burada dosyayla ilgili birtakım işlemler yapılıyor */

    if (fstat(fd, &finfo) == -1)
        exit_sys("fstat");

    printf("%s\n", get_ls(&finfo, "sample.c"));

    close(fd);

    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}

char *get_ls(struct stat *finfo, const char *name)
{
    static char buf[LS_BUFSIZE];
    static mode_t modes[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
    static mode_t ftypes[] = {S_IFBLK, S_IFCHR, S_IFIFO, S_IFREG, S_IFDIR, S_IFLNK, S_IFSOCK};
    int index;
    struct tm *ptime;

    index = 0;
    for (int i = 0; i < 7; ++i)
        if ((finfo->st_mode & S_IFMT) == ftypes[i])
        {
            buf[index++] = "bcp-dls"[i];
            break;
        }

    for (int i = 0; i < 9; ++i)
        buf[index++] = finfo->st_mode & modes[i] ? "rwx"[i % 3] : '-';

    ptime = localtime(&finfo->st_mtim.tv_sec);

    index += sprintf(buf + index, " %llu", (unsigned long long)finfo->st_nlink);
    index += sprintf(buf + index, " %llu", (unsigned long long)finfo->st_uid);
    index += sprintf(buf + index, " %llu", (unsigned long long)finfo->st_uid);
    index += sprintf(buf + index, " %llu", (unsigned long long)finfo->st_size);
    index += strftime(buf + index, LS_BUFSIZE, " %b %2e %H:%M", ptime);

    sprintf(buf + index, " %s", name);

    return buf;
}

