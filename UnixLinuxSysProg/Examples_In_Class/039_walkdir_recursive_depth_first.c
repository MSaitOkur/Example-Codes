#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

void exit_sys(const char *msg);

void walkdir(const char *path, int indent_level);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Wrong number of arguments!...\n");
        exit(EXIT_FAILURE);
    }

    walkdir(argv[1], 0);

    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}

void walkdir(const char *path, int indent_level)
{
    DIR *dir;
    if ((dir = opendir(path)) == NULL)
    {
        fprintf(stderr, "Cannot open directory: %s\n", path);
        return;
    }

    /* Her recursive cagride uzerinde calisilan dizin degismektedir.
     * Degisilen bir dizine gecildigi zaman cwd'nin degismesi gerekmektedir.
     * Yani eger fonksiyonlarin at'li versiyonlari kullanilmaz ise
     * Yani relative bir path ile erisim soz konusu ise bu durumda
     * cwd degistirilir. */
    if (chdir(path) == -1)
    {
        fprintf(stderr, "CWD cannot change to %s!...\n", path);
        goto EXIT;
    }

    struct dirent *de;
    while (errno = 0, (de = readdir(dir)) != NULL)
    {
        fprintf(stdout, "%*s%s\n", indent_level * 4, "", de->d_name);

        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
            continue;

        /* Eger lstat'a sadece dosya ismi yani relative bir path gonderilecekse bu durumda
         * yukarida yapildigi gibi her yeni dizine girildigi zaman CWD set edilmelidir.
         * Yada absolute bir path gonderilmelidir.
         * Yada fstatat kullanilmalidir. */
        struct stat finfo;
        if (lstat(de->d_name, &finfo) == -1)
        {
            fprintf(stderr, "Cannot get stat info: %s\n", de->d_name);
            continue;
        }

        if (S_ISDIR(finfo.st_mode))
        {
            // Eger dizin icinde karsilasilan dosya dizin ise icine gir!
            walkdir(de->d_name, indent_level + 1);

            /* Recursiondan cikildiginda otomatik olarak cwd'nin bir ustteki dizine
             * gecirilmesi gerekmektedir. */
            if (chdir("..") == -1)
            {
                fprintf(stderr, "CWD cannot change to %s!...\n", "..");
                goto EXIT;
            }
        }
    }

    if (errno)
        fprintf(stderr, "Cannot read directory info: %s\n", path);

EXIT:
    closedir(dir);
}