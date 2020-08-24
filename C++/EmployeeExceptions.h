#ifndef __EMPLOYEEEXCEPTIONS_H
#define __EMPLOYEEEXCEPTIONS_H

#include <iostream>
#include <string.h>
#pragma warning(disable:4290)

using namespace std;
//decleration of class
class EmployeeExceptions
{
protected:
	std::string name;
public:
	EmployeeExceptions(const std::string name) {}
	virtual void print() const = 0;
};
class InvalidNameEmployeeExceptions : public EmployeeExceptions
{
public:
	InvalidNameEmployeeExceptions(const std::string name) : EmployeeExceptions(name) {}
	virtual void print() const { cout << "An empty name isn't valid for an Employee." << endl << endl; }
};
#endif 


