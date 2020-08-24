#ifndef __DATEEXCEPTIONS_H
#define __DATEEXCEPTIONS_H

#include <iostream>
#pragma warning(disable:4290)

using namespace std;
//decleration of class
class DateExceptions
{
protected:
	int day, month, year;
public:
	DateExceptions(int day, int month, int year) {}
	virtual void print() const = 0;
};
class InvalidDayExceptions: public DateExceptions
{
public:
	InvalidDayExceptions(int day, int month, int year) : DateExceptions(day, month, year) {}
	virtual void print() const { cout << "Wrong input for the Day of the Date." << endl << endl; }
};
class InvalidMonthExceptions : public DateExceptions
{
public:
	InvalidMonthExceptions(int day, int month, int year) : DateExceptions(day, month, year) {}
	virtual void print() const { cout << "Wrong input for  the Month of the Date." << endl << endl; }
};
class InvalidYearExceptions : public DateExceptions
{
public:
	InvalidYearExceptions(int day, int month, int year) : DateExceptions(day, month, year) {}
	virtual void print() const { cout << "Wrong input for the Year of the Date." << endl << endl; }
};
#endif 

