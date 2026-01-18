#pragma once
#include <iostream>

enum class Month { // If we don't give 1 to jan then it will be 0, also the compiler going to finish the rest from 1+n
		Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

enum class Day {
	monday=1, tuesday, wednesday, thursday, friday, saturday, sunday
};

inline Month operator++(Month& m) {
	m = (m == Month::Dec) ? Month::Jan : Month(int(m) + 1);
	return m;
};

class Date {
public:
	class Invalid {};
	Date();
	Date(int y, Month m, int d);
	int GetEMonth() const { return int(month); }
	int GetMonth() const { return month; }
	int GetDay() const { return day; }
	int GetYear() const { return year; }

	void AddDay(int n);

private:
    int year{0};
    int month{0};
	Month Emonth{Month::Jan};
    int day{0};
    bool is_valid();
};

std::ostream& operator<<(std::ostream& os, const Date& d);
std::istream& operator>>(std::istream& is, Date& d);