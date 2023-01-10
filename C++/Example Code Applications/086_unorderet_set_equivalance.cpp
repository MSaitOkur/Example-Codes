#include <iostream>
#include <unordered_set>
#include "date.hpp"

class Data
{
};

class Data2
{
};
bool operator==(const Data2 &d1, const Data2 &d2)
{
    return rand() % 2;
}

template <>
struct std::hash<Data>
{
    std::size_t operator()(const Data &d) const { return 1; }
};

template <>
struct std::hash<Data2>
{
    std::size_t operator()(const Data2 &d) const { return 2; }
};

int main()
{
    std::unordered_set<Data, std::hash<Data>> dataset;
    // dataset.insert(Data{}); // error, equal_to icin operator== fonksiyonu yok

    std::unordered_set<Data2> dataset2;
    dataset2.insert(Data2{}); // Gecerli
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <unordered_set>
#include "date.hpp"

class Data
{
    bool operator==(const Data &d) const
    {
        return rand() % 2;
    }
};

template <>
struct std::hash<Data>
{
    std::size_t operator()(const Data &d) const { return 1; }
};

struct DataEqual
{
    bool operator()(const Data &d1, const Data &d2) const { return rand() % 2; }
};

int main()
{
    std::unordered_set<Data, std::hash<Data>, DataEqual> dataset;
    dataset.insert(Data{});
}