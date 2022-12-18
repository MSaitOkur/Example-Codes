#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <errno.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    struct group *grp;
    while ((errno = 0, grp = getgrent()) != NULL)
    {
        fprintf(stdout, "Group Name                       : %s\n", grp->gr_name);
        fprintf(stdout, "Group Password                   : %s\n", grp->gr_passwd);
        fprintf(stdout, "Group ID                         : %llu\n", (unsigned long long)grp->gr_gid);
        fprintf(stdout, "Supplementary users of this group: ");
        for (size_t i = 0; grp->gr_mem[i] != NULL; ++i)
        {
            if (i != 0)
                fprintf(stdout, ", ");
            fprintf(stdout, "%s", grp->gr_mem[i]);
        }

        fprintf(stdout, "\n=====================================================\n");
    }

    if (errno)
        exit_sys("getgrent");

    endgrent();
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}