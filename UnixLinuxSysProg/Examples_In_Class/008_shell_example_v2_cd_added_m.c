#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>

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
void exit_sys(const char *msg);

char *g_params[MAX_CMD_PARAMS];
int g_nparams;
char g_cwd[PATH_MAX];

CMD g_cmds[] = {
    {"dir", dir_proc},
    {"clear", clear_proc},
    {"pwd", pwd_proc},
    {"cd", cd_proc},
    {NULL, NULL},
};

int main(void)
{
    char cmdline[MAX_CMD_LINE];

    if (getcwd(g_cwd, PATH_MAX) == NULL)
        exit_sys("getcwd");

    while (1)
    {
        fprintf(stdout, "CSD:%s> ", g_cwd);
        if (fgets(cmdline, MAX_CMD_LINE, stdin) == NULL)
            continue;

        char *str;
        if ((str = strchr(cmdline, '\n')) != NULL)
            *str = '\0';

        parse_cmd_line(cmdline);

        if (g_nparams == 0)
            continue;

        if (!strcmp(g_params[0], "exit"))
            break;

        int i;
        for (i = 0; g_cmds[i].name; ++i)
            if (!strcmp(g_params[0], g_cmds[i].name))
            {
                g_cmds[i].proc();
                break;
            }

        if (g_cmds[i].name == NULL)
            fprintf(stdout, "Bad command: %s\n", g_params[0]);
    }
}

void parse_cmd_line(char *cmdline)
{
    g_nparams = 0;

    char *str;
    for (str = strtok(cmdline, " \t"); str; str = strtok(NULL, " \t"))
        g_params[g_nparams++] = str;
}

void dir_proc(void)
{
    fprintf(stdout, "dir command executing...\n");
}

void clear_proc(void)
{
    system("clear");
}

void pwd_proc(void)
{
    if (g_nparams > 1)
    {
        fprintf(stderr, "ERR: pwd command mustn't be used with argument...\n");
        return;
    }
    fprintf(stdout, "%s\n", g_cwd);
}

void cd_proc(void)
{
    char *dir;
    if (g_nparams > 2)
    {
        fprintf(stdout, "ERR: cd too many arguments!...\n");
        return;
    }

    if (g_nparams == 1)
    {
        if ((dir = getenv("HOME")) == NULL)
            exit_sys("Fatal error(getenv)");
    }
    else
        dir = g_params[1];

    if (chdir(dir) == -1)
        fprintf(stderr, "%s", strerror(errno));

    if (getcwd(g_cwd, PATH_MAX) == NULL)
        exit_sys("Fatal error(getcwd)");
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}