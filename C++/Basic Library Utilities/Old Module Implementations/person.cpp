#include "person.h"
#include <cstdlib>
#include <cstring>
#include<iostream> 

Person::Person(int id, const char *p) : m_id{id} 
{
    mpa = static_cast<char*>(std::malloc(std::strlen(p) + 1));
    if(!mpa){
        std::cerr <<  "Bellek yetersiz!...\n";
        std::exit(EXIT_FAILURE);
    }
    
    std::cout << m_id << " numarali kisi icin ayrilan bellek blogu adresi :" << static_cast<void *>(mpa) << "\n";

    std::strcpy(mpa, p);
}

Person::Person(const Person& other) : m_id{other.m_id}
{
    mpa = static_cast<char *>(std::malloc(std::strlen(other.mpa) + 1));

    if(!mpa){
        std::cerr << "Bellek yetersiz!...\n";
        std::exit(EXIT_FAILURE);
    }

    std::cout << "copy ctor icinde elde edilen bellek blogu adresi :" << static_cast<void *>(mpa) << "\n";
    std::strcpy(mpa, other.mpa);
}

Person::Person(Person&& other) : m_id{other.m_id}, mpa{other.mpa}
{
    other.mpa = nullptr;
}


Person& Person::operator=(const Person& other)
{
    if(this == &other) // Self Assignment Check
        return *this;
    
    std::free(mpa);

    m_id = other.m_id;
    mpa = static_cast<char *>(std::malloc(std::strlen(other.mpa) + 1));
    if(!mpa){
        std::cerr << "Bellek yetersiz!...\n";
        std::exit(EXIT_FAILURE);
    }

    std::strcpy(mpa, other.mpa);
    
    return *this;
}

Person& Person::operator=(Person&& other)
{
    if(this == &other) // Self Assignment Check
        return *this;

    std::free(mpa);
    m_id = other.m_id;
    mpa = other.mpa;
    other.mpa = nullptr;

    return *this;
}


Person::~Person()
{
    if(mpa)
        std::cout << m_id << " numarali kisi icin geri verilen bellek blogu adresi :" << static_cast<void *>(mpa) << "\n";
        std::free(mpa);
}

void Person::print()const
{
    std::cout << "id no : " << m_id << "\n";
    std::cout << "id    : " << mpa << "\n";
}

Person& Person::deep_copy(const Person& other)
{
    m_id = other.m_id;
    
    mpa = static_cast<char *>(std::malloc(std::strlen(other.mpa) + 1));
    if(!mpa){
        std::cerr << "Bellek yetersiz!...\n";
        std::exit(EXIT_FAILURE);
    }

    std::strcpy(mpa, other.mpa);
    
    return *this;
}

void Person::release_resources()
{
    std::free(mpa);
}

