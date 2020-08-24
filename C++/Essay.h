#ifndef __ESSAY_H
#define __ESSAY_H

// includes
#include "Date.h"
#include "EssayExceptions.h"

// decleration of class
class Essay
{
	Date date;
	std::string Magazine, EssayName;
public:
	//C'tor
	Essay(Date date = Date(), const std::string& Magazine = "unknown", const std::string& EssayName = "unknown")
		throw (EssayExceptions);
	//copy C'tor
	Essay(const Essay& other);
	//D'tor

	//set f
	void setMagazineName(const string&  Magazine) { this->Magazine = Magazine; }
	void setEssayName(const string& EssayName) { this->EssayName = EssayName; }
	//get f
	const string& getMagazineName()   const { return Magazine; }
	const string& getEssayName()   const { return EssayName; };
	Date getDate() const { return date; }

	// operator =
	const Essay& operator=(const Essay& other);

	//printing f
	friend ostream& operator <<(ostream& os, const Essay& e);

	//operator == 
	bool operator==(const Essay& other)const { return (EssayName == other.EssayName); }


	//files
	Essay * load_pointer(ifstream& inFile);
	Essay(ifstream& inFile);// c'tor that reads from file
	void save(ofstream & outFile) const;
	
	friend class Researcher;

};
#endif 
