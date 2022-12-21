#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

int walkdir(const char *path, int (*proc)(const char *fname, const struct stat *, int));

static int walkdir_recur(
    const char *path,
    int indent_level,
    int (*proc)(const char *filename, const struct stat *fileinfo, int indent_level));

int disp(const char *filename, const struct stat *fileinfo, int indent_level);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Wrong number of arguments!...\n");
        exit(EXIT_FAILURE);
    }

    int result;
    /* Tum dizini recursive olarak dolas ve dizindeki tum dosyalari display et. */
    if ((result = walkdir(argv[1], disp)) == -1)
    {
        fprintf(stderr, "function terminates problematically!\n");
        exit(EXIT_FAILURE);
    }

    if (result != 0)
        printf("function terminates prematurely with %d code\n", result);
    else
        printf("function terminates normally!..\n");

    return 0;
}

int walkdir(
    const char *path,
    int (*proc)(const char *filename, const struct stat *fileinfo, int indent_level))
{
    /* Her girilen dizin cwd yi degistirecek.
     * Bastan onu alip sonda tekrar ayni degere set etmek iyi bir yontem. */
    char cwd[PATH_MAX];
    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        perror("getcwd");
        return -1;
    }

    /* Kademeli dolasan ve proc ile ekrana yazdiran recursive fonksiyon */
    int result = walkdir_recur(path, 0, proc);

    if (chdir(cwd) == -1)
    {
        perror("chdir");
        return -1;
    }

    return result;
}

int walkdir_recur(
    const char *path,
    int indent_level,
    int (*proc)(const char *fname, const struct stat *, int))
{
    int result = 0;

    /* Fonksiyon cagrildiginda ilgili dizine ait tum dosyalari dolasabilmek icin
     * ilk once dizin acilir. Sonrasinda bu dizin handle'si ile dolasim yapilacaktir.
     */
    DIR *dir;
    if ((dir = opendir(path)) == NULL)
    {
        fprintf(stderr, "Cannot open directory: %s\n", path);
        return -1;
        /* Burada goto EXIT; yapilmamasinin sebebi daha dizinin acilmada basarisiz olunmasidir. */
    }

    /* Bu fonksiyon her cagirildiginda dizin relative(goreceli) oldugu icin 
     * problem olmamasi adina cwd her dizin icin set edilir.
     */
    if ((result = chdir(path)) == -1)
    {
        fprintf(stderr, "CWD cannot change to %s!...\n", path);
        goto EXIT;
    }

    struct dirent *de;
    while (errno = 0, (de = readdir(dir)) != NULL)
    {
        // . ve .. dizinleri bu dolasimda pas gecilmek istendi.
        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
            continue;

        /* Bazen dosyalarin kendisi sembolik link dosyasi olabilir. Bu durumda
         * stat linki izleyecegi icin lstat sembolik link dosyasini gecmeyecegi icin
         * butun dosyalarin bilgilerini elde edebilmek icin daha iyi bir secenektir. */
        struct stat finfo;
        if ((result = lstat(de->d_name, &finfo)) == -1)
        {
            fprintf(stderr, "Cannot get stat info: %s\n", de->d_name);
            continue;
        }

        /* Dosyaya ait bilgiler icin islem yapilmak uzere callback fonk. 
         * olan proc fonksiyonu cagrilir. */
        if ((result = proc(de->d_name, &finfo, indent_level)) != 0)
            goto EXIT;

        if (S_ISDIR(finfo.st_mode))
        {
            /* Eger dosya bir dizin dosyasi ise bu durumda recursive cagri ile icine girilir. */
            result = walkdir_recur(de->d_name, indent_level + 1, proc);

            /* Recursive cagri sonrasinda icine girilen dizinden cikilmasi icin
             * .. dizini ile cwd tekrar set edilir. */
            if ((result = chdir("..")) == -1)
            {
                fprintf(stderr, "CWD cannot change to %s!...\n", "..");
                goto EXIT;
            }

            /* Basarisizlik durumunda hata degeri ile cikis yapilir. */
            if (result != 0)
                goto EXIT;
        }
    }

    if (errno)
        fprintf(stderr, "Cannot read directory info: %s\n", path);

    /* Herhangi bir hata durumunda dizinden cikis yapilmadan 
     * once dizin handle'si kapatilir. */
EXIT:
    closedir(dir);
    return result;
}

int disp(const char *fname, const struct stat *finfo, int indent_level)
{
    fprintf(stdout, "%*s%s\n", indent_level * 4, "", fname);

    if (!strcmp(fname, "test"))
        return 1;

    return 0;
}