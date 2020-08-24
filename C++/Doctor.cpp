#include "Doctor.h"


//c'tor
Doctor::Doctor(const std::string& name, const std::string& skill) throw (DoctorExceptions)
	:Employee(name), MedWorker(name)
{
	if (skill == "")
		throw InvalidSkillDoctorExceptions(skill);
	setSkill(skill);
}
//printing function
void Doctor::toOs(ostream& os) const
{
	MedWorker::toOs(os);
	os << "Skill: " << skill.c_str() << endl;
}

//files
Doctor::Doctor(ifstream& inFile) : Employee(inFile), MedWorker(inFile)
{
	int skillLen;
	inFile.read((char*)& skillLen, sizeof(skillLen));
	char * temp = new char[skillLen + 1];
	inFile.read((char*)temp, skillLen);
	temp[skillLen] = '\0';
	skill = (string)temp;
	delete[] temp;
}
void Doctor::save(ofstream & outFile) const
{
	MedWorker::save(outFile);
	int len = strlen(skill.c_str());
	outFile.write((const char*)&len, sizeof(len));
	outFile.write((const char*)skill.c_str(), len);
}