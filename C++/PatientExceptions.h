#ifndef __PATIENTEXCEPTIONS_H
#define __PATIENTEXCEPTIONS_H

#include <iostream>
#include <string.h>
#include "Date.h"
#pragma warning(disable:4290)

using namespace std;
//decleration of class
class PatientExceptions
{
protected:
	std::string name;
	int id, year_of_birth;
	Date visit_date;
	int p_gender;
public:
	PatientExceptions(const std::string name, int p_id, int year_birth, int gender) {}
	virtual void print() const = 0;
};
class InvalidNamePatientExceptions : public PatientExceptions
{
public:
	InvalidNamePatientExceptions(const std::string name, int p_id, int year_birth, int gender) : PatientExceptions(name, p_id, year_birth,gender) {}
	virtual void print() const { cout << "An empty name isn't valid for a Patient." << endl << endl; }
};
class InvalidIdPatientExceptions : public PatientExceptions
{
public:
	InvalidIdPatientExceptions(const std::string name, int p_id, int year_birth,int gender) : PatientExceptions(name, p_id, year_birth, gender) {}
	virtual void print() const { cout <<  "Wrong input for id of a Patient." << endl << endl; }
};
class InvalidYearBirthPatientExceptions : public PatientExceptions
{
public:
	InvalidYearBirthPatientExceptions(const std::string name, int p_id, int year_birth, int gender) : PatientExceptions(name, p_id, year_birth, gender) {}
	virtual void print() const { cout << "Wrong input for Birth Year of a Patient." << endl << endl; }
};
class InvalidGenderPatientExceptions : public PatientExceptions
{
public:
	InvalidGenderPatientExceptions(const std::string name, int p_id, int year_birth, int gender) : PatientExceptions(name, p_id, year_birth, gender) {}
	virtual void print() const { cout << "Wrong input for Gender of a Patient." << endl << endl; }
};
#endif 


