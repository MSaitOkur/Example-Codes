/*--------------------------------------------------------------------------------------------------------------------------
    Proesin çalışma dizinini chdir isimli POSIX fonksiyonuyla değiştirebiliriz. Fonksiyonun prototipi şöyledir:

    #include <unistd.h>

    int chdir(const char *path);

    Fonksiyon yeni çalışma dizinin yol ifadesini parametre olarak alır. Başarı durumunda 0 değerine başarısızlık durumunda -1 değerine 
    geri döner. 
---------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(void)
{
    char buf[PATH_MAX];

    if (getcwd(buf, PATH_MAX) == NULL) 
        exit_sys("getcwd");

    puts(buf);

    if (chdir("/usr/bin") == -1)
        exit_sys("chdir");

    if (getcwd(buf, PATH_MAX) == NULL) 
        exit_sys("getcwd");

    puts(buf);
    
    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}
