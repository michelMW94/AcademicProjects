#include "Patient.h"
#include "Department.h"
#include"Employee.h"

// c'tor
Patient::Patient(const std::string name, int id, int year_of_birth, Date visit_date, int gender)throw(PatientExceptions)
{
	if (name == "")
		throw InvalidNamePatientExceptions(name, id, year_of_birth, gender);
	else if (id<MIN_ID || id>MAX_ID)
		throw InvalidIdPatientExceptions(name, id, year_of_birth, gender);
	else if (year_of_birth< MIN_YEAR_BIRTH)
		throw InvalidYearBirthPatientExceptions(name, id, year_of_birth, gender);
	else if (gender < MALE || (gender > FEMALE))
		throw InvalidGenderPatientExceptions(name, id, year_of_birth, gender);
	setName(name);
	this->id = id;
	this->year_of_birth = year_of_birth;
	this->p_gender = (Gender)gender;
	this->visit_date = visit_date;
}
//copy c'tor
Patient::Patient(const Patient& other) 
{
	*this = other;
}
//
const Patient& Patient::operator=(const Patient& p)
{

	if (this != &p)
	{
		id = p.getId();
		year_of_birth = p.getBirthYear();
		visit_date = p.getVisitDate();
		p_gender = p.getGender();
		TheDepartment = p.TheDepartment;
		MedicalSupervisor = p.MedicalSupervisor;
	}
	return *this;
}

//print f
ostream& operator <<(ostream& os, const Patient& e)
{
	os << "Patient's information:" << endl;
	os << "Name: " << e.getName().c_str() << endl;
	os << "ID: " << e.getId() << endl;
	os << "Birth year: " << e.getBirthYear() << endl;
	os << "Gender: " << e.genders[(int)e.getGender()] << endl;
	os << e.getVisitDate();
	return os;
}

Patient::Patient(ifstream& inFile)
{

}
void Patient::save(ofstream & outFile) const
{
	//name
	int len = strlen(name.c_str());
	outFile.write((const char*)&len, sizeof(len));
	outFile.write((const char*)name.c_str(), len);
	//id
	outFile.write((const char*)& id, sizeof(id));
	//birth year
	outFile.write((const char*)& year_of_birth, sizeof(year_of_birth));
	//date
	visit_date.save_date(outFile);
	//gender
	int gender_save = (int)p_gender;
	outFile.write((const char*)& gender_save, sizeof(gender_save));
	//visit purpose

}
