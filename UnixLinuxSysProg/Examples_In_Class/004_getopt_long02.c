/*--------------------------------------------------------------------------------------------------------------------------
    getopt_long fonksiyonunda struct option yapısındaki flag elemanına NULL adres yerine int bir nesnenin adresi geçirilirse
    bu durumda getopt_long bu uzun seçenek girildiğinde doğrudan yapının val elemanındaki değeri bu nesneye yerleştirir ve 0 ile geri
    döner. Böylece programcı isterse argümansız uzun seçenekleri switch içerisinde işlemeden doğrudan onun bayrağına set işlemi
    yapabilir. Ayrıca programlarda kısa seçeneklerin uzun seçenek eşdeğerleri de bulunabilmektedir. Bunu sağlamanın en kolay yolu
    uzun seçeneğe ilişkin struct option yapısındaki val elemanına kısa seçeneğe ilişkin karakter kodunu girmektir.
---------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    int result;
    int a_flag, b_flag, all_flag, length_flag, number_flag, err_flag;
    char *b_arg, *length_arg, *number_arg;
    struct option options[] = {
        {"all", no_argument, &all_flag, 1},
        {"length", required_argument, NULL, 'l'},
        {"number", optional_argument, NULL, 3},
        {0, 0, 0, 0},
    };

    a_flag = b_flag = all_flag = length_flag = number_flag = err_flag = 0;
    opterr = 0;
    while ((result = getopt_long(argc, argv, "ab:l:", options, NULL)) != -1)
    {
        switch (result)
        {
        case 'b':
            b_flag = 1;
            b_arg = optarg;
            break;
        case 1:
            all_flag = 1;
            break;
        case 'l':
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
