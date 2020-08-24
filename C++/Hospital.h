#ifndef __HOSPITAL_H
#define __HOSPITAL_H

// includes
#include "Date.h"
#include "Nurse.h"
#include "Research_Institute.h"
#include "Array.h"
#include "Patient.h"

#include "Department.h"
//decleration of class

class Hospital
{
	// departments
	set<Department*, Dep_str> AllDepartments;
	// med workers
	set<Employee*, Employee_str> AllWorkers_hospital;
	//pateint
	set<Patient*, Patient_id> AllPatient_hospital;
	//institute
	vector<Research_Institute*> Institute;
public:
	//C'tor
	Hospital() { Institute.push_back(new Research_Institute()); }
	//copy C'tor
	Hospital(const Hospital& other) = delete;
	//D'tor
	~Hospital(){}

	// adding f
	void add_Depart();
	void add_new_nurse() throw (const char*);
	void add_new_doctor()throw (const char*);
	void add_new_patient() throw (const char*);
	void add_info_patient()throw (const char*);
	void add_researcher();
	void add_essay()throw (const char*);

	//get f
	set<Department*, Dep_str> getAllDepartments()const { return AllDepartments; }
	set<Employee*, Employee_str> getAllWoorkers_hospital()const { return AllWorkers_hospital; }
	set<Patient*, Patient_id> getAllPatient_hospital()const { return AllPatient_hospital; }
	vector<Research_Institute*> getInstitute()const { return Institute; }

	//print f
	void show_menu()const;
	void print_patients_depart() const throw(const char*);
	void print__single_patient() const throw(const char*);
	void  print_all_researchers_doctors() const throw(const char*);

	//comparing f
	void comparing_researcher_by_num_essays() const throw(const char*);
	
};
#endif 

