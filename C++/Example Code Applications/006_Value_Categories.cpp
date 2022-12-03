/* Value Categories of Expressions In C:
 *  - RValue Expression
 *  - LValue Expression
 *       - Modifiable Lvalue   : can be set
 *       - Unmodifiable Lvalue : cannot be set
 *
 *  - If you want to check an expression's value category,
 *    make the expression operand of &(address-of) operator.
 *      -- error    => Rvalue
 *      -- no error => Lvalue
 */

//===========================================================================
//===========================================================================

/* Value Categories of Expressions In Cpp:
 *  - Lvalue  : Left value (Has Identity, Not Movable)
 *  - Xvalue  : Expire value (Has Identity, Movable)
 *  - PRvalue : Pure Right value (Doesn't Have Identity, Movable)
 *
 * ================================
 *
 *  - GLvalue : Lvalue and Xvalue
 *  - Rvalue  : Xvalue and PRvalue
 *
 * ================================
 *
 *  - If a function has RValue Refference return value,
 *    value category of return of the function is X value.
 *
 *      int&& foo(); ==> return is XValue
 *
 * ================================
 */

/* ================================
 *  In C:
 *   => ++x : Rvalue Expression
 *   => x++ : Rvalue Expression
 *   => --x : Rvalue Expression
 *   => x-- : Rvalue Expression
 *
 * In C++:
 *   => ++x : Lvalue Expression
 *   => x++ : Rvalue Expression
 *   => --x : Lvalue Expression
 *   => x-- : Rvalue Expression
 *
 * ================================
 * In C:
 *   => ',' operator's right operand Rvalue ==> Rvalue
 *   => ',' operator's right operand Lvalue ==> Rvalue
 *
 *           int main()
 *           {
 *               int x = 10;
 *               int y = 45;
 *               (x, y) = 50; // Invalid
 *           }
 *
 * In C++:
 *   => ',' operator's right operand Rvalue ==> Rvalue
 *   => ',' operator's right operand Lvalue ==> Lvalue
 *
 *           int main()
 *           {
 *               int x = 10;
 *               int y = 45;
 *               (x, y) = 50; // Valid
 *           }
 *
 * ================================
 * In C:
 *   => Ternary operator's 2. and 3. operands Rvalue ==> Rvalue
 *   => Ternary operator's 2. and 3. operands Lvalue ==> Rvalue
 *
 *           int main()
 *           {
 *               int x = 20;
 *               int y = 231;
 *               int z = 1234;
 *               x > 5 ? y : z = 99; // Invalid
 *           }
 *
 * In C++:
 *   => Ternary operator's 2. and 3. operands Rvalue ==> Rvalue
 *   => Ternary operator's 2. and 3. operands Lvalue ==> Lvalue
 *
 *           int main()
 *           {
 *               int x = 20;
 *               int y = 231;
 *               int z = 1234;
 *               x > 5 ? y : z = 99; // Valid
 *           }
 *
 *  ================================
 * In C:
 *   => Assignment Operator's return ==> Rvalue
 *
 *           int main()
 *           {
 *              int a = 213124;
 *              (a = 20) = 100; // Invalid
 *           }
 *
 * In C++:
 *   => Assignment Operator's return ==> Lvalue
 *
 *           int main()
 *           {
 *              int a = 213124;
 *              (a = 20) = 100; // Valid
 *           }
 */

#include <iostream>

template <typename T>
struct ValCat
{
    static constexpr const char *p = "PR value";
};

template <typename T>
struct ValCat<T &>
{
    static constexpr const char *p = "L value";
};

template <typename T>
struct ValCat<T &&>
{
    static constexpr const char *p = "X value";
};

#define print_val_cat(expr) std::cout << "Value category of expr '" #expr "' is : " << ValCat<decltype((expr))>::p << '\n'

class Nec
{
};

Nec foo();
Nec &bar();
Nec &&baz();

int main()
{
    Nec x{};
    const Nec y{};

    print_val_cat(x);
    print_val_cat(y);
    print_val_cat(foo());
    print_val_cat(bar());
    print_val_cat(baz());
    print_val_cat(std::move(x));
    print_val_cat(std::move(y));

    print_val_cat("necati");
    print_val_cat(void());
    print_val_cat(nullptr);

    int ival{10};
    int *ptr{&ival};
    print_val_cat(ival + 5);
    print_val_cat(++ival);
    print_val_cat(ival++);
    print_val_cat(*ptr);
    print_val_cat(ptr[0]);
    print_val_cat(foo);
    print_val_cat(std::move(foo));
}

/*
    'x' is : L value
    'y' is : L value
    'foo()' is : PR value
    'bar()' is : L value
    'baz()' is : X value
    'std::move(x)' is : X value
    'std::move(y)' is : X value
    '"necati"' is : L value
    'void()' is : PR value
    'nullptr' is : PR value
    'ival + 5' is : PR value
    '++ival' is : L value
    'ival++' is : PR value
    '*ptr' is : L value
    'ptr[0]' is : L value
    'foo' is : L value
    'std::move(foo)' is : L value
*/

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

template <typename T>
struct ValCat
{
    static constexpr const char *p = "PR value";
};

template <typename T>
struct ValCat<T &>
{
    static constexpr const char *p = "L value";
};

template <typename T>
struct ValCat<T &&>
{
    static constexpr const char *p = "X value";
};

#define print_val_cat(expr) std::cout << "Value category of expr '" #expr "' is : " << ValCat<decltype((expr))>::p << '\n'

struct Nec
{
    int a, b;
};

Nec f1();
Nec &f2();
Nec &&f3();

int main()
{
    int x = 10;
    const int y = 20;
    int &r = x;
    int &&rr = x + 5;
    Nec nec;
    Nec *ptr = &nec;
    Nec &nr{nec};
    int a[10];

    print_val_cat(x);            
    print_val_cat(x + 5);         
    print_val_cat(&x);            
    print_val_cat(&y);            
    print_val_cat(y);            
    print_val_cat(++x);          
    print_val_cat(x++);           
    print_val_cat(--x);          
    print_val_cat(x--);           
    print_val_cat((x, y));       
    print_val_cat(x > 5 ? x : y);
    print_val_cat(x > 5 ? x : 7); 
    print_val_cat(x > y);         
    print_val_cat(x && y);        
    print_val_cat(+x);            
    print_val_cat(-x);            
    print_val_cat((double)x);    
    print_val_cat(f1());          
    print_val_cat(f2());         
    print_val_cat(f3());         
    print_val_cat(r);            
    print_val_cat(rr);           
    print_val_cat(nec);          
    print_val_cat(nec.a);        
    print_val_cat(ptr);          
    print_val_cat(*ptr);         
    print_val_cat(&ptr);          
    print_val_cat(ptr->a);       
    print_val_cat(&ptr->a);       
    print_val_cat(ptr + 1);       
    print_val_cat(a);            
    print_val_cat(*a);           
    print_val_cat(a + 3);         
    print_val_cat(a[4]);         
    print_val_cat(nr);           
    print_val_cat(nr.a);         
    print_val_cat(int());         
    print_val_cat(int{});         
    print_val_cat(Nec());         
    print_val_cat(Nec{});         
}