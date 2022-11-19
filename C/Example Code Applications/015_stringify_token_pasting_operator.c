#include <stdio.h>

#define str(s) #s
#define int_print(val) printf(#val " = %d\n", val)
#define uni(x, y) x##y

int main()
{
    int x = 213;
    int y = 1254;
    int_print(x);
    int_print(y);
    int_print(x + y);

    int counter = 0;
    int_print(counter);
    ++uni(coun, ter);
    int_print(counter);
}
