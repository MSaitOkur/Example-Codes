/*--------------------------------------------------------------------------------------------------------------------------
    getopt_long fonksiyonun kullanılmasına bir örnek. Bu örnekteki seçenekler şöyledir:

    -a: arümansız kısa seçenek
    -b: argümanlı kısa seçenek
    --all: argümansız uzun seçenek
    --length: argümanlı uzun seçenek
    --number: isteğe bağlı argümanlı uzun seçenek
---------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    int result;
    struct option options[] = {
        {"all", no_argument, NULL, 1},
        {"length", required_argument, NULL, 2},
        {"number", optional_argument, NULL, 3},
        {0, 0, 0, 0},
    };
    int a_flag, b_flag, all_flag, length_flag, number_flag, err_flag;
    char *b_arg, *length_arg, *number_arg;

    a_flag = b_flag = all_flag = length_flag = number_flag = err_flag = 0;
    opterr = 0;
    while ((result = getopt_long(argc, argv, "ab:", options, NULL)) != -1)
    {
        switch (result)
        {
        case 'a':
            a_flag = 1;
            break;
        case 'b':
            b_flag = 1;
            b_arg = optarg;
            break;
        case 1:
            all_flag = 1;
            break;
        case 2:
            length_flag = 1;
            length_arg = optarg;
            break;
        case 3:
            number_flag = 1;
            number_arg = optarg;
            break;
        case '?':
            if (optopt == 'b')
                fprintf(stderr, "-b option without argument!\n");
            else if (optopt == 2)
                fprintf(stderr, "--length option without argument!\n");
            else if (optopt != 0)
                fprintf(stderr, "invalid option: -%c\n", optopt);
            else
                fprintf(stderr, "invalid long option!\n");
            err_flag = 1;
        }
    }
    if (err_flag)
        exit(EXIT_FAILURE);

    if (a_flag)
        printf("-a option given\n");
    if (b_flag)
        printf("-b option given with argument \"%s\"\n", b_arg);
    if (all_flag)
        printf("--all option given\n");
    if (length_flag)
        printf("--length option given with argument \"%s\"\n", length_arg);
    if (number_flag)
        if (number_arg != NULL)
            printf("--number option given with argument \"%s\"\n", number_arg);
        else
            printf("--number option given without argument\n");

    if (optind != argc)
        printf("Arguments without options:\n");
    for (int i = optind; i < argc; ++i)
        puts(argv[i]);

    return 0;
}

/*

test girişi: ./sample --all --length 100 --number=300 -a ali veli selami
Çıktısı şöyledir:

-a option given
--all option given
--length option given with argument "100"
--number option given with argument "300"
Arguments without options:
ali
veli
selami

*/
