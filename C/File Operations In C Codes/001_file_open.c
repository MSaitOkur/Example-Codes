#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main()
{
    char fileName[SIZE];
    printf("Enter the name of the file to open: ");
    scanf("%s", fileName);

    FILE *f;
    if ((f = fopen(fileName, "r")) == NULL)
    {
        fprintf(stderr, "File couldn't find!\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "File %s was opened.\n", fileName);

    fclose(fileName);
}