/* If a function has parameter which is class type and the argument of the function
 * is PRvalue expr. aka temporary object, compiler doesn't create the temporary object
 * and the parameter of the function seperately.
 * Compiler just creates the parameter with the value of temp. object.
 *
 * This type of copy elision:
 *  Before C++17: Compiler optimization (Class has got to have copy and move ctors. Otherwise error)
 *  After  C++17: Guaranteed(Mandatory) Copy Elision (Even Class doesn't have the copy and move members)
 */

#include <iostream>

class Myclass
{
public:
    Myclass() { std::cout << "default ctor called this : " << this << "\n"; }
    // Myclass(const Myclass &other) { std::cout << "copy ctor called this : " << this << "\n"; }
    // Myclass(Myclass &&other) { std::cout << "move ctor called this : " << this << "\n"; };
    Myclass(const Myclass &other) = delete;
    Myclass(Myclass &&other) = delete;
    ~Myclass() { std::cout << "destructor called this : " << this << "\n"; }
};

void func(Myclass x) // x's def. ctor. was called
{
    std::cout << "func called\n";
}

int main()
{
    std::cout << "main basladi\n";
    func(Myclass{}); // Invalid before C++17, Valid after C++17
    std::cout << "main devam ediyor\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* RVO(Return Value Optimization)
 * If a function's return value type is class type and the returned value of the function
 * is PRvalue expr. aka temporary object, compiler doesn't create the temporary object
 * and the return  value of the function seperately.
 * Compiler just creates the return value with the value of temp. object.
 *
 * This type of copy elision:
 *  Before C++17: Compiler optimization (Class has got to have copy and move ctors. Otherwise error)
 *  After  C++17: Guaranteed(Mandatory) Copy Elision (Even Class doesn't have the copy and move members)
 */

#include <iostream>

class Myclass
{
public:
    Myclass() { std::cout << "default ctor called this : " << this << "\n"; }
    // Myclass(const Myclass &other) { std::cout << "copy ctor called this : " << this << "\n"; }
    // Myclass(Myclass &&other) { std::cout << "move ctor called this : " << this << "\n"; };
    Myclass(const Myclass &other) = delete;
    Myclass(Myclass &&other) = delete;
    ~Myclass() { std::cout << "destructor called this : " << this << "\n"; }
};

Myclass func()
{
    std::cout << "func called\n";
    return Myclass{};
}

int main()
{
    std::cout << "main basladi\n";

    Myclass m = func(); // m's default ctor. was called
    // Invalid before C++17, Valid after C++17

    std::cout << "main devam ediyor\n";
}

/* NRVO(Named Return Value Optimization)
 * If a function has a local class type object which has automatic storage duration
 * in its body and if the return type of the function is as same type as this class object
 * and if the function will return the value of this local object, compiler doesn't destroy
 * the local object and doesn't create a new object aka won't call the copy ctor. for the returned value.
 * It assumes life of the local object continues and uses the value of the local object.
 *
 * This type of copy elision is a branch of RVO.
 * NRVO is not a mandatory copy elision and class has got to have copy and move ctors.
 * Otherwise it will be syntax error.
 */

#include <iostream>
class Myclass
{
public:
    Myclass() { std::cout << "default ctor called this : " << this << "\n"; }
    Myclass(const Myclass &other) { std::cout << "copy ctor called this : " << this << "\n"; }
    Myclass(Myclass &&other) { std::cout << "move ctor called this : " << this << "\n"; };
    ~Myclass() { std::cout << "destructor called this : " << this << "\n"; }
};

Myclass foo()
{
    std::cout << "foo called\n";
    Myclass mx;
    std::cout << "address of the object in foo: " << &mx << "\n";
    return mx;
}

int main()
{
    std::cout << "main started.\n";

    Myclass mx = foo();
    std::cout << "address of the object in main: " << &mx << "\n";

    std::cout << "main continues.\n";
}

//-------------------

#include <iostream>

class Myclass
{
public:
    Myclass() { std::cout << "default ctor called this : " << this << "\n"; }
    Myclass(const Myclass &other) = delete;
    Myclass(Myclass &&other) = delete;
    ~Myclass() { std::cout << "destructor called this : " << this << "\n"; }
};

Myclass foo()
{
    std::cout << "foo called\n";
    Myclass mx;
    std::cout << "address of the object in foo: " << &mx << "\n";
    return mx;
}

int main()
{
    std::cout << "main started.\n";

    Myclass mx = foo(); // error: use of deleted function ‘Myclass::Myclass(const Myclass&)’
    std::cout << "address of the object in main: " << &mx << "\n";

    std::cout << "main continues.\n";
}