#ifndef __DOCTORRESEARCHER_H
#define __DOCTORRESEARCHER_H

// includes
#include "Doctor.h"
#include "Researcher.h"
//decleration of the class
class DoctorReasearcher : public Doctor, public Researcher
{
public:
	DoctorReasearcher(const std::string& name = "unknown", const std::string& skill = "unknown") : Employee(name), Doctor(name, skill), Researcher(name) {}//c'tor
	DoctorReasearcher(const DoctorReasearcher& other) : Employee(other), Doctor(other), Researcher(other) {}//copy c'tor
	virtual void toOs(ostream& os) const override;	// print f
	virtual Employee* clone() const override { return new DoctorReasearcher(*this); }// copy f

	//files
	DoctorReasearcher(ifstream& inFile);// c'tor that reads from file
	virtual void save(ofstream & outFile) const override;
};
#endif 
