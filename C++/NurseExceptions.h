#ifndef __NURSEEXCEPTIONS_H
#define __NURSEEXCEPTIONS_H

#include <iostream>
#pragma warning(disable:4290)

using namespace std;
//decleration of class
class NurseExceptions
{
protected:
	int Years_of_Exp;
public:
	NurseExceptions(int Years_of_Exp) {}
	virtual void print() const = 0;
};
class InvalidYearsofExperienceExceptions : public NurseExceptions
{
public:
	InvalidYearsofExperienceExceptions(int Years_of_Exp) : NurseExceptions(Years_of_Exp) {}
	virtual void print() const { cout << "Wrong input for Years of Experience of a Nurse." << endl << endl; }
};
#endif 


