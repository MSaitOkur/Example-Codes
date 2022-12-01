/* If a special member function will be defaulted by compiler and if
 * there will be error because of compiler defaults the special member function,
 * compiler deletes this special member function.
 * This special member function will be implicitly declared deleted.
 *
 * But If a move ctor. or move assignment will be defaulted by compiler and if
 * there will be error because of compiler defaults the move ctor. or move assignment
 * compiler doesn't delete the function. Compiler assumes this function was never written.
 */

#include <iostream>
class member
{
public:
    member() = default;
    member(const member &)
    {
        std::cout << "copy ctor called";
    }

private:
    member(member &&);
};

class A
{
public:
    member mx;
};

int main()
{
    A ax;
    A ay = std::move(ax); // Valid (Copy Ctor)
    // There is no move ctor of class "A". Because of class "member" has private
    // move ctor. If compiler writes the move ctor. of "A", there will be error.
    // So compiler assumes there is no move ctor of "A".
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

class Myclass
{
public:
    Myclass() = default;
    Myclass(const Myclass &)
    {
        std::cout << "copy ctor called\n";
    }
    Myclass(Myclass &&)
    {
        std::cout << "move ctor called\n";
    }
};

void func(Myclass &&r)
{
    Myclass mx = std::move(r); // move ctor
}

void func(const Myclass &r)
{
    Myclass mx = r; // copy ctor
}

int main()
{
    Myclass m;

    func(m);         // copy ctor
    func(Myclass{}); // move ctor
}