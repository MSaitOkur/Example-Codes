// Equality of floating numbers shouldn't be compared with == operator.
// Because for == operator, all of the bits of the operands should be same.
#include <stdio.h>

int main()
{
    double dval = 0.;
    for(size_t i = 0; i < 10; ++i)
        dval += .1;
    
    if(dval == 1.)
        printf("yes\n");
    else    
        printf("no, but val = %f\n", dval);
}
