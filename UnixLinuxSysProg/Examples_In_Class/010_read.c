/*--------------------------------------------------------------------------------------------------------------------------
    Şimdi bir dosyayı (örneğimizde içerisinde yazı olan bir dosyayı) dosya sonuna kadar read fonksiyonu ile bir döngü içerisinde 
    okuyalım. Bu tür durumlarda klasik yöntem aşağıdaki gibi bir döngü oluşturmaktır:

     while ((result = read(fd, buf, BUFSIZE)) > 0) {
        buf[result] = '\0';
        printf("%s", buf);
    }

    if (result == -1)
        exit_sys("read");

    Bu döngüden IO hatası oluşunca ya da dosya göstericisi dosyanın sonuna geldiğinde çıkılacaktır. 
---------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFSIZE     4096

void exit_sys(const char *msg);

int main(void)
{
    int fd;
    char buf[BUFSIZE + 1];
    ssize_t result;

    if ((fd = open("sample.c", O_RDONLY)) == -1)
        exit_sys("open");
    
    while ((result = read(fd, buf, BUFSIZE)) > 0) {
        buf[result] = '\0';
        printf("%s", buf);
    }

    if (result == -1)
        exit_sys("read");

    close(fd);
    
    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}