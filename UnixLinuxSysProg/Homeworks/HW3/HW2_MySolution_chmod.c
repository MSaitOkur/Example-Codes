#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void exit_sys(const char *err);

int is_mode_number(const char *mode_str);
int check_octal_mode(const char *mode_str);
int set_entered_mode(const char *mode_arg_str, const char *const *const filenames);

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "[ERR] usage: <chmod> <modes> <filename(s)>\n");
        exit(EXIT_FAILURE);
    }

    if (is_mode_number(argv[1]))
    {
        if (!check_octal_mode(argv[1]))
        {
            fprintf(stderr, "[ERR] Wrong octal mode: %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }

        int octal_mode;
        sscanf(argv[1], "%o", &octal_mode);

        for (size_t i = 2; argv[i]; ++i)
            if (chmod(argv[i], octal_mode) == -1)
                exit_sys("[ERR] chmod");
    }
    else
    {
        char mode_str[64] = "";
        strcpy(mode_str, argv[1]);
        umask(0);

        if (strchr(mode_str, ',') == NULL)
        {
            if (set_entered_mode(mode_str, (const char *const *const)(argv + 2)) != 0)
                exit(EXIT_FAILURE);
        }
        else
        {
            for (char *str = strtok(mode_str, ","); str; str = strtok(NULL, ","))
                if (set_entered_mode(str, (const char *const *const)(argv + 2)) != 0)
                    exit(EXIT_FAILURE);
        }
    }
}

void exit_sys(const char *err)
{
    perror(err);
    exit(EXIT_FAILURE);
}

int is_mode_number(const char *mode_str)
{
    return mode_str[0] >= '0' && mode_str[0] <= '9';
}

int check_octal_mode(const char *mode_str)
{
    if (strlen(mode_str) > 3)
        return 0;

    for (size_t i = 0; mode_str[i]; ++i)
        if (mode_str[0] < '0' || mode_str[0] > '7')
            return 0;

    return 1;
}

int set_entered_mode(const char *mode_str, const char *const *filenames)
{
    int u_flag = 0, g_flag = 0, o_flag = 0, a_flag = 0;

    for (size_t i = 0; mode_str[i] != '\0'; ++i)
        if (mode_str[i] == 'u')
            u_flag = 1;
        else if (mode_str[i] == 'g')
            g_flag = 1;
        else if (mode_str[i] == 'o')
            o_flag = 1;
        else if (mode_str[i] == 'a')
            a_flag = 1;

    if (u_flag + g_flag + o_flag == 0)
        a_flag = 1;

    mode_t u_mode = 0, g_mode = 0, o_mode = 0;

    const char *ptr;
    if ((ptr = strchr(mode_str, '+')))
    {
        for (size_t i = 1; *(ptr + i) != '\0'; ++i)
        {
            switch (ptr[i])
            {
            case 'r':
                u_mode |= u_flag || a_flag ? S_IRUSR : 0;
                g_mode |= g_flag || a_flag ? S_IRGRP : 0;
                o_mode |= o_flag || a_flag ? S_IROTH : 0;
                break;
            case 'w':
                u_mode |= u_flag || a_flag ? S_IWUSR : 0;
                g_mode |= g_flag || a_flag ? S_IWGRP : 0;
                o_mode |= o_flag || a_flag ? S_IWOTH : 0;
                break;
            case 'x':
                u_mode |= u_flag || a_flag ? S_IXUSR : 0;
                g_mode |= g_flag || a_flag ? S_IXGRP : 0;
                o_mode |= o_flag || a_flag ? S_IXOTH : 0;
                break;
            }
        }

        for (size_t i = 0; filenames[i]; ++i)
        {
            struct stat finfo;
            if (stat(filenames[i], &finfo) == -1)
                return -1;

            if (chmod(filenames[i], finfo.st_mode | u_mode | g_mode | o_mode) == -1)
                return -1;
        }
    }
    else if ((ptr = strchr(mode_str, '-')))
    {
        for (size_t i = 1; *(ptr + i) != '\0'; ++i)
        {
            switch (ptr[i])
            {
            case 'r':
                u_mode |= u_flag || a_flag ? S_IRUSR : 0;
                g_mode |= g_flag || a_flag ? S_IRGRP : 0;
                o_mode |= o_flag || a_flag ? S_IROTH : 0;
                break;
            case 'w':
                u_mode |= u_flag || a_flag ? S_IWUSR : 0;
                g_mode |= g_flag || a_flag ? S_IWGRP : 0;
                o_mode |= o_flag || a_flag ? S_IWOTH : 0;
                break;
            case 'x':
                u_mode |= u_flag || a_flag ? S_IXUSR : 0;
                g_mode |= g_flag || a_flag ? S_IXGRP : 0;
                o_mode |= o_flag || a_flag ? S_IXOTH : 0;
                break;
            }
        }

        for (size_t i = 0; filenames[i]; ++i)
        {
            struct stat finfo;
            if (stat(filenames[i], &finfo) == -1)
                return -1;

            if (chmod(filenames[i], finfo.st_mode & ~(u_mode | g_mode | o_mode)) == -1)
                return -1;
        }
    }
    else if ((ptr = strchr(mode_str, '=')))
    {
        for (size_t i = 1; *(ptr + i) != '\0'; ++i)
        {
            switch (ptr[i])
            {
            case 'r':
                u_mode |= u_flag || a_flag ? S_IRUSR : 0;
                g_mode |= g_flag || a_flag ? S_IRGRP : 0;
                o_mode |= o_flag || a_flag ? S_IROTH : 0;
                break;
            case 'w':
                u_mode |= u_flag || a_flag ? S_IWUSR : 0;
                g_mode |= g_flag || a_flag ? S_IWGRP : 0;
                o_mode |= o_flag || a_flag ? S_IWOTH : 0;
                break;
            case 'x':
                u_mode |= u_flag || a_flag ? S_IXUSR : 0;
                g_mode |= g_flag || a_flag ? S_IXGRP : 0;
                o_mode |= o_flag || a_flag ? S_IXOTH : 0;
                break;
            }
        }

        for (size_t i = 0; filenames[i]; ++i)
        {
            if (chmod(filenames[i], u_mode | g_mode | o_mode) == -1)
                return -1;
        }
    }
    else
    {
        fprintf(stdout, "[ERR] Wrong mode: %s\n", mode_str);
        return -2;
    }

    return 0;
}
