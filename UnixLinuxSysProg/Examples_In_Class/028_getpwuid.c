#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <errno.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    struct passwd *pass;
    errno = 0;

    if ((pass = getpwuid(atoi(argv[1]))) == NULL)
    {
        if (errno == 0)
        {
            fprintf(stderr, "user name couldn't found!...\n");
            exit(EXIT_FAILURE);
        }

        exit_sys("getpwnam");
    }

    fprintf(stdout, "username: %s\n", pass->pw_name);
    fprintf(stdout, "password: %s\n", pass->pw_passwd);
    fprintf(stdout, "user id : %llu\n", (unsigned long long)pass->pw_uid);
    fprintf(stdout, "group id: %llu\n", (unsigned long long)pass->pw_gid);
    fprintf(stdout, "Gecos   : %s\n", pass->pw_gecos);
    fprintf(stdout, "home dir: %s\n", pass->pw_dir);
    fprintf(stdout, "login pr: %s\n", pass->pw_shell);
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}