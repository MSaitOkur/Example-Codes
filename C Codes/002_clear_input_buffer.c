// This program checks the accuracy of input

#include <stdio.h>

void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    int ival;
    int count = 0;

    while (1)
    {
        printf("[%d] Enter an integer value: ", ++count);
        int n = scanf("%d", &ival);

        if (n == 1)
            break;

        printf("\nWrong Input\n");
        clear_input_buffer();
    }

    printf("Correct input\n");
    printf("Input = %d\n", ival);
}
