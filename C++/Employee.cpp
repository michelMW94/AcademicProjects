#include "Employee.h"

Employee::Employee(const std::string&  name) throw (EmployeeExceptions)
{
	if (name == "")
		throw InvalidNameEmployeeExceptions(name);
	setName(name);
}
ostream& operator <<(ostream& os, const Employee& e)
{
	os <<"Postion: "<< typeid(e).name() + 6 << endl;
	os << "Name: " << e.name.c_str() << endl;
	e.toOs(os);
	return os;
}
bool Employee::operator==(const Employee& e) const
{
	if (name.compare(e.getName()) == 0)
		return true;
	else
		return false;
}


// files
void  Employee::saveTYPE(ofstream & outFile) const
{
	EmployeeGenerator::EmployeeType type = EmployeeGenerator::getType(this);
	outFile.write((const char*)&type, sizeof(EmployeeGenerator::EmployeeType));
}
Employee::Employee(ifstream& inFile) 
{
	int nameLen;
	inFile.read((char*)& nameLen, sizeof(nameLen));
	char * temp = new char[nameLen + 1];
	inFile.read((char*)temp, nameLen);
	temp[nameLen] = '\0';
	name = (string)temp;
	delete[] temp;
}
void  Employee::save(ofstream & outFile) const
{
	int len = strlen(name.c_str());
	outFile.write((const char*)&len, sizeof(len));
	outFile.write((const char*)name.c_str(), len);
}
