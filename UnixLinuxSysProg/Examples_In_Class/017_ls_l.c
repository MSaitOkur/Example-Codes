/*--------------------------------------------------------------------------------------------------------------------------
    Aşağıdaki örnekte get_ls isimli fonksiyon bizden stat yapısını ve dosyanın ismini alarak char türden static bir dizinin içerisine
    dosya bilgilerini ls -l formatında kodlamaktadır. Ancak biz henüz kullanıcı id'sini ve grup id'sini /etc/passwd ve /etc/group
    dosyalarına başvurarak isimlere dönüştürmedik. Buı nedenle bu örnekte dosyaların kullanıcı ve grup id'leri yazı olarak değil
    sayı olarak kodlanmıştır.
---------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

#define LS_BUFSIZE 4096

void exit_sys(const char *msg);
char *get_ls(struct stat *finfo, const char *name);

int main(int argc, char *argv[])
{
    struct stat finfo;
    struct tm *pt;

    if (argc == 1)
    {
        fprintf(stderr, "file(s) must be specified!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; ++i)
    {
        if (stat(argv[i], &finfo) == -1)
            exit_sys("stat");
        printf("%s\n", get_ls(&finfo, argv[i]));
    }

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
