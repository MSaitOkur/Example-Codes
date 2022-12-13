#ifndef DATE_INCLUDED
#define DATE_INCLUDED

#include <iosfwd>
#include <ctime>
#include <stdexcept>

class Date
{
public:
    enum class Weekday
    {
        Sunday,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday
    };

    static constexpr int year_base = 1900;
    static constexpr int random_min_year = 1940;
    static constexpr int random_max_year = 2020;

    static int dayLookup[2][13];

    Date() = default;
    Date(int d, int m, int y);
    Date(const char *p);
    Date(std::time_t timer);

    int get_month_day() const ;
    int get_month() const ;
    int get_year() const ;
    int get_year_day() const ;
    Weekday get_week_day() const ;

    Date &set_month_day(int day);
    Date &set_month(int month);
    Date &set_year(int year);
    Date &set(int day, int mon, int year);

    Date &operator+=(int day);
    Date &operator-=(int day);
    Date operator-(int day) const ;
    Date &operator++();
    Date operator++(int);
    Date &operator--();
    Date operator--(int);

    static Date random_date();
    static bool isleap(int y);

    friend bool operator<(const Date &, const Date &);
    friend bool operator==(const Date &, const Date &);
    friend std::ostream &operator<<(std::ostream &os, const Date &date);
    friend std::istream &operator>>(std::istream &is, Date &date);

private:
    static bool isValidDate(int d, int m, int y);

    int m_day{1}, m_mon{1}, m_year{1900};
};

std::ostream &operator<<(std::ostream &os, const Date &date);
std::istream &operator>>(std::istream &is, Date &date);

bool operator<(const Date &, const Date &);
bool operator<=(const Date &, const Date &);
bool operator>(const Date &, const Date &);
bool operator>=(const Date &, const Date &);
bool operator==(const Date &, const Date &);
bool operator!=(const Date &, const Date &);

int operator-(const Date &d1, const Date &d2);
Date operator+(const Date &date, int n);
Date operator+(int n, const Date &);
Date::Weekday &operator++(Date::Weekday &r);
Date::Weekday operator++(Date::Weekday &r, int);
Date::Weekday &operator--(Date::Weekday &r);
Date::Weekday operator--(Date::Weekday &r, int);

class BadDate : public std::exception
{
public:
    const char* what()const noexcept override;
};

#endif //DATE_INCLUDED

/*


#ifndef DATE_H
#define DATE_H
#include <iosfwd>
#include <ctime>

namespace project {
class Date {
public:
	static constexpr int year_base = 1900;  //1
	static constexpr int random_min_year = 1940;  //2
	static constexpr int random_max_year = 2020;  //3
	enum class Weekday {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday}; //4
	Date(); //5 
	Date(int d, int m, int y);  //6
	Date(const char *p);  //7
	Date(std::time_t timer); //8
	int get_month_day()const; //9
	int get_month()const; //10
	int get_year()const; //11
	int get_year_day()const; //12
	Weekday get_week_day()const; //13

	Date& set_month_day(int day); //14
	Date& set_month(int month); //15
	Date& set_year(int year); //16
    Date& set(int day, int mon, int year); //17
	Date operator-(int day)const; //18
	Date& operator+=(int day); //19
	Date& operator-=(int day); //20
	Date& operator++(); //21
	Date operator++(int); //22
	Date& operator--(); //23
	Date operator--(int); //24

	friend bool operator<(const Date &, const Date &); //27
	friend bool operator==(const Date &, const Date &); //27
	static Date random_date(); //25
	static constexpr bool isleap(int y); //26

	friend std::ostream &operator<<(std::ostream &os, const Date &date); //31
	friend std::istream &operator>>(std::istream &is, Date &date); //32
};

bool operator<(const Date &, const Date &); //27
bool operator<=(const Date &, const Date &); //27
bool operator>(const Date &, const Date &); //27
bool operator>=(const Date &, const Date &); //27
bool operator==(const Date &, const Date &); //27
bool operator!=(const Date &, const Date &); //27

int operator-(const Date &d1, const Date &d2); //28
Date operator+(const Date &date, int n); //29
Date operator+(int n, const Date &); //29
Date::Weekday& operator++(Date::Weekday &r); //30
Date::Weekday operator++(Date::Weekday &r, int); //30
Date::Weekday& operator--(Date::Weekday &r); //30
Date::Weekday operator--(Date::Weekday &r, int); //30}

#endif


*/
