#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    opterr = 0;
    int a_flag = 0, b_flag = 0, c_flag = 0, d_flag = 0, e_flag = 0;
    int error_flag = 0;
    char *c_arg, *e_arg;
    int result;
    while ((result = getopt(argc, argv, "abc:de:")) != -1)
    {
        switch (result)
        {
        case 'a':
            a_flag = 1;
            break;
        case 'b':
            b_flag = 1;
            break;
        case 'c':
            c_flag = 1;
            c_arg = optarg;
            break;
        case 'd':
            d_flag = 1;
            break;
        case 'e':
            e_flag = 1;
            e_arg = optarg;
            break;
        case '?':
            if (optopt == 'c' || optopt == 'e')
                fprintf(stderr, "-%c option must have an argument!\n", optopt);
            else
                fprintf(stderr, "Invalid option: %c\n", optopt);

            error_flag = 1;
        }
    }

    if (error_flag)
        exit(EXIT_FAILURE);

    if (a_flag)
        fprintf(stdout, "-a option was used\n");
    if (b_flag)
        fprintf(stdout, "-b option was used\n");
    if (c_flag)
        fprintf(stdout, "-c option was used, argument: \"%s\"\n", c_arg);
    if (d_flag)
        fprintf(stdout, "-d option was used\n");
    if (e_flag)
        fprintf(stdout, "-e option was used, argument: \"%s\"\n", e_arg);

    if (optind != argc)
    {
        fprintf(stdout, "Optionless arguments: \n");
        for (size_t i = optind; i < argc; ++i)
            puts(argv[i]);
    }
}