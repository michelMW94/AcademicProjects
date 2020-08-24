#ifndef __DEPARTMENTEXCEPTIONS_H
#define __DEPARTMENTEXCEPTIONS_H

#include <iostream>
#include <string.h>
#pragma warning(disable:4290)

using namespace std;
//decleration of class
class DepartmentExceptions
{
protected:
	std::string name;
public:
	DepartmentExceptions(const std::string name) {}
	virtual void print() const = 0;
};
class InvalidNameDepartmentExceptions : public DepartmentExceptions
{
public:
	InvalidNameDepartmentExceptions(const std::string name) : DepartmentExceptions(name) {}
	virtual void print() const { cout << "An empty name isn't valid for a Department." << endl << endl; }
};
#endif 

