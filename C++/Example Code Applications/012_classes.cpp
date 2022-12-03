// ###### NAME LOOKUP IN THE CLASSES

/* - Access control is the last check for the member
 *   functions and data members of the classes. For the function calls of a member function:
 *      First  -> Name lookup.
 *      Second -> Function Overload Resolution
 *      Last   -> Access Control
 *
 * - For the name lookup in a member function:
 *      First  -> Function Scope
 *      Second -> Class Scope
 *
 * - If the first checkpoint for the name lookup is wanted to be in class scope:
 *      - this pointer can be used
 *      - :: operator can be used
 */
//--------------------------------------------------------------------
//--------------------------------------------------------------------

// ###### MEMBER FUNCTIONS AND CONST SEMANTICS

class Data
{
public:
    void foo();        // regular member function
    void func() const; // const member function
private:
    int a;
    mutable int b;
    static int c;
};

void Data::foo()
{
    this->a = 2;  // valid (foo is not const mem. func.)
    this->b = 20; // valid (foo is not const mem. func.)
    this->c = 20; // valid (foo is not const mem. func.)
}
void Data::func() const
{
    this->a = 2;  // invalid (func is const mem. func. and a is not mutable)
    this->b = 20; // valid (func is const mem. func. but b is mutable)
    this->c = 20; // valid (func is const mem. func. but b is mutable)
}

int main()
{
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class
{
public:
    void foo();       // const overloading (not redeclaration)
    void foo() const; // const overloading (not redeclaration)
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Data
{
public:
    void foo();
    void cfoo() const;
    void func();
    void cfunc() const;
};

void Data::func()
{
    this->foo();  // valid
    this->cfoo(); // valid
}

void Data::cfunc() const
{
    this->foo();  // invalid (const mem. func. can't call nonconst mem. func.)
    this->cfoo(); // valid
}

int main() {}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Data
{
public:
    void foo();
    void cfoo() const;
    void func();
    void cfunc() const;
};

int main()
{
    Data d;
    const Data cd;

    d.foo();  // valid
    d.cfoo(); // valid

    cd.foo();  // invalid (const class object can't call nonconst mem. func.)
    cd.cfoo(); // valid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// If a nonconst class object calls an its const overloaded member function,
// nonconst member function has higher priority.

class Data
{
public:
    void foo();       // 1
    void foo() const; // 2
};

int main()
{
    Data d;
    const Data cd;

    d.foo();  // 1
    cd.foo(); // 2
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
