#include <stdio.h>
#include <stdlib.h>

// <fileCopy> <filesource> <destfile>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "usage: <fileCopy> <filesource> <destfile>\n");
        exit(EXIT_FAILURE);
    }

    FILE *fsource;
    // if ((fsource = fopen(argv[1], "r")) == NULL)
    if ((fsource = fopen(argv[1], "rb")) == NULL)
    {
        fprintf(stderr, "Couldn't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    FILE *fdest;
    // if ((fdest = fopen(argv[2], "w")) == NULL)
    if ((fdest = fopen(argv[2], "wb")) == NULL)
    {
        fprintf(stderr, "Couldn't create %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    int c;
    size_t byte_count = 0;
    while ((c = fgetc(fsource)) != EOF)
    {
        fputc(c, fdest);
        ++byte_count;
    }

    fclose(fsource);
    fclose(fdest);

    printf("The %s file that has %zu byte was copied to %s file\n", argv[1], byte_count, argv[2]);
}