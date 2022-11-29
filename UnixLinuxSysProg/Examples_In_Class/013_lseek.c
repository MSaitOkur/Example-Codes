/*--------------------------------------------------------------------------------------------------------------------------
    Dosya göstericisi dosya açıldığında 0'ıncı offset'tedir. Ancak okuma ve yazma yapıldığında okunan ya da yazılan miktar kadar otomatik ilerletilmektedir. 
    Dosya göstericisini belli bir konuma almak için lseek isimli POSIX fonksiyonu kullanılmaktadır. Bu fonksiyon da pek çok işletim 
    sisteminde doğrudan dosyayı konumlandıran sistem fonksiyonunu (Linux'ta sys_lseek) çağırmaktadır. lseek fonksiyonun genel kullanımı
    fseek standart C fonksiyonuna çok benzemektedir. Fonksiyonun prototipi şöyledir:

    #include <unistd.h>

    off_t lseek(int fd, off_t offset, int whence);

    Fonksiyonun birinci parametresi dosya göstericisi konumlandırılacak dosyayaya ilişkin dosya betimleyicisini belirtir. Dosya göstericisi 
    dosya nesnesinin (Linux'ta struct file) içerisinde tutulmaktadır. İkinci parametre konumlandırma offset'ini belirtir. off_t 
    <unistd.h> ve <sys/types.h> içerisinde işaretli bir tamsayı türü biçiminde typedef edilmiş olan bir tür ismidir. Üçüncü parametre konumlandırma 
    orijinini belirtmektedir. Bu üçüncü parametre 0, 1 ya da 2 olarak girilebilir. Tabii sayısal değer girmek yerine yine SEEK_SET (0), SEEK_CUR (1)
    ve SEEK_END (2) sembolik sabitlerini girebiliriz. Bu sembolik sabitler <unistd.h> ve <stdio.h> içerisinde de bildirilmiştir. 
    Fonksyon başarı durumunda konumlandırılan offset'e başarısızlık durumunda -1 değerine geri dönmektedir. 

    SEEK_SET konumlandırmanın dosyanın başından itibaren yapılacağını, SEEK_CUR konumlandırmanın o anda dosya göstericisinin gösterdiği 
    yerden itibaren yapılacağını ve SEEK_END de konumlandırmanın EOF durumundan itibaren yapılacağını belirtmektedir. En normalk durum 
    SEEK_SET orijininde ikinci parametrenin >= 0, SEEK_END orijininde <= 0 biçiminde girilmesidir. SEEK_CUR orijininde ikinxi 
    parametre pozitif ya da negatif girilebilir. Örneğin dosya göstericisini EOF durumuna şöyle konumlandırabiliriz:

    lseek(fd, 0, SEEK_END);

    Dosya sistemine de bağlı olarak UNIX7Linux istemleri dosya göstericisini EOF'un ötesine konumlandırmaya izin verebilmektedir. 
    Bu özel bir durumdur. Bu tüğr durumlarda dosyaya yazma yapıldığında "dosya delikleri (file holes)" oluşmaktadır. Dosya delikleri konusu ileride 
    ele alınacaktır. 

    Aslında dosya açarken O_APPEND modu atomik bir biçimde her write işleminden önce dosya göstericisini EOF durumuna çekmektedir. Bu nedenle 
    her yazılan dosyanın sonuna eklenmektedir. 

    Aşağıdaki örnekte "test.txt" O_WRONLY modunda açılmış ve dosya göstericisi EOF durumuna çekilerek dosyaya ekleme yapılmıştır. 

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
    char buf[] = "\nthis is a test";

    if ((fd = open("test.txt", O_WRONLY)) == -1)
        exit_sys("open");

    lseek(fd, 0, SEEK_END);

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