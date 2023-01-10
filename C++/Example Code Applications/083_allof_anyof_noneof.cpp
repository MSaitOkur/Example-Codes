#include <iostream>
#include <algorithm>

int main()
{
    int a[]{1, 2, 3, 4, 23, 23, 54, 5, 3, 23, 2, 3, 78, 9, 5};

    auto is_even = [](const auto &r)
    { return r % 2 == 0; };

    // all_of: range icindeki butun ogeler cift ise
    std::cout << std::boolalpha << std::all_of(std::begin(a), std::end(a), is_even) << "\n";

    // any_of: range icindeki ogelerden en az birisi cift ise
    std::cout << std::boolalpha << std::any_of(std::begin(a), std::end(a), is_even) << "\n";

    // none_of: range icindeki ogelerden hicbirisi cift degilse
    std::cout << std::boolalpha << std::none_of(std::begin(a), std::end(a), is_even) << "\n";
}