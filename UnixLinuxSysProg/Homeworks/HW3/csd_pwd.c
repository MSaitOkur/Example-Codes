#include "csd_pwd.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// struct passwd {
//     char   *pw_name;       /* username */
//     char   *pw_passwd;     /* user password */
//     uid_t   pw_uid;        /* user ID */
//     gid_t   pw_gid;        /* group ID */
//     char   *pw_gecos;      /* user information */
//     char   *pw_dir;        /* home directory */
//     char   *pw_shell;      /* shell program */
// };

#define MAX_LINE 4096

static char static_buffer[MAX_LINE] = "";
static struct passwd static_pw = {};

struct passwd *csd_getpwnam(const char *name)
{
    FILE *f;
    if ((f = fopen("/etc/passwd", "rb")) == NULL)
        return NULL;

    while (fgets(static_buffer, MAX_LINE, f))
        if (!strncmp(static_buffer, name, strlen(name)))
        {
            static_pw.pw_name = strtok(static_buffer, ":");
            static_pw.pw_passwd = strtok(NULL, ":");
            static_pw.pw_uid = strtoll(strtok(NULL, ":"), NULL, 10);
            static_pw.pw_gid = strtoll(strtok(NULL, ":"), NULL, 10);
            static_pw.pw_gecos = strtok(NULL, ":");
            static_pw.pw_dir = strtok(NULL, ":");
            static_pw.pw_shell = strtok(NULL, ":\n");

            return &static_pw;
        }

    return NULL;
}

struct passwd *csd_getpwuid(uid_t uid)
{
    FILE *f;
    if ((f = fopen("/etc/passwd", "rb")) == NULL)
        return NULL;

    while (fgets(static_buffer, MAX_LINE, f))
    {
        char *ptr = static_buffer;
        for (size_t i = 0; i < 2; ++i)
            ptr = strchr(ptr, ':') + 1;

        uid_t uid_local = (uid_t)strtoul(ptr, NULL, 10);

        if (uid == uid_local)
        {
            static_pw.pw_name = strtok(static_buffer, ":");
            static_pw.pw_passwd = strtok(NULL, ":");
            static_pw.pw_uid = strtoll(strtok(NULL, ":"), NULL, 10);
            static_pw.pw_gid = strtoll(strtok(NULL, ":"), NULL, 10);
            static_pw.pw_gecos = strtok(NULL, ":");
            static_pw.pw_dir = strtok(NULL, ":");
            static_pw.pw_shell = strtok(NULL, ":\n");

            return &static_pw;
        }
    }

    return NULL;
}

static FILE *fpwent = NULL;

struct passwd *csd_getpwent(void)
{
    if (!fpwent)
        if ((fpwent = fopen("/etc/passwd", "rb")) == NULL)
            return NULL;

    if (fgets(static_buffer, MAX_LINE, fpwent))
    {
        static_pw.pw_name = strtok(static_buffer, ":\n");
        static_pw.pw_passwd = strtok(NULL, ":\n");
        static_pw.pw_uid = strtoll(strtok(NULL, ":\n"), NULL, 10);
        static_pw.pw_gid = strtoll(strtok(NULL, ":\n"), NULL, 10);
        static_pw.pw_gecos = strtok(NULL, ":\n");
        static_pw.pw_dir = strtok(NULL, ":\n");
        static_pw.pw_shell = strtok(NULL, ":\n");

        return &static_pw;
    }

    return NULL;
}

void csd_endpwent(void)
{
    fclose(fpwent);
    fpwent = NULL;
}

void csd_setpwent(void)
{
    if (fpwent)
        rewind(fpwent);
}
