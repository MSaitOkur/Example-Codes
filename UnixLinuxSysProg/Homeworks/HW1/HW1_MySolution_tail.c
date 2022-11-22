#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1000

char version_message[] = "Version 1.0\n";

char help_message[] = {
    "Usage: tail [OPTION]... [FILE]...\n"
    "Print the last 10 lines of each FILE to standard output.\n"
    "With more than one FILE, precede each with a header giving the file name.\n"
    "\n"
    "With no FILE, or when FILE is -, read standard input.\n"
    "\n"
    "Mandatory arguments to long options are mandatory for short options too.\n"
    "  -c, --bytes=[+]NUM       output the last NUM bytes; or use -c +NUM to\n"
    "                             output starting with byte NUM of each file\n"
    "  -f, --follow[={name|descriptor}]\n"
    "                           output appended data as the file grows;\n"
    "                             an absent option argument means 'descriptor'\n"
    "  -F                       same as --follow=name --retry\n"
    "  -n, --lines=[+]NUM       output the last NUM lines, instead of the last 10;\n"
    "                             or use -n +NUM to output starting with line NUM\n"
    "      --max-unchanged-stats=N\n"
    "                           with --follow=name, reopen a FILE which has not\n"
    "                             changed size after N (default 5) iterations\n"
    "                             to see if it has been unlinked or renamed\n"
    "                             (this is the usual case of rotated log files);\n"
    "                             with inotify, this option is rarely useful\n"
    "      --pid=PID            with -f, terminate after process ID, PID dies\n"
    "  -q, --quiet, --silent    never output headers giving file names\n"
    "      --retry              keep trying to open a file if it is inaccessible\n"
    "  -s, --sleep-interval=N   with -f, sleep for approximately N seconds\n"
    "                             (default 1.0) between iterations;\n"
    "                             with inotify and --pid=P, check process P at\n"
    "                             least once every N seconds\n"
    "  -v, --verbose            always output headers giving file names\n"
    "  -z, --zero-terminated    line delimiter is NUL, not newline\n"
    "      --help     display this help and exit\n"
    "      --version  output version information and exit\n"
    "\n"
    "NUM may have a multiplier suffix:\n"
    "b 512, kB 1000, K 1024, MB 1000*1000, M 1024*1024,\n"
    "GB 1000*1000*1000, G 1024*1024*1024, and so on for T, P, E, Z, Y.\n"
    "Binary prefixes can be used, too: KiB=K, MiB=M, and so on.\n"
    "\n"
    "GNU coreutils online help: <https://www.gnu.org/software/coreutils/>\n"
    "Full documentation <https://www.gnu.org/software/coreutils/tail>\n"
    "or available locally via: info '(coreutils) tail invocation'\n"};

int is_newline(int c)
{
    return c == '\n' ? 1 : 0;
}

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
        case 'v':
            verbose_flag = 1;
            break;
        case '?':
            if (optopt == 'c')
                fprintf(stderr, "ERR: -c or --bytes options must have an argument!\n");
            else if (optopt == 'n')
                fprintf(stderr, "ERR: -n or --lines options must have an argument!\n");
            else if (optopt != 0)
                fprintf(stderr, "ERR: Invalid option used: -%c\n", optopt);
            else
                fprintf(stderr, "ERR: Invalid long option!\n");

            error_flag = 1;
        }
    }

    if (error_flag == 1)
        exit(EXIT_FAILURE);

    if (help_flag)
    {
        fprintf(stdout, "%s", help_message);
        return 0;
    }
    else if (version_flag)
    {
        fprintf(stdout, "%s", version_message);
        return 0;
    }

    if (bytes_flag + lines_flag == 2)
    {
        fprintf(stderr, "ERR: \"-c/--bytes\" and \"-n/--lines\" cannot be used at the same time!\n");
        exit(EXIT_FAILURE);
    }

    if (bytes_flag)
    {
        long numofbytes = atoi(bytes_arg);
        if (argc - optind == 0)
        {
            if (verbose_flag)
                fprintf(stdout, "=======> Standart Input <=======\n");

            FILE *temp_file = tmpfile();

            int c;
            while ((c = fgetc(stdin)) != EOF)
                fputc(c, temp_file);

            fseek(temp_file, -numofbytes, SEEK_END);

            while ((c = fgetc(temp_file)) != EOF)
                fputc(c, stdout);

            fclose(temp_file);
        }
        else
        {
            for (size_t arg_index = optind; arg_index < argc; ++arg_index)
            {
                FILE *fsource;
                if ((fsource = fopen(argv[arg_index], "r")) == NULL)
                {
                    fprintf(stderr, "%s file couldn't open\n", argv[arg_index]);
                    continue;
                }

                if (argc - optind > 1 || verbose_flag)
                    fprintf(stdout, "==============> %s <==============\n", argv[arg_index]);

                fseek(fsource, -numofbytes, SEEK_END);
                int c;
                while ((c = fgetc(fsource)) != EOF)
                    fputc(c, stdout);

                if (argc - optind > 1)
                    fprintf(stdout, "\n\n");
            }
        }
    }
    else if (lines_flag)
    {
        long numoflines = atoi(lines_arg);
        if (argc - optind == 0)
        {
            if (verbose_flag)
                fprintf(stdout, "=======> Standart Input <=======\n");

            FILE *temp_file = tmpfile();
            int c;
            while ((c = fgetc(stdin)) != EOF)
                fputc(c, temp_file);

            fseek(temp_file, -1L, SEEK_END);

            // If the last character is '\n', ignore it.
            int cval = fgetc(temp_file);
            if (cval == '\n')
                fseek(temp_file, -2L, SEEK_END);
            else
                fseek(temp_file, -1L, SEEK_END);

            size_t new_line_cnt = 0;
            while (1)
            {
                int c;
                if (is_newline(c = fgetc(temp_file)))
                    if (++new_line_cnt == numoflines)
                        break;

                if (fseek(temp_file, -2L, SEEK_CUR))
                {
                    fseek(temp_file, -1L, SEEK_CUR);
                    break;
                }
            }

            char line_buffer[MAX_LINE_LENGTH + 1];
            for (size_t i = 0; i < numoflines; ++i)
                if (fgets(line_buffer, MAX_LINE_LENGTH, temp_file) == NULL)
                    break;
                else
                    fputs(line_buffer, stdout);

            fclose(temp_file);
        }
        else
        {
            for (size_t arg_index = optind; arg_index < argc; ++arg_index)
            {
                FILE *f;
                if ((f = fopen(argv[arg_index], "r")) == NULL)
                {
                    fprintf(stderr, "%s file couldn't open\n", argv[arg_index]);
                    continue;
                }

                if (argc - optind > 1 || verbose_flag)
                    fprintf(stdout, "==============> %s <==============\n", argv[arg_index]);

                fseek(f, -1L, SEEK_END);

                // If the last character is '\n', ignore it.
                int cval = fgetc(f);
                if (cval == '\n')
                    fseek(f, -2L, SEEK_END);
                else
                    fseek(f, -1L, SEEK_END);

                size_t new_line_cnt = 0;
                while (1)
                {
                    int c;
                    if (is_newline(c = fgetc(f)))
                        if (++new_line_cnt == numoflines)
                            break;

                    if (fseek(f, -2L, SEEK_CUR))
                    {
                        fseek(f, -1L, SEEK_CUR);
                        break;
                    }
                }

                char line_buffer[MAX_LINE_LENGTH + 1];
                for (size_t i = 0; i < numoflines; ++i)
                    if (fgets(line_buffer, MAX_LINE_LENGTH, f) == NULL)
                        break;
                    else
                        fputs(line_buffer, stdout);

                if (argc - optind > 1)
                    fprintf(stdout, "\n\n");
            }
        }
    }
    else if (lines_flag + bytes_flag == 0)
    {
        if (argc - optind == 0)
        {
            if (verbose_flag)
                fprintf(stdout, "=======> Standart Input <=======\n");

            FILE *temp_file = tmpfile();
            int c;
            while ((c = fgetc(stdin)) != EOF)
                fputc(c, temp_file);

            fseek(temp_file, -1L, SEEK_END);

            // If the last character is '\n', ignore it.
            int cval = fgetc(temp_file);
            if (cval == '\n')
                fseek(temp_file, -2L, SEEK_END);
            else
                fseek(temp_file, -1L, SEEK_END);

            size_t new_line_cnt = 0;
            while (1)
            {
                int c;
                if (is_newline(c = fgetc(temp_file)))
                    if (++new_line_cnt == 10)
                        break;

                if (fseek(temp_file, -2L, SEEK_CUR))
                {
                    fseek(temp_file, -1L, SEEK_CUR);
                    break;
                }
            }

            char line_buffer[MAX_LINE_LENGTH + 1];
            for (size_t i = 0; i < 10; ++i)
                if (fgets(line_buffer, MAX_LINE_LENGTH, temp_file) == NULL)
                    break;
                else
                    fputs(line_buffer, stdout);
        }
        else
        {
            for (size_t arg_index = optind; arg_index < argc; ++arg_index)
            {
                FILE *f;
                if ((f = fopen(argv[arg_index], "r")) == NULL)
                {
                    fprintf(stderr, "%s file couldn't open\n", argv[arg_index]);
                    continue;
                }

                if (argc - optind > 1 || verbose_flag)
                    fprintf(stdout, "==============> %s <==============\n", argv[arg_index]);

                fseek(f, -1L, SEEK_END);

                // If the last character is '\n', ignore it.
                int cval = fgetc(f);
                if (cval == '\n')
                    fseek(f, -2L, SEEK_END);
                else
                    fseek(f, -1L, SEEK_END);

                size_t new_line_cnt = 0;
                while (1)
                {
                    int c;
                    if (is_newline(c = fgetc(f)))
                        if (++new_line_cnt == 10)
                            break;

                    if (fseek(f, -2L, SEEK_CUR))
                    {
                        fseek(f, -1L, SEEK_CUR);
                        break;
                    }
                }

                char line_buffer[MAX_LINE_LENGTH + 1];
                for (size_t i = 0; i < 10; ++i)
                    if (fgets(line_buffer, MAX_LINE_LENGTH, f) == NULL)
                        break;
                    else
                        fputs(line_buffer, stdout);

                if (argc - optind > 1)
                    fprintf(stdout, "\n\n");
            }
        }
    }

    return 0;
}
