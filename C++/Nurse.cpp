#include "Nurse.h"


//c'tor
Nurse::Nurse(const std::string& name, int Years_of_Exp)
	:Employee(name), MedWorker(name)
{
	if (Years_of_Exp< MIN_YEAR_EXP || Years_of_Exp > MAX_YEAR_EXP)
		throw InvalidYearsofExperienceExceptions(Years_of_Exp);
	this->Years_of_Exp = Years_of_Exp;
}
//copy c'tor
Nurse::Nurse(const Nurse& other) : Employee(other), MedWorker(other)
{
	*this = other;
}

const Nurse& Nurse::operator=(const Nurse& e)
{

	if (this != &e)
		this->Years_of_Exp = e.getWorkerExp();
	return *this;
}


//printing function
void Nurse::toOs(ostream& os) const
{
	MedWorker::toOs(os);
	os << "Years of Experience: " << Years_of_Exp << endl;
}

//files
Nurse::Nurse(ifstream& inFile) : Employee(inFile), MedWorker(inFile)
{
	inFile.read((char*)& Years_of_Exp, sizeof(Years_of_Exp));
}
void Nurse::save(ofstream & outFile) const
{
	MedWorker::save(outFile);
	outFile.write((const char*)& Years_of_Exp, sizeof(Years_of_Exp));
}