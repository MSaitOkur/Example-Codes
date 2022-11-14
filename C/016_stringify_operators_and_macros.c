#include <stdio.h>

// This macro is dangereous because there is no function overloading in C
#define cmf_1(T) \
    T max(T x, T y) { return x > y ? x : y; }

// This macro is safe because this usage is not function declaration.
#define cmf_2(T) \
    T max_##T(T x, T y) { return x > y ? x : y; }

cmf_1(int);
/* cmf_1(double); // invalid */

cmf_2(int);
cmf_2(double); // valid

int main()
{
    printf("max(2,4) = %d\n", max(2, 4));
    printf("max_int(2,4) = %d\n", max_int(2, 4));
    printf("max_double(2.,4.) = %f\n", max_double(2., 4.));
}
