#include "Hospital.h"
#include "Department.h"
#include <string>
#include <algorithm>
#include "Research_Institute.h"

// add f
void Hospital::add_essay() throw (const char*)
{

	std::string researcher_name, essay_name, essay_magazine;
	Date new_date;
	int day, month, year;
	try
	{
		if (!(Institute[0]->AllResearchers.size()))
		throw "There are no Researcher in the institute, please add one before adding a new Essay.";
		cout << "Please insert the new Essay's following Information: " << endl;
		cout << "Name: ";
		cin >> essay_name;
		cout << "Publish Magazine: ";
		cin >> essay_magazine;
		cout << "Please enter the date: (day month year):";
		cin >> day >> month >> year;

		try
		{
			new_date = Date(day, month, year);
			Essay * new_essay = new Essay(new_date, essay_magazine, essay_name);
			cout << "Please insert the new Essay's researcher: ";
			cin >> researcher_name;
			set<Employee*, Employee_str>::iterator itr = Institute[0]->AllResearchers.find(new Researcher(researcher_name));
			if (itr == Institute[0]->AllResearchers.end())
				throw "There is no such a name of researcher in the institute";
			Researcher* tempResearcher = dynamic_cast<Researcher*>(*itr);
			if (tempResearcher)
			{
				if ((tempResearcher->allEssays.operator==(new_essay)))
					throw "This Essay already existes in for this researcher";
				tempResearcher->allEssays.operator+=(new_essay);
			}
		}
		catch (EmployeeExceptions & ex) { ex.print(); }
		catch (EssayExceptions & ex) { ex.print(); }
		catch (DateExceptions & ex) { ex.print(); }
		catch (const char* msg) { cout << msg << endl << endl; }
	}
	catch (const char* msg) { cout << msg << endl << endl; }
}
void Hospital::add_info_patient() throw (const char*)
{
	int id, day, month, year, yourChoise, fasting_status,room_num;
	Date new_d;
	std::string  med_name, department_name;
	VisitPurpose* visit_p;
	cout << "Please enter the Patient's id: ";
	cin >> id;
	set<Patient*, Patient_id>::iterator itr = AllPatient_hospital.find(new Patient("unknown", id, MIN_YEAR_BIRTH, Date(), 0));

	if (itr == AllPatient_hospital.end())
		throw "The patient wasn't found";
	cout << "The patient was found" << endl;
	cout << "Please enter the following Patient's  new information: " << endl;
	cout << "Please enter the date: (day month year):";
	cin >> day >> month >> year;
	try
	{
		new_d = Date(day, month, year);
		(*itr)->setVisitDate(new_d);
		cout << "What is the Visit's purpose?" << endl;
		cout << "Press 1 for Surgery" << endl;
		cout << "Press 2 for Examination" << endl;
		cout << "Your choise: ";
		cin >> yourChoise;
		if(yourChoise<1 || yourChoise >2)
			throw "You enterd a wrong input of choise.";
		if (yourChoise == 1)
		{
			cout << "Is the patient Fasting ?\nPress 1 if YES or 0 if NO" << endl;
			cout << "Your choise: ";
			cin >> fasting_status;
			cout << "Please enter the Surgery room number: ";
			cin >> room_num;
			visit_p = new Operation(room_num, fasting_status);
		}
		else
			visit_p = new Examination();
		(*itr)->TheVisitPurpose.pop_back();
		(*itr)->TheVisitPurpose.push_back(visit_p);
		cout << "Department: ";
		cin >> department_name;
		set<Department*, Dep_str>::iterator itr_dep = AllDepartments.find(new Department(department_name));
		if (itr_dep == AllDepartments.end())
			throw "This Department wasn't found in this hospital";
		//delete patient from department
		Erase_spesicfic_element((*itr)->TheDepartment[0]->AllPatients_department, new Patient("", id, MIN_YEAR_BIRTH, Date(), 0));
		// delete  department from patient
		(*itr)->TheDepartment.pop_back();
		//delete medic
		(*itr)->MedicalSupervisor.pop_back();
		//insert patient to dep
		(*itr_dep)->AllPatients_department.push_back(*itr);
		//insert dep to patient
		(*itr)->TheDepartment.push_back(*itr_dep);
		cout << "Please enter Medical responsible of the patient's name in the department: ";
		cin >> med_name;
		set<Employee*, Employee_str>::iterator itr_emp = AllWorkers_hospital.find(new MedWorker(med_name));
		if (itr_emp == AllWorkers_hospital.end()|| (*itr_emp)->getName() != department_name)
			throw "This Medical Worker wasn't found in this Department";
		(*itr)->MedicalSupervisor.push_back(*itr_emp);
	}
	catch (DateExceptions & ex) { ex.print(); }
	catch (PatientExceptions & ex) { ex.print(); }
	catch (OperationExceptions & ex) { ex.print(); }
	catch (EmployeeExceptions & ex) { ex.print(); }
	catch (DepartmentExceptions & ex) { ex.print(); }
	catch (const char* msg) { cout << msg << endl << endl; }
}
void Hospital::add_new_patient() throw (const char*)
{
	Date new_d;
	int id, birth_year, gender, day, month, year, fasting_status, room_num, yourChoise, answer;
	std::string new_name, med_name, department_name;
	VisitPurpose* visit_p;
		try
		{
			cout << "Did the Patient already been in this Hospital?\nPress 1 if YES or 0 if NO" << endl;
			cout << "Your choise: ";
			cin >> answer;
			if (answer <0 || answer>1)
				throw "You enterd a wrong input of choise.";
			if (answer)
				add_info_patient();
			else
			{
				//getting input from the user
				cout << "Please enter the following Patient's information: " << endl;
				cout << "Name: ";
				cin >> new_name;
				cout << "Id: ";
				cin >> id;
				cout << "Birth Year: ";
				cin >> birth_year;
				cout << "Gender(Press 0 for MALE or 1 for Female): ";
				cin >> gender;
				cout << "Please enter the date: (day month year):";
				cin >> day >> month >> year;
				new_d = Date(day, month, year);
				Patient* new_patient = new Patient(new_name, id, birth_year, new_d, gender);
				cout << "What is the Visit's purpose?" << endl;
				cout << "Press 1 for Surgery" << endl;
				cout << "Press 2 for Examination" << endl;
				cout << "Your choise: ";
				cin >> yourChoise;
				if (yourChoise<1 || yourChoise >2)
					throw "You enterd a wrong input of choise.";
				if (yourChoise == 1)
				{
					cout << "Is the patient Fasting ?\nPress 1 if YES or 0 if NO" << endl;
					cout << "Your choise: ";
					cin >> fasting_status;
					cout << "Please enter the Surgery room number: ";
					cin >> room_num;
					visit_p = new Operation(room_num, fasting_status);
				}
				else
					visit_p = new Examination();
				new_patient->TheVisitPurpose.push_back(visit_p);
				AllPatient_hospital.insert(new_patient);
				cout << "Department: ";
				cin >> department_name;
				set<Department*, Dep_str>::iterator itr = AllDepartments.find(new Department(department_name));
				if (itr == AllDepartments.end())
					throw "This Department wasn't found in this hospital";
				(*itr)->AllPatients_department.push_back(new_patient);
				new_patient->TheDepartment.push_back(*itr);
				cout << "Please enter Medical responsible of the patient's name in the department: ";
				cin >> med_name;
				set<Employee*, Employee_str>::iterator itr_emp = AllWorkers_hospital.find(new MedWorker(med_name));
				if (itr_emp == AllWorkers_hospital.end() || (*itr_emp)->getName() != department_name)
					throw "This Medical Worker wasn't found in this Department";
				new_patient->MedicalSupervisor.push_back(*itr_emp);
		}
	}
		catch (const char* msg) { cout << msg << endl << endl; }
		catch (DateExceptions & ex) { ex.print(); }
		catch (PatientExceptions & ex) { ex.print(); }
		catch (OperationExceptions & ex) { ex.print(); }
		catch (EmployeeExceptions & ex) { ex.print(); }
		catch (DepartmentExceptions & ex) { ex.print(); }
}
void Hospital::add_new_doctor()throw (const char*)
{
	Employee* new_Doctor;
	int  yourChoise = 0, NumofSurgeries;
	std::string new_name, new_skill, department_name;
	cout << "Please insert the new Doctors's following Information: " << endl;
	cout << "Name: ";
	cin >> new_name;
	cout << "Skill: ";
	cin >> new_skill;
	cout << "Would you like the Doctor to be a Surgeon or  a Researcher?" << endl;
	cout << "Press 0 for none" << endl;
	cout << "Press 1 for Surgeon" << endl;
	cout << "Press 2 for Reseacher" << endl;
	cout << "Press 3 for both" << endl;
	cout << "Your choise: ";
	cin >> yourChoise;
	try
	{
		if (yourChoise < 0 || yourChoise >3)
			throw "You enterd a wrong input of choise.";
		if (yourChoise == 1 || yourChoise == 3)
		{
			cout << "Please insert the new Surgeon's number of Surgeries: ";
			cin >> NumofSurgeries;
		}
		// swit case for the type of doctor
		switch (yourChoise)
		{
		case 0: new_Doctor = new Doctor(new_name, new_skill);
			break;
		case 1:new_Doctor = new Surgeon(new_name, new_skill, NumofSurgeries);
			break;
		case 2: new_Doctor = new DoctorReasearcher(new_name, new_skill);
			Institute[0]->AllResearchers.insert(new_Doctor);
			break;
		case 3: new_Doctor = new SurgeonResearcher(new_name, new_skill, NumofSurgeries);
			Institute[0]->AllResearchers.insert(new_Doctor);
			break;
		}
		AllWorkers_hospital.insert(new_Doctor);
		cout << "Department: ";
		cin >> department_name;
		set<Department*, Dep_str>::iterator itr = AllDepartments.find(new Department(department_name));
		if (itr == AllDepartments.end())
			throw "This Department wasn't found in this hospital";
		(*itr)->AllWorkers_department.push_back(new_Doctor);
		MedWorker* tempMedWorker = dynamic_cast<MedWorker*>(new_Doctor);
		if (tempMedWorker)
			tempMedWorker->theDepartment.push_back(*itr);
	}
	catch (EmployeeExceptions & ex) { ex.print(); }
	catch (DoctorExceptions & ex) { ex.print(); }
	catch (SurgeonExceptions & ex) { ex.print(); }
	catch (DepartmentExceptions & ex) { ex.print(); }
	catch (const char* msg) { cout << msg << endl << endl; }
}
void Hospital::add_new_nurse() throw (const char*)
{
	int year_exp;
	std::string new_name, department_name;
	cout << "Please insert the new Nurse's following Information: " << endl;
	cout << "Name: ";
	cin >> new_name;
	cout << "Years of experience: ";
	cin >> year_exp;
	try
	{
		Employee* new_nurse = new Nurse(new_name, year_exp);
		AllWorkers_hospital.insert(new_nurse);
		cout << "Department: ";
		cin >> department_name;
		set<Department*, Dep_str>::iterator itr = AllDepartments.find(new Department(department_name));
		if (itr == AllDepartments.end())
			throw "This Department wasn't found in this hospital";
		(*itr)->AllWorkers_department.push_back(new_nurse);
		MedWorker* tempMedWorker = dynamic_cast<MedWorker*>(new_nurse);
		if (tempMedWorker)
			tempMedWorker->theDepartment.push_back(*itr);

	}
	catch (EmployeeExceptions & ex) { ex.print(); }
	catch (NurseExceptions & ex) { ex.print(); }
	catch (DepartmentExceptions & ex) {ex.print();}
	catch (const char* msg) { cout << msg << endl << endl; }
}
void Hospital::add_Depart()
{
	std::string new_name;
	cout << "Please insert the Department's Name: ";
	cin >> new_name;
	try
	{
		Department*  new_departmnet = new  Department(new_name);
		AllDepartments.insert(new_departmnet);
	}
	catch (DepartmentExceptions & ex) { ex.print(); }
}
void Hospital::add_researcher()
{
	std::string researcher_name;
	cout << "Please insert the new Researcher's Name: ";
	cin >> researcher_name;
	try
	{
		Employee* new_researcher = new Researcher(researcher_name);
		Institute[0]->AllResearchers.insert(new_researcher);
	}
	catch (EmployeeExceptions & ex) { ex.print(); }
}
void Hospital::show_menu()const
{
	cout << "Press 1 for adding a new Department" << endl;
	cout << "Press 2 for adding a new Nurse" << endl;
	cout << "Press 3 for adding a new Doctor" << endl;
	cout << "Press 4 for adding a new Patient's Visit" << endl;
	cout << "Press 5 for adding a new Researcher" << endl;
	cout << "Press 6 for adding a new Essay to a specific Researcher" << endl;
	cout << "Press 7 for printing all the Patients in a specific Department" << endl;
	cout << "Press 8 for printing all the Medical workers in the hospital" << endl;
	cout << "Press 9 for printing all the Researchers in the institute" << endl;
	cout << "Press 10 for searching a Patient by Id" << endl;
	cout << "Press 11 for printing all the Researchers-Doctors in the Hospital" << endl;
	cout << "Press 12 for cmparing two Researchers by number of Essays" << endl;

	cout << endl;
}
void Hospital::print_patients_depart() const throw(const char*)
{
	std::string department_name;
	cout << "Please enter the Department of which  you would like to print: ";
	cin >> department_name;
	cout << endl;
	set<Department*, Dep_str>::iterator itr = AllDepartments.find(new Department(department_name));
	try
	{
		
		if (itr == AllDepartments.end())
			throw "This Department wasn't found in this hospital";
		if (!((*itr)->AllPatients_department.size()))
			throw" There are no patients in ths department";
		printCollection((*itr)->AllPatients_department);
	}
	catch (DepartmentExceptions & ex) { ex.print(); }
	catch (const char* msg) { cout << msg << endl << endl; }
}

void Hospital::print__single_patient() const throw(const char*)
{
	int id;
	try
	{
		if (!(AllPatient_hospital.size()))
			throw "There are no patients in this hospital";
		cout << "Please enter the  Patient's ID: ";
		cin >> id;
		set<Patient*, Patient_id>::iterator itr = AllPatient_hospital.find(new Patient("unknown", id, MIN_YEAR_BIRTH, Date(), MALE));
		if (itr == AllPatient_hospital.end())
			throw  "The patient wasn't found";
		cout << "The patient wasn't found" << endl;
		cout << "Patient's info: " << endl;
		cout << "Name: " << (*itr)->name.c_str() << endl;
		cout << "Visit purpose: " << typeid(*((*itr)->TheVisitPurpose[0])).name() + 6 << endl;
		if (!((*itr)->TheDepartment.size()))
			throw "No Department";
		cout << "Department of Visit: " << (*itr)->TheDepartment[0]->name.c_str() << endl;
		cout << endl;
	}
	catch (const char* msg) { cout << msg << endl << endl; }
	catch (PatientExceptions & ex) { ex.print(); }
}
void  Hospital::print_all_researchers_doctors() const throw(const char*)
{
	int flag = 0;
	set<Employee*, Employee_str>::iterator  itr = Institute[0]->AllResearchers.begin();
	set<Employee*, Employee_str>::iterator  itrEnd = Institute[0]->AllResearchers.end();
	try
	{
		if (itr == itrEnd)
			throw "There are no Researcher in the institute";
		for (; itr != itrEnd; ++itr)
		{
			if (typeid(**itr) != typeid(Researcher))
			{
				cout << **itr << endl;
				flag = 1;
			}
		}
		if (!flag)
			throw "There no Researcher-Doctors in this Hospital";
	}
	catch (const char* msg) { cout << msg << endl << endl; }
}
void Hospital::comparing_researcher_by_num_essays() const throw(const char*)
{
	try
	{
		if (Institute[0]->AllResearchers.size() <= 1)
			throw "There are not enought Researchers in the institute to do comparation.";
		std::string name_researcher1, name_researcher2;
		cout << "Please enter the names of the Researcher that you want to compare:" << endl;
		cout << "Name of the first Reasearcher:";
		cin >> name_researcher1;
		cout << "Name of the second Reasearcher:";
		cin >> name_researcher2;
		set<Employee*, Employee_str> ::iterator itr1 = Institute[0]->AllResearchers.find(new Researcher(name_researcher1));
		set<Employee*, Employee_str> ::iterator itr2 = Institute[0]->AllResearchers.find(new Researcher(name_researcher2));
		if (itr1 == Institute[0]->AllResearchers.end() || itr2 == Institute[0]->AllResearchers.end())
			throw "At least one of the Researchers wasn't fount in the Institute";
		else if (itr1 == itr2)
			throw "You can't compare a Researcher with it self";
		Researcher* tempResearcher1 = dynamic_cast<Researcher*>(*itr1);
		Researcher* tempResearcher2 = dynamic_cast<Researcher*>(*itr2);
		if (tempResearcher1 && tempResearcher2)
		{
			if (*tempResearcher1 > *tempResearcher2)
				cout << "Result: The first Researcher wrote more essays then the second Researcher" << endl;
			else
				cout << "Result: The first Researcher wrote less or the same number of essays like the second Researcher" << endl;
		}
	}
	catch (const char* msg) { cout << msg << endl << endl; }
	catch (EmployeeExceptions & ex) { ex.print(); }
}



