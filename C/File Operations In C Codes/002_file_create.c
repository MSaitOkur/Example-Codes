#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main()
{
    char fileName[SIZE];
    printf("Enter the name of the file to create: ");
    scanf("%s", fileName);

    FILE *f;
    if ((f = fopen(fileName, "w")) == NULL)
    {
        fprintf(stderr, "File couldn't create!\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "File %s was created.\n", fileName);

    fclose(fileName);
}