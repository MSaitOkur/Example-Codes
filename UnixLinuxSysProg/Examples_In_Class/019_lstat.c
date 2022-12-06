/*--------------------------------------------------------------------------------------------------------------------------
    lstat fonksiyonu ile stat fonksiyonu arasındaki tek fark eğer stat bilgisi elde edilecek dosya bir sembolik bağlantı dosyası ise
    stat fonksiyonun bu bağlantının gösterdiği dosyanın bilgisini alması ancak lstat fonksiyonun bağlantı dosyasının kendi bilgisini almasıdır.
    Diğer dosyalar için bu fonksiyon arasında bir farklılık yoktur. Örneğin:

    parallels@ubuntu-linux-20-04-desktop:~/Study/Unix-Linux-SysProg$ ls -l sample.c x
    -rw-rw-r-- 1 parallels parallels 1748 Dec  4 13:46 sample.c
    lrwxrwxrwx 1 parallels parallels    8 Dec  4 13:47 x -> sample.c

    Burada "x" bir sembolik bağlantı dosyasıdır ve bu dosya "sample.c" dosyasını göstermektedir. İşte biz "x" dosyasının stat bilgilerini
    stat fonksiyonu ile almaya çalışırsak stat bize aslında "sample.c" dosyasının bilgilerini verir. Ancak biz "x" dosyasının stat bilgilerini
    lstat fonksiyonu ile alırsak lstat bize "x" dosyasının kendi bilgisini verir.

    Aşağıdaki örnekte sembolik bağlantı dosyasının lstat ve stat fonksiyonlarıyla stat bilgileri alınmıştır.
---------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

#define LS_BUFSIZE 4096

void exit_sys(const char *msg);
char *get_ls(struct stat *finfo, const char *name);

int main(void)
{
    struct stat finfo;

    if (lstat("x", &finfo) == -1)
        exit_sys("lstat");

    printf("%s\n", get_ls(&finfo, "x"));

    if (stat("x", &finfo) == -1)
        exit_sys("fstat");

    printf("%s\n", get_ls(&finfo, "sample.c"));

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
