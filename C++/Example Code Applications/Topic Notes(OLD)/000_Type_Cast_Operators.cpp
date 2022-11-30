/*
 *  static_cast: Statik tür dönüşümleri için kullanılır. 
    ▪   Aritmetik türler arasındaki dönüşümler
        •   int to double
        •   char to int
        •   . . .
    ▪   enum türleri ile aritmetik türler arasındaki ve enum türlerinin kendi aralarındaki dönüşümler
    ▪   void* to T*

 *  const_cast
    ▪   CV qualified types
    ▪   Bir nesnenin constluğu yada volatile'lığı üzerinde yapılan tür dönüşümleri

 *  reinterpret_cast
    ▪   Belirli bir türden nesneye başka bir türdenmiş gibi muamele etmektir.
    ▪   Mesela int* türünden bir nesne char* türünden bir dizi gibi kullanılması

 *  dynamic_cast
    ▪   C dilinde olan bir araç değil. C++'ta inheritance(kalıtım) ile ilgili bir araç
*/