#include "Date.h"

//c'tor
Date::Date(int day, int month, int year) throw (DateExceptions)
{
	if (year < MIN_YEAR || year > MAX_YEAR)
		throw InvalidYearExceptions(day, month, year);
	else if (month < eMonth::Jan || month >eMonth::Dec)
		throw InvalidMonthExceptions(day, month, year);
	else if (!(check_Day(day)))
		throw InvalidDayExceptions(day, month, year);
	this->day = day;
	this->month = month;
	this->year = year;
}
//copy c'tor
Date::Date(const Date& other)
{
	*this = other;
}
// operator =
const Date& Date::operator=(const Date& d)
{
	if (this != &d)
	{
		year = d.year;
		month = d.month;
		day = d.day;
	}
	return *this;
}
//set f
bool Date::check_Day(int day)
{
	bool answer = false;
	if (day <= 0 || day > MAX_DAY_IN_MONTH)
	{
		return false;
	}
	else
	{
		if (this->month == eMonth::Feb)
		{
			if (this->year % 4 != 0 && day <= 28)
				answer = true;
			else if (this->year % 4 == 0 && day <= 29)
				answer = true;
		}
		else if ((this->month == eMonth::Apr || this->month == eMonth::Jun || this->month == eMonth::Sep || this->month == eMonth::Nov) && day <= 30)
			answer = true;
		else if (day <= MAX_DAY_IN_MONTH)
			answer = true;
	}
	return answer;
}

// print f
ostream& operator <<(ostream& os, const Date& d)
{
	os << "Date: " << (d.day < 10 ? "0" : "") << d.day << "/" << (d.month < eMonth::Oct ? "0" : "") << d.month;
	cout << "/" << d.year << endl;
	return os;
}