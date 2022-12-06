// SINCE C++17

/* Mentality is as same as inline functions.
 * If a global variable is defined with "inline" keyword in a header file
 * and the definition of inline variable is same as token-by-token all header files,
 * the ODR will be remain fairly.
 * 
 * If a static data member of class is defined with "inline" keyword inside of class
 * and the definition of inline variable is same as token-by-token all header files,
 * the ODR will be remain fairly.
 *
 * Static data members which defined with "constexpr" are implicitly inline.
 */

// Myclass.h
inline int i = 23523; // This is definition

class Myclass
{
public:
    inline static int mx = 13; // This is definition

    constexpr static int a[]{1, 2, 3, 4, 5}; // This is definition

    const static int ival = 20; // This is declaration.
    // Linker still needs the definition of the ival.
    // Otherwise it will be linker error
};

