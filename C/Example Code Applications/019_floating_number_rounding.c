#include <stdio.h>

#define round(dval)  ((dval) - (int)(dval) >= 0.5 ? (int)(dval) + 1 : (int)(dval))

int main()
{
    double dval;
    printf("Enter a floating number in this range [-5 5]: ");
    scanf("%lf", &dval);

    printf("dval = %f\n", dval);

    int ival = round(dval);

    printf("ival = %d\n", ival);
}