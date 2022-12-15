/* ----------------------------------------------------------------------------------------------------------
    Aşağıdaki girilen octal digitlerle dosyaların erişim haklarını değiştiren bir örnek verilmiştir.
    Bu örnekte doğrudan chmod fonksiyonunda bitmask değerler sayısal olarak kullanılmıştır.
    Bu durumun eski sistemlerde sorunlu olabileceğini bir kez daha vuruguluyoruz.
------------------------------------------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int check_mode(const char *mode_str);
void exit_sys(const char *msg);

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "too few parameters!...\n");
        exit(EXIT_FAILURE);
    }

    if (!check_mode(argv[1]))
    {
        fprintf(stderr, "Invalid mode: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    mode_t mode_val;
    sscanf(argv[1], "%o", &mode_val);

    for (size_t i = 2; i < argc; ++i)
    {
        if (chmod(argv[i], mode_val) == -1)
            fprintf(stderr, "Cannot change mode(%s) for %s\n", argv[1], argv[i]);
    }
}

int check_mode(const char *mode_str)
{
    if (strlen(mode_str) > 4)
        return 0;

    for (size_t i = 0; mode_str[i] != '\0'; ++i)
        if (mode_str[i] < '0' || mode_str[i] > '7')
            return 0;

    return 1;
}

void exit_sys(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
