#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void exit_sys(const char *msg);

void walkdir(const char *path, int indent_level);

// void walkdir(const char *path);
// int walkdir(const char *path, int (*proc)(const char *, const struct stat *, int));

/*Sınıfta yapılan dizin ağacını dolaşan örnekleri fonksiyonların at'li
versyonları ile yeniden yazınız. Böylece bu özyinelemeli fonksiyonlarda chdir
fonksiyonu ile prosesin çalışma dizinini değiştimeyiniz. Bunun için
muhtemelen fdopendir ve fstatat fonksiyonlarının kullanılması gerekecektir.
Tabii fonksiyonların parametrik yapılarında da değişiklikler olacaktır.
Yazılacak fonksiyonlar şu prototiplere sahip olmalıdır:*/

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
    int fddir;
    if ((fddir = dirfd(dir)) == -1)
    {
        fprintf(stderr, "Cannot get descriptor of directory: %s", path);
        return;
    }

    struct dirent *de;
    while (errno = 0, (de = readdir(dir)) != NULL)
    {
        fprintf(stdout, "%*s%s\n", indent_level * 4, "", de->d_name);

        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
            continue;

        struct stat finfo;
        if (fstatat(fddir, de->d_name, &finfo, AT_SYMLINK_NOFOLLOW) == -1)
        {
            fprintf(stderr, "Cannot get stat info: %s\n", de->d_name);
            continue;
        }

        if (S_ISDIR(finfo.st_mode))
        {
            char new_path[PATH_MAX];
            sprintf(new_path, "%s/%s", path, de->d_name);
            walkdir(new_path, indent_level + 1);
        }
    }

    if (errno)
        fprintf(stderr, "Cannot read directory info: %s\n", path);

    closedir(dir);
}