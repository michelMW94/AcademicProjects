#include "Essay.h"
//c'tor
Essay::Essay(Date date, const std::string& Magazine, const std::string& EssayName) throw (EssayExceptions)
{
	if (EssayName == "")
		throw InvalidNameEssayExceptions(Magazine, EssayName);
	else if (Magazine == "")
		throw InvalidNameMagazineExceptions(Magazine, EssayName);
	setEssayName(EssayName);
	setMagazineName(Magazine);
	this->date = date;
}
//copy c'tor
Essay::Essay(const Essay& other): Magazine(""), EssayName("")
{
	*this = other;
}
//operator = f
const Essay& Essay::operator=(const Essay& other)
{
	if (this != &other)
	{
		setEssayName(other.getEssayName());
		setMagazineName(other.getMagazineName());
		date = other.date;
	}
	return *this;
}
//printing function
ostream& operator <<(ostream& os, const Essay& e)
{
	os << "Essay's information:" << endl;
	os << "Name: " << e.getEssayName().c_str() << endl;
	os << "Publishe Magazine: " << e.getMagazineName().c_str() << endl;
	os << e.getDate();
	return os;
}

//files

Essay * Essay::load_pointer(ifstream& inFile)
{
	Essay* loaded_essay = new Essay(inFile);
	return loaded_essay;
}
Essay::Essay(ifstream& inFile)
{

	//name
	int EssayNameLen;
	inFile.read((char*)& EssayNameLen, sizeof(EssayNameLen));
	char* temp = new char[EssayNameLen + 1];
	inFile.read((char*)temp, EssayNameLen);
	temp[EssayNameLen] = '\0';
	EssayName = (string)temp;
	delete[]temp;
	
	//magazine
	int MagazineLen;
	inFile.read((char*)& MagazineLen, sizeof(MagazineLen));
	char* temp2 = new char[MagazineLen + 1];
	inFile.read((char*)temp2, MagazineLen);
	temp2[MagazineLen] = '\0';
	Magazine = (string)temp2;
	delete[]temp2;
	//date
	date = Date(inFile);

}
void Essay::save(ofstream & outFile) const
{
	//name
	int EssayNameLen = strlen(EssayName.c_str());
	outFile.write((const char*)&EssayNameLen, sizeof(EssayNameLen));
	outFile.write((const char*)EssayName.c_str(), EssayNameLen);
	//magazine
	int MagazineLen = strlen(Magazine.c_str());
	outFile.write((const char*)&MagazineLen, sizeof(MagazineLen));
	outFile.write((const char*)Magazine.c_str(), MagazineLen);
	//date
	date.save_date(outFile);
}