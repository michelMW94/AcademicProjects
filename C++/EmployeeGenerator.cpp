#include "EmployeeGenerator.h"
#include "DoctorResearcher.h"
#include "Nurse.h"
#include"SurgeonResearcher.h"

Employee* EmployeeGenerator::loadEmployee(ifstream& inFile)
{
	EmployeeType type;
	inFile.read((char*)&type, sizeof(int));
	if (type == DOCTOR)
		return new Doctor(inFile);
	else if (type == NURSE)
		return new Nurse(inFile);
	else if (type == SURGEON)
		return new Surgeon(inFile);
	else if (type == SURGEON_RESEARCHER)
		return new SurgeonResearcher(inFile);
	else if (type == DOCTOR_RESEARCHER)
		return new DoctorReasearcher(inFile);
	else if (type == RESEARCHER)
		return new Researcher(inFile);
	else
		return NULL;

}
EmployeeGenerator::EmployeeType EmployeeGenerator::getType(const Employee* employee)
{
	if (typeid(*employee) == typeid(Doctor))
		return DOCTOR;
	else if (typeid(*employee) == typeid(Nurse))
		return NURSE;
	else if (typeid(*employee) == typeid(Surgeon))
		return SURGEON;
	else if (typeid(*employee) == typeid(SurgeonResearcher))
		return SURGEON_RESEARCHER;
	else if (typeid(*employee) == typeid(DoctorReasearcher))
		return DOCTOR_RESEARCHER;
	else if (typeid(*employee) == typeid(Researcher))
		return RESEARCHER;
	else
		return UNKNOWN;

}