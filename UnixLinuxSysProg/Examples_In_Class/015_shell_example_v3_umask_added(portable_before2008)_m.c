#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_CMD_LINE 4096
#define MAX_CMD_PARAMS 128

typedef struct tagCMD
{
    char *name;
    void (*proc)(void);
} CMD;

void parse_cmd_line(char *cmdline);
void dir_proc(void);
void clear_proc(void);
void pwd_proc(void);
void cd_proc(void);
void umask_proc(void);

int check_umask_arg(const char *);
int umask_octal_to_decimal(mode_t umask_val_octal);
void set_umask_val(unsigned int octal_val);

void exit_sys(const char *msg);

char *g_params[MAX_CMD_PARAMS];
int g_nparams;
char g_cwd[PATH_MAX];

CMD g_cmds[] = {
    {"dir", dir_proc},
    {"clear", clear_proc},
    {"pwd", pwd_proc},
    {"cd", cd_proc},
    {"umask", umask_proc},
    {NULL, NULL}};

int main(void)
{
    char cmdline[MAX_CMD_LINE];
    char *str;
    int i;

    if (getcwd(g_cwd, PATH_MAX) == NULL)
        exit_sys("fatal error (getcwd)");

    for (;;)
    {
        printf("CSD:%s>", g_cwd);
        if (fgets(cmdline, MAX_CMD_LINE, stdin) == NULL)
            continue;
        if ((str = strchr(cmdline, '\n')) != NULL)
            *str = '\0';
        parse_cmd_line(cmdline);
        if (g_nparams == 0)
            continue;
        if (!strcmp(g_params[0], "exit"))
            break;
        for (i = 0; g_cmds[i].name != NULL; ++i)
            if (!strcmp(g_params[0], g_cmds[i].name))
            {
                g_cmds[i].proc();
                break;
            }
        if (g_cmds[i].name == NULL)
            printf("ERR: bad command: %s\n", g_params[0]);
    }

    return 0;
}

void parse_cmd_line(char *cmdline)
{
    char *str;

    g_nparams = 0;
    for (str = strtok(cmdline, " \t"); str != NULL; str = strtok(NULL, " \t"))
        g_params[g_nparams++] = str;
}

void dir_proc(void)
{
    printf("dir command executing..\n");
}

void clear_proc(void)
{
    system("clear");
}

void pwd_proc(void)
{
    printf("%s\n", g_cwd);
}

void cd_proc(void)
{
    char *dir;

    if (g_nparams > 2)
    {
        printf("ERR: too many arguments!\n");
        return;
    }
    if (g_nparams == 1)
    {
        if ((dir = getenv("HOME")) == NULL)
            exit_sys("fatal error (getenv");
    }
    else
        dir = g_params[1];

    if (chdir(dir) == -1)
    {
        printf("ERR: %s\n", strerror(errno));
        return;
    }

    if (getcwd(g_cwd, PATH_MAX) == NULL)
        exit_sys("fatal error (getcwd)");
}

void umask_proc(void)
{
    if (g_nparams > 2)
    {
        fprintf(stderr, "ERR: Too many arguments in umask command!...\n");
        return;
    }

    if (g_nparams == 1)
    {
        mode_t umask_val_octal = umask(0);
        umask(umask_val_octal);

        fprintf(stdout, "%04o\n", umask_octal_to_decimal(umask_val_octal));
        return;
    }

    if (check_umask_arg(g_params[1]) == 0)
    {
        fprintf(stderr, "ERR: Octal number out of range : %s\n", g_params[1]);
        return;
    }

    unsigned int umask_val;
    sscanf(g_params[1], "%o", &umask_val); // The entered value is octal. It must be read formatted.

    set_umask_val(umask_val);
    return;
}

int check_umask_arg(const char *str)
{
    size_t arg_len = strlen(str);

    if (arg_len > 4)
        return 0;

    for (size_t i = 0; i < arg_len; ++i)
        if (str[i] < '0' || str[i] > '7')
            return 0;

    return 1;
}

int umask_octal_to_decimal(mode_t umask_val_octal)
{
    static mode_t mode_bits[] = {
        S_IXOTH,
        S_IWOTH,
        S_IROTH,
        S_IXGRP,
        S_IWGRP,
        S_IRGRP,
        S_IXUSR,
        S_IWUSR,
        S_IRUSR,
        S_ISVTX, // sticky bit
        S_ISGID, // set group id
        S_ISUID, // set user id
    };

    int decimal_umask_val = 0;

    for (size_t i = 0; i < 12; ++i)
        if (umask_val_octal & mode_bits[i])
            decimal_umask_val |= 1 << i;

    return decimal_umask_val;
}

void set_umask_val(unsigned int octal_val)
{
    static mode_t mode_bits[] = {
        S_IXOTH,
        S_IWOTH,
        S_IROTH,
        S_IXGRP,
        S_IWGRP,
        S_IRGRP,
        S_IXUSR,
        S_IWUSR,
        S_IRUSR,
        S_ISVTX, // sticky bit
        S_ISGID, // set group id
        S_ISUID, // set user id
    };

    mode_t umask_val_standart = 0;

    for (size_t i = 0; i < 12; ++i)
        if ((octal_val >> i) & 1)
            umask_val_standart |= mode_bits[i];

    umask(umask_val_standart);
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}
