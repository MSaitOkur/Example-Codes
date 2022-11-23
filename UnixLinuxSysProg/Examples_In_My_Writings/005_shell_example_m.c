#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CMD_LINE 4096
#define MAX_CMD_PARAMS 128

typedef struct tagCMD
{
    char *name;
    void (*proc)(void);
} CMD;

void parse_cmd_line(void);
void dir_proc(void);
void clear_proc(void);
void pwd_proc(void);

char g_cmdline[MAX_CMD_LINE];
char *g_params[MAX_CMD_PARAMS];
int g_nparams;

CMD g_cmds[] = {
    {"dir", dir_proc},
    {"clear", clear_proc},
    {"pwd", pwd_proc},
    {NULL, NULL},
};

int main(void)
{
    while (1)
    {
        fprintf(stdout, "CSD>");
        if (fgets(g_cmdline, MAX_CMD_LINE, stdin) == NULL)
            continue;

        char *str;
        if ((str = strchr(g_cmdline, '\n')) != NULL)
            *str = '\0';

        parse_cmd_line();

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

void parse_cmd_line(void)
{
    g_nparams = 0;

    char *str;
    for (str = strtok(g_cmdline, " \t"); str; str = strtok(NULL, " \t"))
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
        fprintf(stderr, "pwd command mustn't be used with argument...\n");
        return;
    }

    char cwd[4096];
    getcwd(cwd, 4096);
    fprintf(stdout, "%s\n", cwd);
}
