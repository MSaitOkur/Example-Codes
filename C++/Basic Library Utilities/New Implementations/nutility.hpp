#ifndef NUTILITY_HPP
#define NUTILITY_HPP

#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <forward_list>
#include <ratio>
#include <chrono>

class Irand
{
public:
	Irand() = default;
	Irand(int min, int max) : m_dist{min, max} {}
	int operator()();

private:
	std::uniform_int_distribution<int> m_dist;
};

class Drand
{
public:
	Drand() = default;
	Drand(double dmin, double dmax) : m_dist{dmin, dmax} {}
	double operator()();

private:
	std::uniform_real_distribution<double> m_dist;
};

// Necati Hoca==============================================================

void my_terminate();
std::string rname();   // random
std::string rfname();  // random
std::string rtown();   // random
std::string rperson(); // random
std::ostream &sl(std::ostream &os);

bool isprime(int val);

// Benim kodlar==============================================================

//========================
//========================

// void randomize()
// {
// 	srand(static_cast<unsigned>(time(nullptr)));
// }

inline std::chrono::steady_clock::rep randomize()
{
	return std::chrono::steady_clock::now().time_since_epoch().count();
}
//========================
//========================

inline std::mt19937 &my_engine()
{
	static std::mt19937 eng{std::random_device{}()};
	return eng;
}

//========================
//========================

std::string &remove_duplicates(std::string &s);
std::string remove_chars(const std::string &source, const std::string scars);
std::string trim(const std::string &source);
std::string opposite_case(const std::string &s);
//--------------------------------------------------
//--------------------------------------------------
constexpr int ndigit(int val)
{
	if (val == 0)
		return 1;

	int digit_count = 0;

	while (val != 0)
	{
		val /= 10;
		++digit_count;
	}

	return digit_count;
}
//--------------------------------------------------
//--------------------------------------------------
template <typename C, typename F>
void fc(C &c, size_t n, F frand) // FILL CONTAINER
{
	while (c.size() < n)
		c.insert(c.end(), frand());
}
//--------------------------------------------------
//--------------------------------------------------
template <typename T, typename F>
void fc(std::forward_list<T> &c, size_t n, F frand) // FILL CONTAINER
{
	while (n--)
		c.insert_after(c.before_begin(), frand());
}
//--------------------------------------------------
//--------------------------------------------------
template <typename C>
void pc(const C &c, const char *p = " ", std::ostream &os = std::cout) // PRINT CONTAINER
{
	for (const auto &elem : c)
		os << elem << p;
	os << sl;
}
//--------------------------------------------------
//--------------------------------------------------

template <typename InIter>
void pr(InIter beg, InIter end, const char *p = " ", std::ostream &os = std::cout) // PRINT RANGE
{
	while (beg != end)
	{
		os << *beg++ << p;
	}
	os << sl;
}

//--------------------------------------------------
//--------------------------------------------------

template <typename C, typename F>
void fcs(C &c, size_t n, F func) // FILL CONTAINER SORTED
{
	std::set<typename C::value_type> s;
	while (s.size() != n)
		s.insert(func());
	c.assign(s.begin(), s.end());
}

//--------------------------------------------------
//--------------------------------------------------

template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &t)
{
	return os << "[" << t.first << "    " << t.second << "]";
}

//--------------------------------------------------
//--------------------------------------------------

std::string get_str_from_file(const std::string &filename);
std::vector<std::string> get_dictionary(const std::string &fname);

//--------------------------------------------------
//--------------------------------------------------

template <intmax_t x, intmax_t y>
std::ostream &operator<<(std::ostream &os, std::ratio<x, y> r)
{
	return os << r.num << " / " << r.den;
}

//--------------------------------------------------
//--------------------------------------------------

class de
{
public:
	constexpr de(long long x) : mx{x} {}
	friend std::ostream &operator<<(std::ostream &os, de x)
	{
		auto s = std::to_string(x.mx);
		if (s[0] == '-')
		{
			os << "-";
			s.erase(0, 1);
		}

		auto len = s.length();
		for (std::size_t i{}; i < len; ++i)
		{
			os << s[i];
			auto n = len - 1 - i;
			if (n && n % 3 == 0)
				os << '.';
		}

		return os;
	}

private:
	long long mx;
};

//--------------------------------------------------
//--------------------------------------------------

template <typename R, typename P>
std::ostream &operator<<(std::ostream &os, const std::chrono::duration<R, P> &dur)
{
	return os << de(dur.count()) << " * (" << de(P::num) << " / " << de(P::den) << ")";
}

//--------------------------------------------------
//--------------------------------------------------

void print_time(const time_t &timer);

//--------------------------------------------------
//--------------------------------------------------

constexpr inline const char *regex_validate_email()
{
	return R"((?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9]?[0-9]))\.){3}(?:(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9]?[0-9])|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\]))";
}

//--------------------------------------------------
//--------------------------------------------------

template <typename C>
class BackInsertIterator
{
public:
	BackInsertIterator(C &c) : rc{c} {}
	BackInsertIterator &operator*() { return *this; }
	BackInsertIterator &operator++() { return *this; }
	BackInsertIterator &operator++(int) { return *this; }
	BackInsertIterator &operator=(const typename C::value_type &val)
	{
		rc.push_back(val);
		return *this;
	}

private:
	C &rc;
};

template <typename C>
BackInsertIterator<C> BackInserter(C &c)
{
	return BackInsertIterator<C>{c};
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

template <typename C>
class FrontInsertIterator
{
public:
	FrontInsertIterator(C &c) : rc{c} {}
	FrontInsertIterator &operator*() { return *this; }
	FrontInsertIterator &operator++() { return *this; }
	FrontInsertIterator &operator++(int) { return *this; }
	FrontInsertIterator &operator=(const typename C::value_type &val)
	{
		rc.insert(rc.begin(), val);
		return *this;
	}

private:
	C &rc;
};
template <typename C>
FrontInsertIterator<C> FrontInserter(C &c)
{
	return FrontInsertIterator<C>{c};
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

template <typename T>
class Ostream_iterator
{
public:
	Ostream_iterator(std::ostream &os, const char *p = " ") : m_os{os}, m_sep{p} {}
	Ostream_iterator &operator*() { return *this; }
	Ostream_iterator &operator++() { return *this; }
	Ostream_iterator &operator++(int) { return *this; }
	Ostream_iterator &operator=(const T &tval)
	{
		m_os << tval << m_sep;
		return *this;
	}

private:
	std::ostream &m_os;
	const char *m_sep;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#endif
