#ifndef __PATIENT_H
#define __PATIENT_H

// includes
#include "PatientExceptions.h"
#include <vector>
#include "Operation.h"
#include "Examination.h"
// decleration of const
const int MIN_ID = 000000000;
const int MAX_ID = 999999999;
const int MIN_YEAR_BIRTH = 1900;
typedef enum { MALE, FEMALE } Gender;

//
class Date;
class Department;
//decleration of class
class Employee;

class Patient
{
protected:
	std::string name;
	int id, year_of_birth;
	Date visit_date;
	Gender p_gender;
	vector<Department*> TheDepartment;
	vector<Employee*> MedicalSupervisor;
	vector<VisitPurpose*> TheVisitPurpose;

public:

	const char* genders[NAME_LENGTH] = { "MALE", "FEMALE" };
	// c'tor
	Patient(const std::string name="unknown", int id= MIN_ID, 
		int year_of_birth=MIN_YEAR_BIRTH, Date visit_date=Date(), int p_gender=0 ) throw(PatientExceptions);
	//copy c'tor
	Patient(const Patient& other);
	//
	const Patient& operator=(const Patient& p);
	//d'tor
	~Patient(){}
	// get f
	const string& getName() const { return name; }
	const char * getGendersArr() const { return genders[NAME_LENGTH]; }
	int getId() const { return id; }
	int getBirthYear() const { return year_of_birth; }
	Date getVisitDate() const { return visit_date; }
	Gender getGender() const { return p_gender; }

	vector<Department*>  getdepart() const { return TheDepartment; }
	vector<Employee*> getMedicalSupervisor() const { return MedicalSupervisor; }
	vector<VisitPurpose*> getTheVisitPurpose()const { return TheVisitPurpose; }
	//set f
	void setName(const string&  name) { this->name = name; }//set f
	void setVisitDate(Date visit_date) { this->visit_date = visit_date; }

	bool operator==(const Patient& other)const { return (id == other.id); }
	//print F
	friend ostream& operator <<(ostream& os, const Patient& e);// opertor ostream f


	//files
	Patient(ifstream& inFile);
	void save(ofstream & outFile) const;
	friend class Hospital;

};
class Patient_id
{
public:
	bool operator()(Patient* first_Patient, Patient* second_Patient) const
	{
		return first_Patient->getId() < second_Patient->getId();
	}
};
#endif 


