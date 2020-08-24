#ifndef _DEPARTMENT_H_
#define _DEPARTMENT_H_


// includes
#include "DepartmentExceptions.h"
#include "Array.h"
//decleration of the class
class Employee;
class Patient;

class Department
{
	std::string name;
	// med workers
	vector<Employee*> AllWorkers_department;
	vector<Patient*> AllPatients_department;
	

public:
	//C'tor
	Department(const std::string name = "unknown") throw (DepartmentExceptions);
	//copy c'tor
	Department(const Department& other);
	//set f
	void setName(const string&  name) { this->name = name; }//set f

	//get f
	const string& getName()   const { return name; }// get f
	vector<Employee*> getallWorkers() const { return AllWorkers_department; }
	vector<Patient*>  getAllPatients_department() const { return AllPatients_department; }

	//print f
	friend ostream& operator <<(ostream& os, const Department& d);// opertor ostream f
																  //
	const Department& operator=(const Department& d);// operator = f

	//add f


	friend class Hospital;
};
class Dep_str
{
public:
	bool operator()(Department* first_dep, Department* second_dep) const
	{
		return first_dep->getName() < second_dep->getName();
	}
};
#endif 
