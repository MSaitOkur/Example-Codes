#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

void exit_sys(const char *msg);

void walkdir(const char *path);
static void walkdir_recur(const char *path, int indent_level);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Wrong number of arguments!...\n");
        exit(EXIT_FAILURE);
    }

    walkdir(argv[1]);

    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}

void walkdir(const char *path)
{
    /*walkdir fonksiyonu CWD yi set etmesin.*/
    char cwd[PATH_MAX];
    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        perror("getcwd");
        return;
    }

    /* Ilk cagrida indentation olmasin. Sonra her cagrida bir dizin daha
     * iceri girildigi icin 1 tab iceri yazilsin. */
    walkdir_recur(path, 0);

    /* Butun dizin agaci dolasildiktan sonra CWD eski halinde kalsin. */
    if (chdir(cwd) == -1)
    {
        perror("chdir");
        return;
    }
}

void walkdir_recur(const char *path, int indent_level)
{
    DIR *dir;
    if ((dir = opendir(path)) == NULL)
    {
        fprintf(stderr, "Cannot open directory: %s\n", path);
        return;
    }

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

        struct stat finfo;
        if (lstat(de->d_name, &finfo) == -1)
        {
            fprintf(stderr, "Cannot get stat info: %s\n", de->d_name);
            continue;
        }

        if (S_ISDIR(finfo.st_mode))
        {
            walkdir_recur(de->d_name, indent_level + 1);

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