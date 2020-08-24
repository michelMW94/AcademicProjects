#include "Department.h"
#include "Employee.h"
#include "MedWorker.h"


//c'tor
Department::Department(const std::string name) throw (DepartmentExceptions)
{
	if (name == "")
		throw InvalidNameDepartmentExceptions(name);
	setName(name);
}
// copy c'tor
Department::Department(const Department& other)
{
	*this = other;
}
// print f
ostream& operator <<(ostream& os, const Department& d)
{
	os << "Department's Name: " << d.getName().c_str() << endl;
	return os;
}
const Department& Department::operator=(const Department& d)
{
	if (this != &d)
	{
		AllWorkers_department = d.AllWorkers_department;
		AllPatients_department = d.AllPatients_department;
	}
	return *this;
}
