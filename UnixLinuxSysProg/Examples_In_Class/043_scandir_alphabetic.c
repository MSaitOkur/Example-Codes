#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void exit_sys(const char *msg);

int myfilter(const struct dirent *de)
{
    return de->d_name[0] == 'a' || de->d_name[0] == 'A';
}

int main(int argc, char *argv[])
{
    int result;
    struct dirent **dents;

    if (argc != 2)
    {
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    if ((result = scandir(argv[1], &dents, myfilter, alphasort)) == -1)
        exit_sys("scandir");

    for (int i = 0; i < result; ++i)
        printf("%s\n", dents[i]->d_name);

    for (int i = 0; i < result; ++i)
        free(dents[i]);
    free(dents);

    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}
