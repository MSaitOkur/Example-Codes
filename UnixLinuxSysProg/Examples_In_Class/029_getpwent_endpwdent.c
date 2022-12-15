#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <errno.h>

void exit_sys(const char *msg);

int main(void)
{
    struct passwd *pass;
    while ((errno = 0, pass = getpwent()) != NULL)
    {
        fprintf(stdout, "username: %s\n", pass->pw_name);
        fprintf(stdout, "password: %s\n", pass->pw_passwd);
        fprintf(stdout, "user id : %llu\n", (unsigned long long)pass->pw_uid);
        fprintf(stdout, "group id: %llu\n", (unsigned long long)pass->pw_gid);
        fprintf(stdout, "Gecos   : %s\n", pass->pw_gecos);
        fprintf(stdout, "home dir: %s\n", pass->pw_dir);
        fprintf(stdout, "login pr: %s\n", pass->pw_shell);
        fprintf(stdout, "=====================================================\n");
    }

    if (errno)
        exit_sys("getpwnam");

    endpwent();
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}