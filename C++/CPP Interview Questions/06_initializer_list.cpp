#include <iostream>
#include <vector>

int foo()
{
    std::cout << "foo";
    return 0;
}
int bar()
{
    std::cout << "bar";
    return 0;
}

void h(std::vector<int>) {}

int main()
{
    h({foo(), bar()});
}

// burada ilk deger veren ifade initializer_list
// ilk deger veren ifadede fonksiyonlarin cagrilmasi imp. defined degildir.
// elemanlarin sirasina goredir.