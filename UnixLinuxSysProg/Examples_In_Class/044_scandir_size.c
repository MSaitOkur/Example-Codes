#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

void exit_sys(const char *msg);

int myfilter(const struct dirent *de)
{
    return de->d_name[0] == 'a' || de->d_name[0] == 'A';
}

int cmp_size(const struct dirent **de1, const struct dirent **de2)
{
    struct stat finfo1, finfo2;

    if (stat((**de1).d_name, &finfo1) == -1)
        exit_sys("stat");

    if (stat((**de2).d_name, &finfo2) == -1)
        exit_sys("stat");

    if (finfo1.st_size > finfo2.st_size)
        return 1;

    if (finfo1.st_size < finfo2.st_size)
        return -1;

    return 0;
}

int main(int argc, char *argv[])
{
    int result;
    struct dirent **dents;

    if (argc != 2) {
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    if (chdir(argv[1]) == -1) 
        exit_sys("chdir");

    if ((result = scandir(argv[1], &dents, myfilter, cmp_size)) == -1)
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