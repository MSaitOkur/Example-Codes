/*--------------------------------------------------------------------------------------------------------------------------
    Aşağıdaki örnekte eski POSIX standartları da dikkate alınarak mode bilgisi 
    S_IXXX sembolik sabitlerinin bit düzeyinde OR'lanması ile oluşturulmuştur.
---------------------------------------------------------------------------------------------------------------------------*/

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

    mode_t modes[] = {S_IXOTH, S_IWOTH, S_IROTH, S_IXGRP, S_IWGRP, S_IRGRP,
                      S_IXUSR, S_IWUSR, S_IRUSR, S_ISVTX, S_ISGID, S_ISUID};

    mode_t mode_val;
    sscanf(argv[1], "%o", &mode_val);

    mode_t mode = 0;
    for (size_t i = 0; i < 12; ++i)
        if (mode_val & (1 << i))
            mode |= modes[i];

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