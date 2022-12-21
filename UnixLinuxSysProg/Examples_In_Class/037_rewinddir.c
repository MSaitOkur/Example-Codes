#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

void exit_sys(const char *msg);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Wrong number of arguments!...\n");
        exit(EXIT_FAILURE);
    }

    DIR *dir;
    if ((dir = opendir(argv[1])) == NULL)
        exit_sys("opendir");

    struct dirent *de;
    while (errno = 0, (de = readdir(dir)) != NULL)
        fprintf(stdout, "%s\n", de->d_name);

    if (errno != 0)
        exit_sys("readdir");

    rewinddir(dir);
    fprintf(stdout, "==================================\n");

    while (errno = 0, (de = readdir(dir)) != NULL)
        fprintf(stdout, "%s\n", de->d_name);

    if (errno != 0)
        exit_sys("readdir");

    closedir(dir);

    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}
