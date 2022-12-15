#include "csd_grp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// struct group
// {
//     char *gr_name;   /* group name */
//     char *gr_passwd; /* group password */
//     gid_t gr_gid;    /* group ID */
//     char **gr_mem;   /* NULL-terminated array of pointers to names of group members */
// };

#define MAX_LINE 4096
#define MAX_SUP_MEMBERS 4096

static char static_buffer[MAX_LINE] = "";
static char *group_members_array[MAX_SUP_MEMBERS] = {NULL};
static struct group static_grp = {.gr_mem = group_members_array};

struct group *csd_getgrnam(const char *name)
{
    FILE *f;
    if ((f = fopen("/etc/group", "rb")) == NULL)
        return NULL;

    while (fgets(static_buffer, MAX_LINE, f))
        if (!strncmp(static_buffer, name, strlen(name)))
        {
            static_grp.gr_name = strtok(static_buffer, ":");
            static_grp.gr_passwd = strtok(NULL, ":");
            static_grp.gr_gid = strtoull(strtok(NULL, ":"), NULL, 10);

            size_t sup_members_idx = 0;
            for (char *ptr = strtok(NULL, ",\n"); ptr; ptr = strtok(NULL, ",\n"))
                static_grp.gr_mem[sup_members_idx++] = ptr;
            static_grp.gr_mem[sup_members_idx] = NULL;

            return &static_grp;
        }

    return NULL;
}

struct group *csd_getgrgid(gid_t gid)
{
    FILE *f;
    if ((f = fopen("/etc/group", "rb")) == NULL)
        return NULL;

    while (fgets(static_buffer, MAX_LINE, f))
    {
        char *ptr = static_buffer;
        for (size_t i = 0; i < 2; ++i)
            ptr = strchr(ptr, ':') + 1;

        uid_t gid_local = (uid_t)strtoul(ptr, NULL, 10);

        if (gid == gid_local)
        {
            static_grp.gr_name = strtok(static_buffer, ":");
            static_grp.gr_passwd = strtok(NULL, ":");
            static_grp.gr_gid = strtoull(strtok(NULL, ":"), NULL, 10);

            size_t sup_members_idx = 0;
            for (char *ptr = strtok(NULL, ",\n"); ptr; ptr = strtok(NULL, ",\n"))
                static_grp.gr_mem[sup_members_idx++] = ptr;
            static_grp.gr_mem[sup_members_idx] = NULL;

            return &static_grp;
        }
    }

    return NULL;
}

static FILE *fgrent = NULL;

struct group *csd_getgrent(void)
{
    if (!fgrent)
        if ((fgrent = fopen("/etc/group", "rb")) == NULL)
            return NULL;

    if (fgets(static_buffer, MAX_LINE, fgrent))
    {
        static_grp.gr_name = strtok(static_buffer, ":");
        static_grp.gr_passwd = strtok(NULL, ":");
        static_grp.gr_gid = strtoull(strtok(NULL, ":"), NULL, 10);

        size_t sup_members_idx = 0;
        for (char *ptr = strtok(NULL, ",\n"); ptr; ptr = strtok(NULL, ",\n"))
            static_grp.gr_mem[sup_members_idx++] = ptr;
        static_grp.gr_mem[sup_members_idx] = NULL;

        return &static_grp;
    }

    return NULL;
}

void csd_endgrent(void)
{
    fclose(fgrent);
    fgrent = NULL;
}

void csd_setgrent(void)
{
    if (fgrent)
        rewind(fgrent);
}

