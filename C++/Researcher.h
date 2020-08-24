#ifndef __RESEARCHER_H
#define __RESEARCHER_H

// includes
#include "Essay.h"
#include "Employee.h"
#include "Array.h"
//decleration of class
class Researcher : virtual public Employee
{
protected:
	Array<Essay*> allEssays;

public:
	//C'tor
	Researcher(const std::string& name = "unknown"): Employee(name){}
	//copy C'tor
	Researcher(const Researcher& other);

	Array<Essay*> getallessays()  { return allEssays; }
	//printing f
	virtual void toOs(ostream& os) const override;

	//add + resizing f
	void add_essay(const std::string& name, const std::string& magazine, Date d) { allEssays += new Essay(d, magazine, name);}
	//  opertor = f
	const Researcher& Researcher::operator= (const Researcher& e);

	virtual Employee* clone() const override { return new Researcher(*this); }
	// > opertor f
	bool operator > (const  Researcher&  other) const;


	//files
	Researcher(ifstream& inFile);// c'tor that reads from file
	virtual void save(ofstream & outFile) const override;

	friend class Hospital;
};
#endif 
