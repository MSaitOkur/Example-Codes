#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

// default(bs=512): dd if=a.txt of=b.txt
// set block size:  dd if=a.txt of=b.txt bs=64
// set total bytes: dd if=a.txt of=b.txt bs=64 count=2
// byte conversion: dd if=a.txt of=b.txt bs=64 count=2 conv=ucase {ucase, lcase, excl}
//                  dd if=a.txt of=b.txt bs=64 count=2 conv=ucase,excl

// ex1: dd if=/dev/zero of=test.dat bs=512 count=2
// ex2: dd if=/dev/random of=test.dat bs=512 count=2

#define MAX_PATH_NAME 4096
#define MAX_BUFFER_SIZE 4096

void exit_sys(const char *msg);

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Wrong usage, at least 3 arguments must be entered!...\n");
        exit(EXIT_FAILURE);
    }

    int if_flag = 0, of_flag = 0, bs_flag = 0, count_flag = 0, conv_flag = 0;

    for (size_t i = 1; i < argc; ++i)
    {
        if (!strncmp(argv[i], "if=", 3))
            if_flag = i;
        else if (!strncmp(argv[i], "of=", 3))
            of_flag = i;
        else if (!strncmp(argv[i], "bs=", 3))
            bs_flag = i;
        else if (!strncmp(argv[i], "count=", 6))
            count_flag = i;
        else if (!strncmp(argv[i], "conv=", 5))
            conv_flag = i;
    }

    if (!if_flag || !of_flag)
    {
        fprintf(stderr, "input and output files must be entered!...\n");
        exit(EXIT_FAILURE);
    }

    int ucase_flag = 0, lcase_flag, excl_flag = 0;
    if (conv_flag)
    {
        char conv_string[32];
        strcpy(conv_string, argv[conv_flag] + 5);

        for (char *ptr = strtok(conv_string, ","); ptr; ptr = strtok(NULL, ","))
        {
            if (!strcmp(ptr, "ucase"))
                ucase_flag = 1;
            else if (!strcmp(ptr, "lcase"))
                lcase_flag = 1;
            else if (!strcmp(ptr, "excl"))
                excl_flag = 1;
            else
            {
                fprintf(stderr, "Wrong conversion!...\n");
                exit(EXIT_FAILURE);
            }
        }

        if (ucase_flag + lcase_flag + excl_flag == 0)
        {
            fprintf(stderr, "Wrong conversion!...\n");
            exit(EXIT_FAILURE);
        }
        else if (ucase_flag + lcase_flag > 1)
        {
            fprintf(stderr, "ucase and lcase cannot be combined!...\n");
            exit(EXIT_FAILURE);
        }
    }

    char input_file_name[MAX_PATH_NAME], output_file_name[MAX_PATH_NAME];
    strcpy(input_file_name, argv[if_flag] + 3);
    strcpy(output_file_name, argv[of_flag] + 3);

    int fi, fo;
    if ((fi = open(input_file_name, O_RDONLY)) == -1)
        exit_sys("ERR open(if)");

    if ((fo = open(output_file_name, O_WRONLY | O_CREAT | O_TRUNC | (excl_flag ? O_EXCL : 0),
                   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    {
        close(fi);
        exit_sys("ERR open(of)");
    }

    size_t block_size = bs_flag ? atoi(argv[bs_flag] + 3) : 512;
    size_t block_count = count_flag ? atoi(argv[count_flag] + 6) : 0;

    int read_result, write_result;
    char buf[MAX_BUFFER_SIZE];
    size_t block_count_cnt = 0;

    while ((read_result = read(fi, buf, block_size)) > 0)
    {
        if (ucase_flag || lcase_flag)
        {
            for (size_t i = 0; i < read_result; ++i)
                if (isalpha(buf[i]))
                    buf[i] = ucase_flag ? toupper(buf[i]) : tolower(buf[i]);
        }

        if ((write_result = write(fo, buf, read_result)) == -1)
            exit_sys("ERR write");
        else if (write_result != read_result)
        {
            fprintf(stderr, "ERR: Cannot write to %s\n", output_file_name);
            exit(EXIT_FAILURE);
        }

        if (block_count)
        {
            ++block_count_cnt;
            if (block_count_cnt == block_count)
                break;
        }
    }
    if (read_result == -1)
        exit_sys("ERR read");

    close(fi);
    close(fo);
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}