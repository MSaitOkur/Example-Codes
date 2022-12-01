// Default argument is not a runtime tool but a compile time tool.

// Default arguments can not be written on the function definition
// and function declaration at the same time. That why default arguments must be
// written on the function declaration.

void func(int a = 10, int b = 20, int c = 30);
void func(int a = 10, int b = 20, int c = 30) {} // error

int main() {}

//------------------------

#include <iostream>

void func(int a = 10, int b = 20, int c = 30);

int main()
{
    func(1, 2, 3);
    func(1, 2);
    func(1);
    func();
}

void func(int a, int b, int c)
{
    std::cout << "a = " << a << "b = " << b << "c = " << c << "\n";
    std::cout << "----------------------------------------------\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// The normal parameters cannot be used as a default argument for parameters.

void func(int x, int y = x); // Error

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// With redeclaration, more default argument can be added to function. But
// at the redeclaration, the parameters that have def. argument cannot be written
// again.

void func(int, int, int = 56);
// codes...
void func(int x, int y = 10, int z);
// Valid, 2. parameter has got default arg. in addition to first declaration.
// void func(int x, int y = 10, int z = 56); // Last state of func

//-------------------------

void func(int, int = 56);
// codes...
void func(int x, int = 56); // Invalid

//--------------------------------------------------------------------
//--------------------------------------------------------------------
