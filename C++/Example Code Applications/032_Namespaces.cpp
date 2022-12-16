/* A namespace only can be declared inside of global namespace or another namespace.
 * There is nothing such local namespace.
 */

namespace MyNameSpace
{
    //...
}

// ===================================================

namespace n
{
    int x = 24;
    double x = 325.; // Invalid

}

// ===================================================

int x = 125; // ::x

namespace n1
{
    double x = 1532; // Valid, n1::x
}

namespace n2
{
    char x = 'A'; // Valid, n2::x
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

namespace MyNamespace
{
    class Myclass
    {
    public:
        int x;
        int y;
        double z;
        static int sx;
    };

    int x = 12;

    void func();

    Myclass m;

}

class Neco
{
public:
    int x;
    int y;
    double z;
    static int sx;
};

int a = 3412;

int main()
{
    MyNamespace::x = 1254;
    MyNamespace::func();
    MyNamespace::m.x = 45674;
    MyNamespace::Myclass::sx = 567;

    Neco::sx = 125;
    ::a = 1325;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* A name within a namespace can be used without using scope resolution operator(::) in three ways.
 *  - using declaration
 *  - using namespace directive
 *  - Argument Dependent Lookup (ADL)
 */

//======================= using declaration ====================================
//======================= using declaration ====================================
//======================= using declaration ====================================

/* It can be made with "using" keyword.
 * This declaration has a scope.
 * The declared object can be used in the scope of using declaration.
 * In the scope of using declaration, the declared object can be used without '::' operator.
 */

namespace Nec
{
    int x, y, z;
    class Myclass
    {
    };
}

int a = x; // Invalid. There is no global x, Nec::x is invisible at this point

using Nec::x; // From this declaration Nec::x can be used without namespace

int main()
{
    x = 2; // Valid, Nec::x
}

//================

namespace Nec
{
    int x, y, z;
    class Myclass
    {
    };
}

int a = x; // Invalid. There is no global x, Nec::x is invisible at this point

void f1()
{
    using Nec::x; // From this declaration to end of the f1 function scope
                  // Nec::x can be used without namespace
    x = 15;       // Valid, Nec::x = 15
}

int main()
{
    x = 2; // Invalid. There is no x, Nec::x is invisible at this point
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* A name which is declared to a scope with using declaration, will be as declared as in this scope.
 * In other words, it will be treated like defined in this scope. Therefore in this scope, it cannot be
 * another object with same name.
 */

namespace Nec
{
    int x, y, z;
    class Myclass
    {
    };
};

void f1()
{
    using Nec::x;
    int x = 1234; // Invalid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

namespace Nec
{
    int x, y, z;
    class Myclass
    {
    };
}

using Nec::x, Nec::y, Nec::z; // Before C++17 invalid

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* A namespace name cannot be used with using declaration. */

namespace Nec
{
    int x, y, z;

    class Myclass
    {
    };

    namespace can
    {
        int m;
    }
}

using Nec::can; // Invalid

//======================= using namespace directive ====================================
//======================= using namespace directive ====================================
//======================= using namespace directive ====================================

// Bildirimin yapıldığı scope’da bildirilen isim alanının içindeki isimler sanki o namespace’ler
// yokmuş gibi görünür hale gelirler.

/* In a scope which has a using namespace directive, the names in the namespace with
 * using namespace directive can be used without namespace name which means like there is no namespace.
 */

namespace Nec
{
    int x, y, z;
}

int m = y; // Invalid, there is no global y, Nec::y is invisible at this point

using namespace Nec;

int a = x; // Valid, Nec::x

void f1()
{
    z = 1254; // Valid, Nec::z
}
int main()
{
    y = 23; // Valid, Nec::y
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* There are some nuance between using declaration and using namespace directive.
 *  1- The names used with using declaration will be injected at the scope.
 *     But the names used within the namespaces with using namespace directive,
 *     won't be injected to the scope. These names just become visible.
 *      - This means the namespace will stay at same place. Even if a using namespace directive
 *        was made in a scope, an object can be created with same name which is the object in the namespace.
 */

#include <iostream>

namespace Nec
{
    int x = 5, y, z;
}

x = 15; // error, Nec::x is invisible

int main()
{
    // the names in the namespace Nec, are invisible.

    using namespace Nec; // After this directive, the names in the namespace Nec, will be visible.

    int x = 324; // local x

    std::cout << "x = " << x << '\n'; // local x, 324
}

//=========================

#include <iostream>

namespace Nec
{
    int x = 5, y = 20, z;
}

// x = 15; // error, Nec::x is invisible

int main()
{
    using namespace Nec;

    int a = x; // Valid, (int a = Nec::x;)
    int b = Nec::x;

    x = 521; // (Nec::x = 521)

    int y = 324; // local y

    std::cout << "x = " << x << '\n'; // Nec::x
    std::cout << "y = " << y << '\n'; // local y

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';

    int x = 12; // local x

    std::cout << "x = " << x << '\n'; // local x
}

//=========================

namespace Nec
{
    int x, y, z;
}

void f1()
{
    using namespace Nec;
    x = 20;      // Valid, (Nec::x = 20;)
    int x = 125; // Valid, but also Nec::x is visible.
}

void f2()
{
    using Nec::x;
    int x = 2135; // Invalid, there shouldn't be x other than Nec::x,
                  // because Nec::x was injected to this scope
}

void f3()
{
    int x = 1;
    using Nec::x; // Invalid, there is a local x, now this directive is invalid.
                  // 2 same names cannot be in the same scope.
}

//=====================

namespace Nec
{
    int x = 5, y, z;
}

using namespace Nec;

int x = 125; // ::x

int main()
{
    x = 5; // Syntax Error (Ambiguity)

    Nec::x = 132; // Valid
    ::x = 36;     // Valid
}

//======================= Argument Dependent Lookup (ADL) ====================================
//======================= Argument Dependent Lookup (ADL) ====================================
//======================= Argument Dependent Lookup (ADL) ====================================

/* In a function call, if an argument is a name which is declared in a namespace,
 * this called funciton's name also will be looked up in this argument's namespace.
 */

#include <iostream>
#include <vector>
namespace nec
{
    class Data
    {
    };
    enum class color
    {
        white,
        black
    };
    void func(Data);
    void foo(color);
    void bar(std::vector<Data> vec);
}
int main()
{
    nec::Data mydata;
    std::vector<nec::Data> myvec;

    func(mydata);           // Valid ADL
    foo(nec::color::black); // Valid ADL
    bar(myvec);             // Valid ADL
}

//==========================

#include <iostream>

int main()
{
    // std::cout << "Merhaba Dunya\n";
    // std::operator<<(std::cout, "Merhaba Dunya\n");
    operator<<(std::cout, "Merhaba Dunya\n");

    // The third function call at the above, will be valid due to ADL.
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* The reason of existence of ADL in C++ is global functions.
 * Because in Java or C#, there are no global functions so no need to use ADL.
 * Therefore there is no ADL in Java or C#.
 */

#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> ivec;
    auto a1 = std::count(std::begin(ivec), std::end(ivec), 6); // Valid
    auto a2 = count(begin(ivec), end(ivec), 6);                // Valid
}

//==========================

namespace nec
{
    class Data
    {
    };
    void func(Data);
}
void func(nec::Data);

int main()
{
    nec::Data mydata;
    func(mydata); // Invalid, ambiguity
    // ::func and nec::func are both viable
}

//==========================

namespace nec
{
    class Data
    {
    };
    void func(Data);
}

void func(nec::Data);

int main()
{
    void func(nec::Data);
    nec::Data mydata;
    func(mydata); // Valid, local func
}

//======================= inline namespaces ====================================
//======================= inline namespaces ====================================
//======================= inline namespaces ====================================

/* The names which declared in the inline namespaces are visible for the enclosing namespaces.
 * These names are accessible without using scope resolution operator.
 * Inline namespaces are better tool than using namespace directives.
 */

inline namespace A
{
    inline namespace B
    {
        inline namespace C
        {
            int x = 213;
        }
    }
}

int main()
{
    x = 1;          // Valid
    A::x = 2;       // Valid
    B::x = 5;       // Valid
    C::x = 214;     // Valid
    A::B::x = 3;    // Valid
    B::C::x = 24;   // Valid
    A::B::C::x = 4; // Valid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* Inline namespaces are very useful tool for versioning the projects. */

#define OLD_VERSION
namespace Proj
{
#ifdef OLD_VERSION
    inline
#endif
        namespace Ver1
    {
        class Myclass
        {
        };
    }
#ifdef NEW_VERSION
    inline
#endif
        namespace Ver2
    {
        class Myclass
        {
        };
    }
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

namespace N
{
    class Data
    {
    };
    namespace Nested
    {
        void func(N::Data) {}
    }
    using namespace Nested;
}

int main()
{
    N::Data mydata;
    func(mydata); // Invalid (ADL doesn't work) (func is undefined at this point)
}

//======================

namespace N
{
    class Data
    {
    };
    inline namespace Nested
    {
        void func(N::Data);
    }
}

int main()
{
    N::Data mydata;
    func(mydata); // Valid, (ADL works with using inline namespace)
}

//======================= NAMESPACE ALIAS ====================================
//======================= NAMESPACE ALIAS ====================================
//======================= NAMESPACE ALIAS ====================================

/* Sometimes in the big projects, there might be numerous nested namespaces.
 * For this situations, to reach the most nested namespace, '::' operator must be used.
 * But this is a big problem to easiness of readability and writeability.
 * Namespace alias is used to solve this problem. This tool makes the code very easy to read and write.
 */

namespace Project
{
    namespace Nested1
    {
        namespace Nested2
        {
            namespace Nested3
            {
                int x;
            }
        }
    }
}

int main()
{
    namespace most_nested = Project::Nested1::Nested2::Nested3;

    Project::Nested1::Nested2::Nested3::x = 312;
    most_nested::x = 1352;
}

