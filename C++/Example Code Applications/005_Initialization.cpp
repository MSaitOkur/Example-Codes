struct A
{
};

struct B
{
    B(A);
};

int gx;  // Zero Init. (gx = 0)
bool gb; // Zero Init. (gb = false)
int *gp; // Zero Init. (gb = nullptr)

int main()
{
    int x;  // Default Init. (x = garbage value)
    bool b; // Default Init. (b = garbage value)
    int *p; // Default Init. (p = garbage value)

    static int sx;  // Zero Init. (sx = 0)
    static bool sb; // Zero Init. (sb = false)
    static int *sp; // Zero Init. (sp = nullptr)

    int x1 = 20;   // Copy Init.
    int x2 = 20.1; // Copy Init. (Narrowing Conversion is valid)

    int y1(15);   // Direct Init.
    int y2(12.6); // Direct Init. (Narrowing Conversion is valid)

    int z1{30};   // Uniform(Brace) Init.
    int z2{30.8}; // Uniform(Brace) Init.(Narrowing Conversion in not valid)

    B bx1(A()); // Not Direct Init. - bx1 is a function (Most Vexing Parse)
    B bx2{A()}; // Uniform(Brace - Value) Init. - bx2's type is "B"

    int ival1(); // Not Direct Init. - ival is function (Most Vexing Parse)
    int ival2{}; // Value Init. - ival2's type is "int"

    int ival{};  // a's value is 0         ====> Value Init.
    int *ptr{};  // ptr's value is nullptr ====> Value Init.
    bool bval{}; // bval's value is false  ====> Value Init.
}