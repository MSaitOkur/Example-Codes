/*--------------------------------------------------------------------------------------------------------------------------
    UNIX/Linux sistemlerinde dosya kopyalama bir döngü içerisinde kaynak dosyadan hedef dosyaya blok blok okuma yazma işlemi ile
    yapılmaktadır. Ancak bazı UNIX türevi işletim sistemleri dosya kopyalama işlemi için sistem fonksiyonları da bulundurabilmektedir. 
    Örneğin Linux sistemlerinde copy_file_range isimli sistem fonksiyonı doğrudan disk üzerinde blok kopyalaması yoluyla dosya 
    kopyalamasını hiç user mode işlem yapmadan gerçekleştirebilmektedir. Ancak bu işlemin taşınabilir yolu yukarıda belirttiğimiz gibi 
    kaynaktan hedefe aktarım yapmaktır. Pekiyi bu kopyalama işleminde hangi büyüklükte bir tampon kullanılmalıdır? Tipik olarak dosya sistemindeki 
    blok uzunluğu bunun için tercih edilir. stat, fstat, lstat gibi fonksiyonlar bunu bize verirler. Blok uzunlukları 512'nin 
    katları biçimindedir. 

    Aşağıdaki örnekte blok kopyalaması yoluyla dosya kopyalaması yapılmıştır. 
---------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------------
    write çok çok seyrek de olsa başarılı olduğu halde talep edilen miktar kadar hedef dosyaya yazamayabilir. Örneğin diskin dolu 
    olması durumunda ya da bir sinyal oluşması durumunda write talep edilen miktar kadar yazma yapamayabilir. Bu tür durumları diğer
    durumlardan ayırmak için ayrı bir kontrol yapmak gerekebilir. 
---------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE     4096

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    char buf[BUFFER_SIZE];
    int fds, fdd;
    ssize_t size, result;

    if (argc != 3) {
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    if ((fds = open(argv[1], O_RDONLY)) == -1)
        exit_sys(argv[1]);

    if ((fdd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1)
        exit_sys(argv[2]);

    while ((result = read(fds, buf, BUFFER_SIZE)) > 0) {
        if ((size = write(fdd, buf, result)) == -1) 
            exit_sys("write");
        if (size != result) {
            fprintf(stderr, "cannot write file!..\n");
            exit(EXIT_FAILURE);
        }
    }

    if (result == -1)
        exit_sys("read");

    close(fds);
    close(fdd);
    
    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}
