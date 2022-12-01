/* MIL syntax is used to initialize the nonstatic
 * data members beginning the constructor.
 */

class Myclass
{
public:
    Myclass();
    Myclass(int a, int b);

private:
    int mx, my;
};

Myclass::Myclass() : mx(1023), my(412) {}
// Myclass::Myclass() : mx{1023}, my{412}{} // Modern C++

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* When the using of MIL syntax, it's better to initialize data members
 * as same order as declaration of them in the class. If it is not, there will be
 * no error but some of them might have garbage value.
 */

class Myclass
{
public:
    Myclass();

private:
    int ma, mb;
};
Myclass::Myclass() : mb(10), ma(mb / 3) {}
// Here is ma created first, then mb is created.
// Therefore when ma was created, mb has garbage value.

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Myclass
{
public:
    Myclass();

private:
    const int mx;
};

Myclass::Myclass() : mx(10)
{
    // Here is, mx is alive.
    mx = 125; // Invalid. This is not an initialization but assignment
    // So that const variables cannot be set after was created.
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
