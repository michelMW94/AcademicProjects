#include "Surgeon.h"

Surgeon::Surgeon(const std::string& name, const std::string& skill, int NumofSurgery)throw (SurgeonExceptions) : Employee(name), Doctor(name, skill)
{
	if (NumofSurgery <MIN_NUM_SUR || NumofSurgery>MAX__NUM_SUR)
		throw InvalidNumofSurgeryExceptions(NumofSurgery);
	this->NumofSurgery = NumofSurgery;
}
Surgeon::Surgeon(const Surgeon& other) : Employee(other), Doctor(other)
{
	*this = other;
}
const Surgeon& Surgeon::operator= (const Surgeon& s)
{
	if (this != &s)
		this->NumofSurgery = s.NumofSurgery;
	return *this;
}
void Surgeon::toOs(ostream& os) const
{
	Doctor::toOs(os);
	os << "Num of Surgeries: " << NumofSurgery << endl;

}

//files
Surgeon::Surgeon(ifstream& inFile) : Employee(inFile), Doctor(inFile)
{
	inFile.read((char*)&NumofSurgery, sizeof(NumofSurgery));
}
void Surgeon::save(ofstream & outFile) const
{
	Doctor::save(outFile);
	outFile.write((const char*)& NumofSurgery, sizeof(NumofSurgery));
}