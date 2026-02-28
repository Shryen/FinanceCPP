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

	hour = SystemTime.wHour;
	minute = SystemTime.wMinute;
	second = SystemTime.wSecond;
}

Date::Date(int y, Month m, int d, int hour, int minute, int second) : year(y), Emonth(m), day(d), hour(hour), minute(minute), second(second)
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
	return os << d.GetYear() << "-"
		<< d.GetEMonth() << "-"
		<< d.GetDay() << "/"
		<< d.GetHour() << ":"
		<< d.GetMinute() << ":"
		<< d.GetSecond();
}

std::istream& operator>>(std::istream& is, Date& d)
{
	int y, m, day, hour, minute, second;
	char dash1, dash2, slash, semicolon1, semicolon2;
	if (is >> y >> dash1 >> m >> dash2 >> day >> slash >> hour >> semicolon1 >> minute >> semicolon2 >> second){
		if (dash1 != '-' || dash2 != '-' || slash != '/' || semicolon1 != ':' || semicolon2 != ':')
			is.setstate(std::ios::failbit);

		d = Date(y, static_cast<Month>(m), day, hour, minute, second);
	}
	else
		is.setstate(std::ios::failbit);
	return is;
}
