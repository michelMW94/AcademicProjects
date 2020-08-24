#ifndef __EMPLOYEE_H
#define __EMPLOYEE_H
// includes
#include "Array.h"
#include "EmployeeExceptions.h"
#include "EmployeeGenerator.h"
#include <string>


//decleration of the class
class Employee
{
protected:
	std::string name;

public:
	Employee(const std::string& name = "unknown") throw (EmployeeExceptions);//c'tor
	const string& getName()   const { return name; }// get f
	void setName(const string&  name) { this->name = name; }//set f
	virtual void toOs(ostream& os) const {}
	friend ostream& operator <<(ostream& os, const Employee& e);// opertor ostream f
	virtual Employee* clone() const = 0;// copy f
	bool operator==(const Employee& e) const;

	// files
	Employee(ifstream& inFile);
	void saveTYPE(ofstream & outFile) const;
	virtual void save(ofstream & outFile) const = 0;

};
class Employee_str
{
public:
	bool operator()(Employee* first_Employee, Employee* second_Employee) const
	{
			return first_Employee->getName() < second_Employee->getName();
	}
};
#endif 



