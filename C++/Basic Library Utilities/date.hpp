#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>

class Date
{
public: // public nested types
	enum class Weekday
	{
		Sunday = 1,
		Monday,
		Tuesday,
		Wednesday,
		Thursday,
		Friday,
		Saturday,
	};
	enum class Months
	{
		January = 1,
		February,
		March,
		April,
		May,
		June,
		July,
		August,
		September,
		October,
		November,
		December
	};

public: // public member funtions
	constexpr Date() {}
	// constexpr Date(int d, int m, int y) : md{d}, mm{m}, my{y} // exception handling
	Date(int d, int m, int y) : md{d}, mm{m}, my{y}
	{
		if (!Date::is_valid(md, mm, my))
		{
			std::cerr << "Invalid date!!!...\n";
			exit(EXIT_FAILURE);
		}
	}
	Date(const char *p)
		: md{std::atoi(p)},
		  mm{std::atoi(std::strchr(p, '/') + 1)},
		  my{std::atoi(std::strrchr(p, '/') + 1)}
	{
		if (!Date::is_valid(md, mm, my))
		{
			std::cerr << "Invalid date!!!...\n";
			exit(EXIT_FAILURE);
		}
	}
	Date(std::time_t timer)
		: md{std::localtime(&timer)->tm_mday},
		  mm{std::localtime(&timer)->tm_mon + 1},
		  my{std::localtime(&timer)->tm_year + year_base}
	{
		if (!Date::is_valid(md, mm, my))
		{
			std::cerr << "Invalid date!!!...\n";
			exit(EXIT_FAILURE);
		}
	}

	constexpr int get_month_day() const { return md; }
	constexpr int get_month() const { return mm; }
	constexpr int get_year() const { return my; }
	int get_year_day() const
	{
		int year_day = md;

		switch (mm - 1)
		{
		case 11:
			year_day += 30;
		case 10:
			year_day += 31;
		case 9:
			year_day += 30;
		case 8:
			year_day += 31;
		case 7:
			year_day += 31;
		case 6:
			year_day += 30;
		case 5:
			year_day += 31;
		case 4:
			year_day += 30;
		case 3:
			year_day += 31;
		case 2:
			year_day += Date::is_leap(my) ? 29 : 28;
		case 1:
			year_day += 31;
		}

		return year_day;
	}
	Weekday get_week_day() const
	{
		static const int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

		int d = md;
		int m = mm;
		int y = my;

		y -= m < 3;

		return static_cast<Weekday>((y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7 + 1);
	}

	Date &set_month_day(int day)
	{
		if (!Date::is_valid(day, mm, my))
		{
			std::cerr << "Invalid date!!!...\n";
			exit(EXIT_FAILURE);
		}

		md = day;
		return *this;
	}
	Date &set_month(int month)
	{
		if (!Date::is_valid(md, month, my))
		{
			std::cerr << "Invalid date!!!...\n";
			exit(EXIT_FAILURE);
		}

		mm = month;
		return *this;
	}
	Date &set_year(int year)
	{
		if (!Date::is_valid(md, mm, year))
		{
			std::cerr << "Invalid date!!!...\n";
			exit(EXIT_FAILURE);
		}

		my = year;
		return *this;
	}
	Date &set(int day, int mon, int year)
	{
		if (!Date::is_valid(day, mon, year))
		{
			std::cerr << "Invalid date!!!...\n";
			exit(EXIT_FAILURE);
		}

		md = day;
		mm = mon;
		my = year;

		return *this;
	}

	Date operator+(int day) const
	{
		if (md + day <= Date::dayLookup[Date::is_leap(my)][mm])
			return Date{md + day, mm, my};
		else if (get_year_day() + day <= (Date::is_leap(my) ? 366 : 365))
			return Date::get_date_from_day_of_year(get_year_day() + day, my);

		return Date::go_to_day_next(*this, day);
	}
	Date &operator+=(int day)
	{
		if (md + day <= Date::dayLookup[Date::is_leap(my)][mm])
			this->md += day;
		else if (get_year_day() + day <= (Date::is_leap(my) ? 366 : 365))
			*this = Date::get_date_from_day_of_year(get_year_day() + day, my);
		else
			*this = Date::go_to_day_next(*this, day);

		return *this;
	}

	Date operator-(int day) const
	{
		if (md - day >= 1)
			Date{md - day, mm, my};
		else if (get_year_day() - day >= 1)
			return Date::get_date_from_day_of_year(get_year_day() - day, my);

		return Date::go_to_day_prev(*this, day);
	}
	Date &operator-=(int day)
	{
		if (md - day >= 1)
			this->md -= day;
		else if (get_year_day() - day >= 1)
			*this = Date::get_date_from_day_of_year(get_year_day() - day, my);
		else
			*this = Date::go_to_day_prev(*this, day);

		return *this;
	}

	Date &operator++()
	{
		if (md < dayLookup[Date::is_leap(my)][mm])
			++md;
		else if (mm < 12)
		{
			++mm;
			md = 1;
		}
		else
		{
			md = 1;
			mm = 1;
			++my;
		}

		return *this;
	}
	Date operator++(int)
	{
		Date temp{*this};
		++*this;
		return temp;
	}
	Date &operator--()
	{
		if (md > 1)
			--md;
		else if (mm > 1)
		{
			--mm;
			md = dayLookup[Date::is_leap(my)][mm];
		}
		else
		{
			md = 31;
			mm = 12;
			--my;
		}

		return *this;
	}
	Date operator--(int)
	{
		Date temp{*this};
		--*this;
		return temp;
	}

	constexpr friend bool operator<(const Date &d1, const Date &d2)
	{
		return d1.my < d2.my ||
			   (d1.my == d2.my && d1.mm < d2.mm) ||
			   (d1.my == d2.my && d1.mm == d2.mm && d1.md < d2.md);
	}
	constexpr friend bool operator==(const Date &d1, const Date &d2)
	{
		return d1.md == d2.md && d1.mm == d2.mm && d1.my == d2.my;
	}

	friend int operator-(const Date &d1, const Date &d2)
	{
		int result;

		if (d1 == d2)
			return 0;

		if (d1.my == d2.my && d1.mm == d2.mm)
			return d1.md - d2.md;
		else if (d1.my == d2.my && d1.mm != d2.mm)
			return d1.get_year_day() - d2.get_year_day();
		else if (d1.my > d2.my)
		{
			result = d1.get_year_day() + (Date::is_leap(d2.my) ? 366 : 365) - d2.get_year_day();
			for (int i = d2.my + 1; i < d1.my; ++i)
				result += Date::is_leap(i) ? 366 : 365;
			return result;
		}

		result = d2.get_year_day() + (Date::is_leap(d1.my) ? 366 : 365) - d1.get_year_day();
		for (int i = d1.my + 1; i < d2.my; ++i)
			result += Date::is_leap(i) ? 366 : 365;
		return result * -1;
	}

	friend Date operator+(const Date &date, int n)
	{
		return Date::go_to_day_next(date, n);
	}
	friend Date operator+(int n, const Date &date)
	{
		return Date::go_to_day_next(date, n);
	}

	friend Date::Weekday &operator++(Date::Weekday &wd)
	{
		return wd = wd == Date::Weekday::Saturday ? Date::Weekday::Sunday
												  : static_cast<Date::Weekday>(static_cast<int>(wd) + 1);
	}
	friend Date::Weekday operator++(Date::Weekday &wd, int)
	{
		Date::Weekday wd_temp{wd};
		++wd;
		return wd_temp;
	}
	friend Date::Weekday &operator--(Date::Weekday &wd)
	{
		return wd = wd == Date::Weekday::Sunday ? Date::Weekday::Saturday
												: static_cast<Date::Weekday>(static_cast<int>(wd) - 1);
	}
	friend Date::Weekday operator--(Date::Weekday &wd, int)
	{
		Date::Weekday wd_temp{wd};
		--wd;
		return wd_temp;
	}

	friend std::ostream &operator<<(std::ostream &os, const Date &date)
	{
		return os << date.md << ' '
				  << Date::month_names[date.mm] << ' '
				  << date.my << ' '
				  << Date::day_names[static_cast<int>(date.get_week_day())]
				  << '\n';
	}
	friend std::istream &operator>>(std::istream &is, Date &date)
	{
		is >> date.md;
		std::getchar();
		is >> date.mm;
		std::getchar();
		is >> date.my;

		if (!Date::is_valid(date.md, date.mm, date.my))
		{
			std::cerr << "Invalid date!!!...\n";
			exit(EXIT_FAILURE);
		}

		return is;
	}

public: // static public member functions
	static Date random_date()
	{
		int year = rand() % (random_max_year + 1 - random_min_year) + random_min_year;
		int month = rand() % 12 + 1;
		int day = rand() % dayLookup[Date::is_leap(year)][month] + 1;

		return Date{day, month, year};
	}
	static constexpr bool is_leap(int y)
	{
		return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
	}

private: // static private member functions
	constexpr static bool is_valid(int d, int m, int y)
	{
		return y >= year_base &&
			   d && d <= dayLookup[Date::is_leap(y)][m] &&
			   m && m <= 12;
	}
	static Date get_date_from_day_of_year(int day_of_year, int year)
	{
		int day;
		int month = 1;

		while (1)
		{
			if (day_of_year > Date::dayLookup[Date::is_leap(year)][month])
				day_of_year -= Date::dayLookup[Date::is_leap(year)][month];
			else if (day_of_year <= Date::dayLookup[Date::is_leap(year)][month])
			{
				day = day_of_year;
				break;
			}
			++month;
		}

		return Date{day, month, year};
	}
	static Date go_to_day_next(Date d, int plus_days)
	{
		plus_days -= (Date::is_leap(d.my) ? 366 : 365) - d.get_year_day();

		d.md = d.mm = 1;
		d.my += 1;

		while (plus_days >= (Date::is_leap(d.my) ? 366 : 365))
		{
			plus_days -= Date::is_leap(d.my) ? 366 : 365;
			++d.my;
		}

		return !plus_days ? d : get_date_from_day_of_year(plus_days, d.my);
	}
	static Date go_to_day_prev(Date d, int minus_days)
	{
		minus_days -= d.get_year_day();
		d.md = 31;
		d.mm = 12;
		d.my -= 1;

		while (minus_days >= (Date::is_leap(d.my) ? 366 : 365))
		{
			minus_days -= Date::is_leap(d.my) ? 366 : 365;
			--d.my;
		}

		return !minus_days ? d : get_date_from_day_of_year((Date::is_leap(d.my) ? 366 : 365) - minus_days, d.my);
	}

public: // static public data members
	static constexpr int year_base = 1900;
	static constexpr int random_min_year = 1940;
	static constexpr int random_max_year = 2023;

private: // static private data members
	constexpr static const char *day_names[8]{
		"EMPTY",
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday",
	};
	constexpr static const char *month_names[13]{
		"EMPTY",
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December",
	};
	constexpr static const int dayLookup[2][13]{
		{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	};

private: // nonstatic private data members
	int md{1};
	int mm{1};
	int my{year_base};
};

constexpr bool operator<=(const Date &d1, const Date &d2)
{
	return d1 < d2 || d1 == d2;
}
constexpr bool operator>(const Date &d1, const Date &d2)
{
	return d2 < d1;
}
constexpr bool operator>=(const Date &d1, const Date &d2)
{
	return d2 < d1 || d1 == d2;
}
constexpr bool operator!=(const Date &d1, const Date &d2)
{
	return !(d1 == d2);
}

#endif
