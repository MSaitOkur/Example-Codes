#include "istack.h"
#include "mint.h"
#include <string>
#include "pimpl.h"

struct Myclass::pimpl
{
	Istack istack;
	Mint mint;
	std::string str;
};

Myclass::Myclass() : mp{new pimpl} {}

Myclass::~Myclass()
{
	delete mp;
}

void Myclass::Myfunc()
{
	mp->istack.push(12);
	mp->str.push_back('a');
	mp->mint += Mint{124};
}