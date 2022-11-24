/*--------------------------------------------------------------------------------------------------------------------------
    Prosesin çalışma dizini getcwd isimli POSIX fonksiyonuyla elde edilebilmektedir. Fonksiyonun prototipi şöyledir:

    #include <unistd.h>

    char *getcwd(char *buf, size_t size);

    Fonksiyonun birinci parametresi yol ifadesinin yerleştirileceği dizinin adresini ikinci parametresi ise bu dizinin null karakter 
    dahil olmak üzere uzunluğunu almaktadır. Fonksiyon başarı durumunda birinci parametresiyle belirtilen adresin aynısına başarısılık durumunda 
    NULL adrese geri dönmektedir. Fonksiyonun ikinci parametresinde belirtilen uzunluk eğer yol ifadesini içerecek büyüklükte değilse 
    fonksiyon başarısız olmaktadır. 

    UNIX/Linux sistemlerinde bir yol ifadesinin maksimum karakter sayısı (null karakter dahil olmak üzere) <limits.h> içerisindeki 
    PATH_MAX sembolik sabitiyle belirtilmiştir. Ancak bu konuda bazı ayrıntılar vardır. Bazı sistemlerde bu PATH_MAX Sembolik sabiti tanımlı değildir. 
    Dolayısıyla bazı sistemlerde maksimum yol ifadesi uzunluğu pathconf denilen özel bir fonksiyon ile elde edilebilmektedir. Linux sistemlerinde 
    <limits.h> dosyası içerisinde PATH_MAX 4096 olarak define edilmiştir. 
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
    
    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}