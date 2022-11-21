#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int bytes_flag = 0, lines_flag = 0, verbose_flag = 0,
        help_flag = 0, version_flag = 0;

    char *bytes_arg, *lines_arg;

    const struct option options[] =
        {
            {"bytes", required_argument, NULL, 'c'},
            {"lines", required_argument, NULL, 'n'},
            {"verbose", no_argument, &verbose_flag, 'v'},
            {"help", no_argument, &help_flag, 1},
            {"version", no_argument, &version_flag, 2},
            {0, 0, 0, 0},
        };

    opterr = 0;
    int error_flag = 0;

    int opt_result;
    while ((opt_result = getopt_long(argc, argv, "c:n:v", options, NULL)) != -1)
    {
        switch (opt_result)
        {
        case 'c':
            bytes_flag = 1;
            bytes_arg = optarg;
            break;
        case 'n':
            lines_flag = 1;
            lines_arg = optarg;
            break;
        case '?':
            if (optopt == 'c')
                fprintf(stderr, "-c or --bytes options must have an argument!\n");
            else if (optopt == 'n')
                fprintf(stderr, "-n or --lines options must have an argument!\n");
            else if (optopt != 0)
                fprintf(stderr, "Invalid option used: -%c\n", optopt);
            else
                fprintf(stderr, "Invalid long option!\n");

            error_flag = 1;
        }
    }

    if (error_flag == 1)
        exit(EXIT_FAILURE);
}