#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

#define BUFFER_MAX 4096

void exit_sys(const char *msg);
const char *get_file_modes(const struct stat *finfo);
char *get_ls_li(char *buffer, const char *filename, const struct stat *finfo);

int main(int argc, char *argv[])
{
    char buffer[BUFFER_MAX] = "";

    if (argc == 1)
    {
        fprintf(stderr, "File name must be entered!...\n");
        exit(EXIT_FAILURE);
    }

    struct stat finfo;
    for (size_t i = 1; i < argc; ++i)
    {
        if (stat(argv[1], &finfo) == -1)
            exit_sys("stat");

        puts(get_ls_li(buffer, argv[i], &finfo));
    }
}

char *get_ls_li(char *buffer, const char *filename, const struct stat *finfo)
{
    size_t index = 0;
    index += sprintf(buffer + index, "%llu ", (long long unsigned)finfo->st_ino);
    index += sprintf(buffer + index, "%s ", get_file_modes(finfo));
    index += sprintf(buffer + index, "%lld ", (long long int)finfo->st_nlink);

    // index += sprintf(buffer + index, "%lld ", finfo->st_uid);
    struct passwd *pass;
    if ((pass = getpwuid(finfo->st_uid)) == NULL)
        index += sprintf(buffer + index, "%lld ", (long long int)finfo->st_uid);
    else
        index += sprintf(buffer + index, "%s ", pass->pw_name);

    // index += sprintf(buffer + index, "%lld ", finfo->st_gid);
    struct group *grp;
    if ((grp = getgrgid(finfo->st_gid)) == NULL)
        index += sprintf(buffer + index, "%lld ", (long long int)finfo->st_gid);
    else
        index += sprintf(buffer + index, "%s ", grp->gr_name);

    index += sprintf(buffer + index, "%lld ", (long long int)finfo->st_size);
    index += strftime(buffer + index, BUFFER_MAX, " %b %2e %H:%M ", localtime(&finfo->st_mtim.tv_sec));

    sprintf(buffer + index, "%s", filename);
                                              
    return buffer;
}

const char *get_file_modes(const struct stat *finfo)
{
    static mode_t filetypes[] = {S_IFBLK, S_IFCHR, S_IFIFO,
                                 S_IFREG, S_IFDIR, S_IFLNK, S_IFSOCK};
    static char mode_str[11] = "";
    size_t mode_str_idx = 0;

    for (size_t i = 0; i < sizeof filetypes / sizeof *filetypes; ++i)
        if ((finfo->st_mode & S_IFMT) == filetypes[i])
        {
            sprintf(mode_str + mode_str_idx++, "%c", "bcp-dls"[i]);
            break;
        }

    static mode_t modes[] = {S_IRUSR, S_IWUSR, S_IXUSR,
                             S_IRGRP, S_IWGRP, S_IXGRP,
                             S_IROTH, S_IWOTH, S_IXOTH};

    for (size_t i = 0; i < sizeof modes / sizeof *modes; ++i)
        sprintf(mode_str + mode_str_idx++, "%c", modes[i] & finfo->st_mode ? "rwx"[i % 3] : '-');

    return mode_str;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}
