#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define _XOPEN_SOURCE 500
#define __USE_XOPEN_EXTENDED 1

#include <ftw.h>

void exit_sys(const char *err_msg);

int callback(const char *path, const struct stat *finfo, int flag, struct FTW *ftw);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Wrong number of arguments!....\n");
        exit(EXIT_FAILURE);
    }

    int result;
    if ((result = nftw(argv[1], callback, 100, FTW_PHYS)) == -1)
        exit_sys("nftw");

    fprintf(stdout, "result = %d\n", result);
}

void exit_sys(const char *err_msg)
{
    perror(err_msg);
    exit(EXIT_FAILURE);
}

int callback(const char *path, const struct stat *finfo, int flag, struct FTW *ftw)
{

    switch (flag)
    {
    case FTW_DNR:
        fprintf(stdout, "%*s%s (Cannot read)\n", ftw->level * 4, "", path + ftw->base);
        break;
    case FTW_NS:
        fprintf(stdout, "%*s%s (Cannot get stat info)\n", ftw->level * 4, "", path + ftw->base);
        break;
    default:
        fprintf(stdout, "%*s%s\n", ftw->level * 4, "", path + ftw->base);
    }

    return 0;
}
