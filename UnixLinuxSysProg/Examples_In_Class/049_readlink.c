#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

void exit_sys(const char *err_msg);

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Wrong number of arguments!....\n");
        exit(EXIT_FAILURE);
    }

    if (symlink(argv[1], argv[2]) == -1)
        exit_sys("symlink");

    // char buffer[PATH_MAX + 1] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    char buffer[4096 + 1] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    ssize_t result;
    if ((result = readlink(argv[2], buffer, 4096)) == -1)
        exit_sys("readlink");

    fprintf(stdout, "result = %lld\n", (long long)result);

    fprintf(stdout, "path   : %s\n", buffer);                // readlink null karakteri buffera path'in sonuna yazmaz.
    fprintf(stdout, "path   : %.*s\n", (int)result, buffer); // Ekrana yazdirmada bu yontem kullanilmalidir.

    // Ekrana yazdirmada diger bir alternatif
    if (result < 4096)
    {
        buffer[result] = '\0'; 
        puts(buffer);
    }
    else
        fprintf(stderr, "path maybe truncated!..\n");
}

void exit_sys(const char *err_msg)
{
    perror(err_msg);
    exit(EXIT_FAILURE);
}
