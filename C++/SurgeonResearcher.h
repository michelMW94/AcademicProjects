#ifndef __SERGEONRESEARCHER_H
#define __SERGEONRESEARCHER_H
// includes
#include "Surgeon.h"
#include "Researcher.h"

//decleration of the class
class SurgeonResearcher :public Surgeon, public Researcher
{
public:
	SurgeonResearcher(const std::string& name = "unknown", const std::string& skill = "unknown", int NumofSurgery = 0) //c'tor
		:Employee(name), Surgeon(name, skill, NumofSurgery), Researcher(name) {}
	SurgeonResearcher(const SurgeonResearcher& other)// copy c'tor
		: Employee(other), Surgeon(other), Researcher(other) {}
	virtual void toOs(ostream& os) const override;// print f
	virtual Employee* clone() const override { return new SurgeonResearcher(*this); }// copy f


	 //files
	SurgeonResearcher(ifstream& inFile);// c'tor that reads from file
	virtual void save(ofstream & outFile) const override;
};
#endif 
