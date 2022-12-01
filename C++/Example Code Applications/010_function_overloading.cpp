// There is no function overloading in C but in C++.

// Function Signature: Info about parameter number and parameter types.

// For the function overloading to be usable
//  - The overloaded functions' signatures must be different.
//  - The overloaded functions must be in the same scope.

void foo1(int);
void foo1(const int); // valid (redeclaration)
// ----------------------
void foo2(int *p);
void foo2(int *const p); // valid (redeclaration)
// ----------------------
void foo3(int, int);
int foo3(int, int); // Invalid, (If the signatures same, returns must be same)
// ----------------------
void foo4(int);
int foo4(int, int); // Valid. (If the signatures different, returns can be different)
// ----------------------
void foo5(int *);
void foo5(const int *); // Valid (const overloading)
// ----------------------
void foo6(int &);
void foo6(const int &); // Valid (const overloading)
                        // ----------------------

//=============================================================
//=======Function Overload Resolution==========================

/*
 1- First compiler list all the candidate overloaded funtions.
    If there is no candidate function, it'll be error.

 2- Compiler seperates if the candidate functions are legal or not. The criteria of legality is
    "If the function would be alone, would the function call be legal?".
        - If the legal functions pass this point, these functions will be viable.
        - If there is no viable func. ==> error
        - If there are more than one viable func. compiler goes to 3. step.

 3- At this point compiler searches the best match from viable functions.
    The searching will be 3 steps. Priority of the steps ise from higher to lower.
    Priority: 3_1 > 3_2 > 3_3

    3_1 - Standart Conversion: The data loss is not an important criteria.
          Priority : Exact Match > Promotion > Conversion
            # Exact Match
                * Same Type
                * Lvalue to PRvalue Transformation
                * Const Conversion(T to const T)
                * Array to Pointer Conversion
                * Function to Pointer Conversion
            # Promotion
                * Integral Promotion(char to int)
                * float to double
            # Conversion
                * If the all remained viable funtions are in conversion status, it'll be ambiguity.

    3_2 - User Defined Conversion:
            # If there is no viable function in the status of standart conversion
              compiler checks the user defined conversion.
                * Conversion Constructor
                * Typecast Operator Functions
                * If the all remained viable funtions are in user defined conversion status,
                  it'll be ambiguity.

    3_3 - Variadic Conversion:
            # This point is the least priority point.
            # Compiler checks this category at last.
            # If there is no viable function or more than one function at this point,
              it'll be error.
*/

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// If one of the overloaded functions has def. argument, the ambiguity is possible.

void func1(int);
void func1(int, int = 102);

int main()
{
    func1(12);      // error (ambiguity)
    func1(12, 123); // Valid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// If overloaded functions has call by value and const reference relation,
// the ambiguity is possible.

void func2(int);
void func2(const int &);

int main()
{
    int x = 5623;
    func2(x); // error(ambiguity)
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// If the overloaded functions are const overload and
// if the function called with const pointer, the priority is on the const one.

void func3(int *p);       // 1
void func3(const int *p); // 2

void func4(int &p);       // 3
void func4(const int &p); // 4

int main()
{
    int x = 123;
    const int y = 667;

    func3(&x); // 1
    func3(&y); // 2

    func4(x); // 3
    func4(y); // 4
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// The Rvalue reference(T&&) has higher priority than const Lvalue reference(const T&).

void func5(int &);       // 1
void func5(const int &); // 2
void func5(int &&);      // 3

int main()
{
    int x = 5623;
    const int y = x;

    func5(x);     // gecerli 1
    func5(y);     // gecerli 2
    func5(4356);  // gecerli 3
    func5(x + 2); // gecerli 3
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// There is high possibility of ambiguity between T&& and T.

void func6(int &&);
void func6(int);

int main()
{
    int x = 5623;

    func6(4356); // invalid (ambiguity)
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

void func7(double *); // 1
void func7(int);      // 2

int main()
{
    func7(nullptr); // valid (1)
    func7(0);       // valid (2)
    func7(NULL);    // invalid (ambiguity)
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// Deleted functions can be added function overlead resolution set.
// Alse a deleted function can be choosed to call from overloaded functions.
// A call to deleted function is syntax error.

void func8(int) = delete;

int main()
{
    func8(2); // error
}

//---------------------

void func9(int) = delete;
void func9(double) = delete;
void func9(char) = delete;
void func9(float);

int main()
{
    func9(4356); // error
}

/*
    Eğer overload edilmiş fonksiyonlar birden fazla parametreye sahipse
    argümanlardan en az biri için ilgili parametre değişkenine dönüşümün kalitesi daha iyi olacak,
    ancak kalan argümanlar için ilgili parametre değişkenlerine dönüşümün kalitesi
    daha kötü olmayacak yani argümanlardaki dönüşümlerde en az bir tane dönüşümde üstün olup
    diğerlerinde de en az eşit olmalıdır. Bu koşul sağlanmazsa sentaks hatasıdır.
*/