class Nec
{
public:
    friend void foo(Nec);
};

void foo(Nec) {} // correct usage

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Nec
{
public:
    friend void foo(Nec);
    friend void f1(Nec);
    friend void f2(Nec);
    void f3(Nec);
};

void foo(Nec) {} // Valid

friend void f1(Nec) {}
// Invalid ("friend" keyword mustn't be on both definition and declaration)

void Nec::f2(Nec) {}
// Invalid (f2 is not a member function, if f2 is a member function, it's error.)
// Classes cannot give friendship to their member functions

friend void Nec::f3(Nec) {}
// Invalid ("friend" keyword must be on the declaration and inside of the class)

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Nec
{
    void pfoo();

public:
    friend void ffun(Nec);

private:
    int mx;
};

Nec gn;

void gf(Nec p)
{
    Nec nx;
    nx.mx = 10; // access error (gf is not a member function or friend function)
    p.pfoo();   // access error (gf is not a member function or friend function)
    gn.pfoo();  // access error (gf is not a member function or friend function)
}

void ffun(Nec p)
{
    Nec nx;
    nx.mx = 10; // Valid
    p.pfoo();   // Valid
    gn.pfoo();  // Valid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Neco
{
public:
    friend void func(int);
    friend void foo(Neco);
};

int main()
{
    Neco n;
    func(213); // Error, Scope resolution operator is needed
    foo(n);    // Before C++11 Error, After C++11 valid. Argument Depended Lookup(ADL)
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------

class A
{
public:
    void Afoo(int);
};

class B
{
    void Bfoo(int);
};

class C;

class Neco
{
    friend void A::Afoo(int);
    friend void B::Bfoo(int); // Access Error, B::Bfoo is private
    friend void C::Cfoo(int); // Error, C is incomplete type

    int mx;
    void foo();
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Neco;

class Myclass
{
    void f1()
    {
        Neco nx; // error, At here Neco is incomplete type
        nx.foo();
    }
    void f2()
    {
        Neco nx; // error, At here Neco is incomplete type
        nx.foo();
    }
    void f3()
    {
        Neco nx; // error, At here Neco is incomplete type
        nx.foo();
    }
};

class Neco
{
    void foo();
    friend class Myclass;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Neco
{
    void foo();
    friend class Myclass;
};

class Myclass
{
    void f1()
    {
        Neco nx; // Valid
        nx.foo();
    }
    void f2()
    {
        Neco nx; // Valid
        nx.foo();
    }
    void f3()
    {
        Neco nx; // Valid
        nx.foo();
    }
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class A
{
    void fa();

public:
    friend class B;
};

class B
{
    void fb();
};

void A::fa()
{
    B{}.fb(); // invalid, A can't see B's private part
}

void B::fb()
{
    A{}.fa(); // Valid, B can see A's private part
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class A
{
    void fa();

public:
    friend class B;
};

class B
{
    void fb();
    friend class A;
};

void A::fa()
{
    B{}.fb(); // Valid (B can see A's private part)
}

void B::fb()
{
    A{}.fa(); // Valid (A can see B's private part)
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class A
{
    void fa();

public:
    friend class B;
};

class B
{
    void fb();
    friend class C;
};
class C
{
    void fc();
};

void A::fa()
{
    B{}.fb(); // Invalid (A can't see B's private part)
    C{}.fc(); // Invalid (A can't see C's private part)
}

void B::fb()
{
    A{}.fa(); // Valid (B can see A's private part)
    C{}.fc(); // Invalid (B can't see C's private part)
}

void C::fc()
{
    A{}.fa(); // Valid (C can't see A's private part)
    B{}.fb(); // Invalid (C can see B's private part)
}
