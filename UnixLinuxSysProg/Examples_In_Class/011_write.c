/*--------------------------------------------------------------------------------------------------------------------------
    Dosyaya yazma yapmak için write isimli POSIX fonksiyonu kullanılmaktadır. Bu fonksiyon da pek çok sistemde doğrudan işletim sisteminin
    dosyaya yazma yapan sistem fonksiyonunu (Linux'ta sys_write) çağırmaktadır. Prototipi şöyledir:

    #include <unistd.h>

    ssize_t write(int fd, const void *buf, size_t nbyte);

    Fonksiyonun birinci parametresi yazma yapılacak dosyaya ilişkin dosya betimleyicisini belirtir. İkinci parametre yazılacak 
    bilgilerin bulunduğu bellek adresidir. Üçüncü parametre yazılacak byte sayısını belirtir. write fonksiyonu başarılı olarak yazılan 
    byte sayısı ile geri dönmektedir. Normal olarak bu değer üçncü parametrede belirtilen yazılmak istenen byte sayısıdır. Ancak çok seyrek 
    bazı durumlarda (örneğin diskin dolu olması gibi) write talep edilenden daha az byte'ı yazabilir. Bu duurmda yazabildiği byte sayısı ile geri döner. 
    write başarısız olursa -1 değerinegeri dönmektedir. 
---------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(void)
{
    int fd;
    char buf[] = "this is a test";
    ssize_t result;

    if ((fd = open("test.txt", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1)
        exit_sys("open");
    
    if (write(fd, buf, strlen(buf)) == -1)
        exit_sys("write");

    close(fd);
    
    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}
