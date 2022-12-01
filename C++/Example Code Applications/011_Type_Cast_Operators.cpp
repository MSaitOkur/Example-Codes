// The best type conversion is the one that is never done.

/*
 *  static_cast: This is used to make conversion between static tpyes.
    ▪   Conversions between arithmetic types
        •   int to double
        •   char to int
        •   . . .
    ▪   Conversions between arithmetic types and enum types
    ▪   Conversions between enum types
    ▪   void* to T*

 *  const_cast
    ▪   CV qualified types
    ▪   Conversions about constness or volatileness of an object.

 *  reinterpret_cast
    ▪   To pretend an object is from another type.
    ▪       - For example an object from int* type is like an array from char*.

 *  dynamic_cast
    ▪   It is related to inheritance(kalıtım)
*/

// If a type cast is made by wrong type cast operator, it'll be compile time error.

int main()
{
    const unsigned int uval{};
    char *p1 = reinterpret_cast<char *>(const_cast<unsigned int *>(&uval)); // Valid
    char *p2 = const_cast<char *>(reinterpret_cast<const char *>(&uval));   // Valid
    char *p3 = static_cast<char *>(&uval);                                  // Invalid
    char *p2 = const_cast<char *>(&uval);                                   // Invalid
    char *p2 = reinterpret_cast<char *>(&uval);                             // Invalid
}