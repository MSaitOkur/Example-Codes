#include<iostream>

// immediately invoked lambda expr.
void f(int a = []{static int b = 1; return b++;}()) 
{
    std::cout << a;
}

int main()
{
    f();
    f();
}
