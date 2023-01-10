#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

int rmtree(const char *path);
int rmtree_recur(const char *path);

void exit_sys(const char *err_msg);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Wrong number of arguments!...\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 1; i < argc; ++i)
        if (rmtree(argv[i]) == -1)
            exit_sys("rmtree main");
}

int rmtree(const char *path)
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        perror("getcwd rmtree");
        return -1;
    }

    if (rmtree_recur(path) == -1)
        return -1;

    if (chdir(cwd) == -1)
    {
        perror("chdir rmtree");
        return -1;
    }

    if (rmdir(path) == -1)
    {
        perror("rmdir rmtree");
        return -1;
    }

    return 0;
}

int rmtree_recur(const char *path)
{
    DIR *dirptr;
    if ((dirptr = opendir(path)) == NULL)
    {
        perror("opendir rmtree_recur");
        return -1;
    }

    if (chdir(path) == -1)
    {
        perror("chdir rmtree_recur");
        goto RETURN_UNSUCCESS;
    }

    struct dirent *dentry;
    while (errno = 0, (dentry = readdir(dirptr)) != NULL)
    {
        if (!strcmp(dentry->d_name, ".") || !strcmp(dentry->d_name, ".."))
            continue;

        struct stat fileinfo;
        if (lstat(dentry->d_name, &fileinfo) == -1)
        {
            perror("lstat");
            continue;
        }

        if (S_ISDIR(fileinfo.st_mode))
        {
            if (rmtree_recur(dentry->d_name) == -1)
                goto RETURN_UNSUCCESS;

            if (chdir("..") == -1)
            {
                perror("chdir isdir");
                goto RETURN_UNSUCCESS;
            }

            fprintf(stdout, "%s dizini silindi\n", dentry->d_name);

            if (rmdir(dentry->d_name) == -1)
            {
                perror("rmdir");
                goto RETURN_UNSUCCESS;
            }
        }
        else
        {
            fprintf(stdout, "%s dosyasi silindi\n", dentry->d_name);

            if (unlink(dentry->d_name) == -1)
            {
                perror("unlink");
                goto RETURN_UNSUCCESS;
            }
        }
    }
    if (errno)
    {
        perror("readdir");
        goto RETURN_UNSUCCESS;
    }

    return 0;

RETURN_UNSUCCESS:
    closedir(dirptr);
    return -1;
}

void exit_sys(const char *err_msg)
{
    perror(err_msg);
    exit(EXIT_FAILURE);
}