// This program checks the sign of an integer value.

#include <stdio.h>

int main()
{
    int x;
    printf("Enter an integer value: ");
    scanf("%d", &x);

    printf("sign(%d) = (%d)\n", x, (x > 0) - (x < 0));
}