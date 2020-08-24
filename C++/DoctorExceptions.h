#ifndef __DOCTOREXCEPTIONS_H
#define __DOCTOREXCEPTIONS_H

#include <iostream>
#include <string.h>
#pragma warning(disable:4290)

using namespace std;
//decleration of class
class DoctorExceptions
{
protected:
	std::string skill;
public:
	DoctorExceptions(const std::string skill) {}
	virtual void print() const = 0;
};
class InvalidSkillDoctorExceptions : public DoctorExceptions
{
public:
	InvalidSkillDoctorExceptions(const std::string skill) :DoctorExceptions(skill) {}
	virtual void print() const { cout << "An empty skill name isn't valid for a Doctor." << endl << endl; }
};
#endif 



