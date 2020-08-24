#ifndef __DATE_H
#define __DATE_H

#include "DateExceptions.h"
#include <fstream>
// CONSTANTS DECLARATION
const int NAME_LENGTH = 20;
const int MAX_DAY_IN_MONTH = 31;
const int MAX_MONTH_IN_YEAR = 12;
const int MIN_YEAR = 1990;
const int MAX_YEAR = 2019;
enum eMonth {
	Jan = 1, Feb = 2, Mar = 3, Apr = 4, May = 5, Jun = 6, Jul = 7,
	Aug = 8, Sep = 9, Oct = 10, Nov = 11, Dec = 12
};
//decleration of class
class Date
{
	int day, month, year;
public:
	//c'tor
	Date(int day = 1, int month = 1, int year = 2000) throw (DateExceptions);
	//copy c'tor
	Date(const Date& other);
	// d'tor
	~Date() {}
	// set f
	bool check_Day(int day);
	// get f
	int getDay() const { return day; }
	int getMonth()const { return month; }
	int getYear()const { return year; }
	// print date f
	const Date& operator = (const Date& d);
	// print date f
	friend ostream& operator<<(ostream& os, const Date& d);
	//files
	Date(ifstream& inFile) { inFile.read((char*)this, sizeof(*this)); }
	void save_date(ofstream &outFile) const{ outFile.write((const char*)this, sizeof(*this));}
};
#endif 
