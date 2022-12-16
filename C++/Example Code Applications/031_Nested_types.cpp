/* The name lookup of the names which is used in class definition is different than the
 * name lookup of the member functions.
 *  - The member function's name lookup is enclosed of the whole class definitin. The place of definitions or
 *    declarations don't matter.
 *  - But other than the member functions if a name used in a class definition, the name will be looked up
 *    places before where it used in class definition. If it couldn't be found, then the places before the class
 *    will be checked for name lookup.
 *    - If it couldn't be found there will be error.
 */

class Myclass
{
    Word wy; // Invalid
    typedef int Word;
    Word wx; // Valid
};

// =========================

typedef double Word;

class Myclass
{
    Word wy; // Valid, this Word type was defined to double. This is the global Word (::Word)
    typedef int Word;
    Word wx; // Valid. This Word type was defined to int. This is the local Word (Myclass::Word)
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* If a nested type is used inside of inline defined member function, the name lookup will be
 * same as the member function which means the name first will be looked up in the scope of member function then,
 * in the whole class definition.
 */

class Myclass
{
    void func()
    {
        Nested nx;  // Valid
        Myint ival; // Valid
    }

    typedef int Myint;

    class Nested
    {
    };
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* If a class is a nested type of another class,
 *  - Enclosing class cannot reach the private part of nested class without friend declaration.
 *  - But nested class can reach and use the private part of enclosing class without friend declaration.
 */

class Myclass
{
public:
    class Nested
    {
        void nfoo();
    };

    void necfunc()
    {
        Nested mynested;
        mynested.nfoo(); // Invalid.
        // Enclosing class cannot reach the private part of nested class
        // without friend declaration
    }
};

// ===================================================

class Myclass
{
public:
    class Nested
    {
        friend class Myclass;
        void nfoo();
    };

    void necfunc()
    {
        Nested mynested;
        mynested.nfoo(); // Valid but attention to friend declaration
    }
};

// ===================================================

class Myclass
{
public:
    class Nested
    {
        void nfoo()
        {
            Myclass::f();         // Valid
            auto sz = sizeof(mx); // Valid
        }
    };

private:
    static void f();
    int mx;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* If a private nested type will be used to create an object with its name, there will be an error.
 * But if it will be used to create an object without its name which means type deduction(auto), there
 * will be no error.
 */

class Myclass
{
private:
    class Nested
    {
    };

public:
    Nested func();
};

int main()
{
    Myclass m;
    Myclass::Nested x = m.func(); // Invalid
    auto y = m.func();            // Valid but nonsense
}
