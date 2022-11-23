/*--------------------------------------------------------------------------------------------------------------------------
    Bir kullanıcı ile login olunduğunda login programı /etc/passwd dosyasında belirtilen programı çalıştırır. 
    Biz istersek bu programı değiştirip kendi istediğimiz bir programın çalıştırılmasını sağlayabiliriz. Kendi programımız 
    myshell isimli program olsun ve onu /bin dizinine kopyalamış olalım. /etc/passwd dosyasnının içeriğini şöyle dğeiştirebiliriz:

    ali:x:1002:1001::/home/ali:/bin/myshell
---------------------------------------------------------------------------------------------------------------------------*/
/* myshell.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CMD_LINE        4096
#define MAX_CMD_PARAMS      128

typedef struct tagCMD {
    char *name;
    void (*proc)(void);
} CMD;

void parse_cmd_line(char *cmdline);
void dir_proc(void);
void clear_proc(void);
void pwd_proc(void);

char *g_params[MAX_CMD_PARAMS];
int g_nparams;

CMD g_cmds[] = {
    {"dir", dir_proc},
    {"clear", clear_proc},
    {"pwd", pwd_proc},
    {NULL, NULL}
};

int main(void)
{
    char cmdline[MAX_CMD_LINE];
    char *str;
    int i;

    for (;;) {
        printf("CSD>");
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
            if (!strcmp(g_params[0], g_cmds[i].name)) {
                g_cmds[i].proc();
                break;
            }
        if (g_cmds[i].name == NULL)
            printf("bad command: %s\n", g_params[0]);
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
    char cwd[4096];

    if (g_nparams > 1) {
        printf("pwd command must be used withoud argument!..\n");
        return;
    }

    getcwd(cwd, 4096);

    printf("%s\n", cwd);
}

