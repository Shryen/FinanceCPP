#include "Date.h"
#include "Windows.h"
#include <iostream>

Date::Date()
{
	SYSTEMTIME SystemTime, LocalTime;

	GetSystemTime(&SystemTime);
	GetLocalTime(&LocalTime);

	year = SystemTime.wYear;
	month = SystemTime.wMonth;
	day = SystemTime.wDay;
	Emonth = static_cast<Month>(month);
}

Date::Date(int y, Month m, int d) : year(y), Emonth(m), day(d)
{
	if (!is_valid()) throw Invalid{};
}

void Date::AddDay(int n)
{
	
}

bool Date::is_valid()
{
	return true;
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
	return os << d.GetYear() << "-" << d.GetEMonth() << "-" << d.GetDay();
}

std::istream& operator>>(std::istream& is, Date& d)
{
	int y, m, day;
	char dash1, dash2;
	if (is >> y >> dash1 >> m >> dash2 >> day)
		d = Date(y, static_cast<Month>(m), day);
	else
		is.setstate(std::ios::failbit);
	return is;
}
