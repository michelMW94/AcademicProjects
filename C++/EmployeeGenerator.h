#ifndef __EMPLOYEEGENERATOR_H
#define __EMPLOYEEGENERATOR_H
// include
#include <fstream>
using namespace std;
class Employee;
//decleration of the class
class EmployeeGenerator
{
public:
	enum EmployeeType { UNKNOWN, DOCTOR, NURSE, SURGEON, DOCTOR_RESEARCHER, SURGEON_RESEARCHER, RESEARCHER };
	static Employee* loadEmployee(ifstream& inFile);
	static EmployeeType getType(const Employee* employee);

};
#endif 
