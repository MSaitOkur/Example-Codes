#include <iostream>
#include <bitset>

int main()
{
    int x;
    std::cout << "Bir tamsayi giriniz: ";
    std::cin >> x;

    std::cout << std::bitset<32>(x) << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <bitset>

int main()
{
    std::size_t x;
    std::cout << "Bir tamsayi giriniz: ";
    std::cin >> x;
    std::bitset<32> bx(x);

    std::cout << std::boolalpha;

    std::cout << "bx = " << bx << '\n';
    std::cout << "bx.any() = " << bx.any() << '\n';   // En az 1 bit set mi?
    std::cout << "bx.none() = " << bx.none() << '\n'; // Butun bitler 0 mi?
    std::cout << "bx.all() = " << bx.all() << '\n';   // Butun bitler 1 mi?
    std::cout << "bx.count() = " << bx.count() << " bit set\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <bitset>

int main()
{
    std::size_t x;
    std::cout << "Bir tamsayi giriniz: ";
    std::cin >> x;
    std::bitset<32> bx(x);

    std::cout << std::boolalpha;

    std::cout << "bx = " << bx << '\n';

    bx.set(9); // 9. bit set edildi

    std::cout << "bx = " << bx << '\n';

    bx.set(); // butun bitler set edildi

    std::cout << "bx = " << bx << '\n';

    bx.reset(9); // 9. bit 0 oldu

    std::cout << "bx = " << bx << '\n';

    bx.reset(); // butun bitler 0 oldu

    std::cout << "bx = " << bx << '\n';

    bx.flip(9); // 9. bit flip edildi, toggle

    std::cout << "bx = " << bx << '\n';
    
    bx.flip(); // Butun bitler flip edildi, toggle
    
    std::cout << "bx = " << bx << '\n';
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <bitset>

int main()
{
    std::size_t x;
    std::cout << "Bir tamsayi giriniz: ";
    std::cin >> x;
    std::bitset<32> bx(x);

    std::cout << "bx = " << bx << '\n';

    if (bx.test(5))
        std::cout << "5. basamaktaki bit set\n";
    else
        std::cout << "5. basamaktaki bit not set\n";

    if (bx[5])
        std::cout << "5. basamaktaki bit set\n";
    else
        std::cout << "5. basamaktaki bit not set\n";

    bx[5].flip();

    if (bx[5])
        std::cout << "5. basamaktaki bit set\n";
    else
        std::cout << "5. basamaktaki bit not set\n";

    bx[5] = bx[2]; // valid
    bx[5] = true;  // valid
    bx[5] = 1;     // valid
    bx.set(5);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <bitset>
#include <set>

int main()
{
    std::set<std::bitset<16>> myset;

    myset.insert(34); // Bitset sinifinin < operatoru yok
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
