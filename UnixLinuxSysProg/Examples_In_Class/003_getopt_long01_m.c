#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    opterr = 0;

    struct option options[] =
        {
            {"all", no_argument, NULL, 1},
            {"length", required_argument, NULL, 2},
            {"number", optional_argument, NULL, 3},
            {0, 0, 0, 0},
        };

    int a_flag = 0, b_flag = 0, all_flag = 0, length_flag = 0, number_flag = 0;
    char *b_arg, *length_arg, *number_arg = NULL;
    int error_flag = 0;

    int result;
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
                fprintf(stderr, "ERR: -b option must have an argument!\n");
            else if (optopt == 2)
                fprintf(stderr, "ERR: --length option must have an argument!\n");
            else if (optopt != 0)
                fprintf(stderr, "ERR: Invalid short option used: -%c\n", optopt);
            else
                fprintf(stderr, "ERR: Invalid long option used\n");

            error_flag = 1;
        }
    }

    if (error_flag)
        exit(EXIT_FAILURE);

    if (a_flag)
        fprintf(stdout, "-a option used.\n");
    if (b_flag)
        fprintf(stdout, "-b option used with argument: \"%s\"\n", b_arg);
    if (all_flag)
        fprintf(stdout, "--all option used.\n");
    if (length_flag)
        fprintf(stdout, "--length option used with argument: \"%s\"\n", length_arg);
    if (number_flag)
    {
        if (number_arg)
            fprintf(stdout, "--number option used with argument: \"%s\"\n", number_arg);
        else
            fprintf(stdout, "--number option used without argument.\n");
    }

    if (optind != argc)
        fprintf(stdout, "Arguments without option: \n");
    for (size_t i = optind; i < argc; ++i)
        fprintf(stdout, "%s\n", argv[i]);
}