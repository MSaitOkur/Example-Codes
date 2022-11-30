
int main()
{
    //========================
    //========================

    int ival1 = 10;
    // int ar1[ival1]; // invalid (ival1 is not constant expr.)

    const int ival2 = ival1;
    // int ar2[ival2]; // invalid (ival2's initializer is not constant expr.)

    const int ival3 = 1;
    int ar3[ival3]; // valid, (ival3's initializer is constant expr.)

    // constexpr int ival4 = ival1; // invalid (ival4's initializer must be constant expr.)
    // constexpr int ival5 = ival2; // invalid (ival5's initializer must be constant expr.)
    constexpr int ival6 = ival3; // valid (ival6's initializer is constant expr.)

    // constexpr int ival7; // invalid (constexpr variables must have initializer)

    //========================
    //========================

    int ival7 = 43;
    const int *pival1 = &ival7;
    // *pival1 = 2352; // invalid (*pival1 is not a modifiable lvalue)
    pival1 = &ival1; // valid

    int *const pival2 = &ival7;
    *pival2 = 35; // valid
    // pival2 = &ival1; // invalid (pival2 is not a modifiable lvalue)

    const int *const pival3 = &ival7;
    // *pival3 = 35;    // invalid (*pival3 is not a modifiable lvalue)
    // pival3 = &ival1; // invalid (pival3 is not a modifiable lvalue)

    const int ival8 = 35;
    // int *pival4 = &ival8;       // invalid (type "const int *" cannot be used to initialize type "int *")
    // int *const pival5 = &ival8; // invalid (type "const int *" cannot be used to initialize type "int *const")
    const int *pival5 = &ival8; // valid

    int ival9 = 3;
    // constexpr int *pival6 = &ival9;       // invalid (Type of pival6 -> "int *const")
    // constexpr const int *pival7 = &ival9; // invalid (Type of pival7 -> "const int *const")
    // pival6 and pival7 are invalid. Because &ival9 is automatic storage duration.

    static int ival10 = 3;
    constexpr int *pival8 = &ival10;       // valid
    constexpr const int *pival9 = &ival10; // valid
    // pival6 and pival7 are valid. Because &ival10 are static storage duration.

    /*constexpr Type* val==> Type*const val*/

    int val = 214;
    // constexpr int *cptr = &val;     // invalid
    constexpr int *cptr2 = nullptr; // valid

    //========================
    //========================
}