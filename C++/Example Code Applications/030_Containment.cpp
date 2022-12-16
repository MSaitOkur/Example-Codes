/* If a class has a class type nonstatic member object, the member object must be complete type.
 * But if the class type member object is pointer, reference or static member object, there is
 * no complete type condition.
 */

class Member;

struct Owner
{
    Member mx;        // Invalid, For this declaration Member must be complete type
    Member *mx;       // Valid
    Member &mx;       // Valid
    static Member my; // Valid, This is not definition, but declaration
};

//===================

#include <iostream>

class Member
{
    char str[16];
    double x, y;
};

class Owner
{
    Member mx;
    int x, y;
};

int main()
{
    std::cout << "sizeof(Member) = " << sizeof(Member) << "\n";
    std::cout << "sizeof(Owner) = " << sizeof(Owner) << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* A class has class type member object, but doesn't have membership of the member object's class,
 * the owner class cannot reach the private part the member object.
 *
 */

class Member
{
public:
    void foo();

private:
    void pfunc();
};

class Owner
{
public:
    void f()
    {
        mx.foo();   // Valid
        mx.pfunc(); // Invalid
    }

private:
    Member mx;
};

//===========================

class Member
{
    friend class Owner;

public:
    void foo();

private:
    void pfunc();
};

class Owner
{
public:
    void f()
    {
        mx.foo();   // Valid
        mx.pfunc(); // Valid, Owner has friendship of Member class
    }

private:
    Member mx;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
class Member
{
public:
    Member() { std::cout << "Member default ctor\n"; }
};
class Neco
{
    Member mx;
};
int main()
{
    Neco nec; // Valid
    // Compiler has written the default constructor of Neco class.
    // And compiler has initialized the all member objects as default in other word
    // compiler called the default ctor of the Member class
}

// ===================================================

#include <iostream>

class Member
{
};

class Neco
{
public:
    Member mx;
};

int main()
{
    Neco nec; // Invalid
    // Call to a deleted function
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* If member classs' default ctor is user declared, the responsibility of initialization of the member
 * objects belong to programmer.  If programmer forgets to initialize these member objects, compiler
 * will call default constructor for these member objects.
 */

#include <iostream>

class Member
{
public:
    Member()
    {
        std::cout << "Member default ctor\n";
    }
};

class Neco
{
    Member mx;

public:
    Neco()
    {
        std::cout << "Neco default ctor\n";
    }
};

int main()
{
    Neco nec;
}

//==================================

#include <iostream>
class Member
{
public:
    Member(int)
    {
        std::cout << "Member(int) ctor\n";
    }
};
class Neco
{
    Member mx{12};  // Valid
    Member my = 12; // Valid
    Member mz(12);  // Invalid, Most Vexing Parse

public:
    Neco()
    {
        std::cout << "Neco default ctor\n";
    }
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
