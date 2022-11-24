#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// mycalc [option] op1 op2
// options:
// -a(no argument)   : add
// -m(no argument)   : multiply
// -d(no argument)   : divide
// -s(no argument)   : subtract
// -M(need argument) : output string
//
// mycalc -a 10 20 ---> 30
// mycalc -m 2 16  ---> 32
// mycalc -m 2 16 -M result ---> result: 32

int main(int argc, char **argv)
{
    opterr = 0;

    int a_flag = 0, m_flag = 0, d_flag = 0, s_flag = 0, M_flag = 0;
    char *M_arg;
    int error_flag = 0;

    int result;
    while ((result = getopt(argc, argv, "amdsM:")) != -1)
    {
        switch (result)
        {
        case 'a':
            a_flag = 1;
            break;
        case 'm':
            m_flag = 1;
            break;
        case 'd':
            d_flag = 1;
            break;
        case 's':
            s_flag = 1;
            break;
        case 'M':
            M_flag = 1;
            M_arg = optarg;
            break;
        case '?':
            if (optopt == 'M')
                fprintf(stderr, "-M option must have an argument!\n");
            else
                fprintf(stderr, "Invalid option: -%c\n", optopt);

            error_flag = 1;
        }
    }

    if (error_flag)
        exit(EXIT_FAILURE);

    if (a_flag + m_flag + d_flag + s_flag > 1)
    {
        fprintf(stderr, "Only one option must be specified!\n");
        exit(EXIT_FAILURE);
    }
    else if (a_flag + m_flag + d_flag + s_flag == 0)
    {
        fprintf(stderr, "At least one of -{amds} options must be specified!\n");
        exit(EXIT_FAILURE);
    }

    if (argc - optind != 2)
    {
        fprintf(stderr, "Two operand must be specified!\n");
        exit(EXIT_FAILURE);
    }

    double op1 = atof(argv[optind]), op2 = atof(argv[optind + 1]);
    double calc_result;

    if (a_flag)
        calc_result = op1 + op2;
    else if (m_flag)
        calc_result = op1 * op2;
    else if (d_flag)
        calc_result = op1 / op2;
    if (s_flag)
        calc_result = op1 - op2;

    if (M_flag)
        fprintf(stdout, "%s: %f\n", M_arg, calc_result);
    else
        fprintf(stdout, "%f\n", calc_result);
}