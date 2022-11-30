int ival = 1;         // external linkage
const int cival = 2;  // internal linkage
static int sval = 34; // internal linkage

namespace{
    // internal linkage
}

// If you want to add c codes
extern "C"
{
    // C codes here
    // More than 1 line
}

extern "C" // just 1 line C code here

int main()
{
}