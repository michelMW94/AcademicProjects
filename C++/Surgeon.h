#ifndef __SERGEON_H
#define __SERGEON_H

// CONSTANTS DECLARATION
const int MIN_NUM_SUR = 0;
const int MAX__NUM_SUR = 100000;
// includes
#include "Doctor.h"
#include "SurgeonExceptions.h"

//decleration of the class
class Surgeon :public Doctor
{
protected:
	int NumofSurgery;

public:
	Surgeon(const std::string& name = "unknown", const std::string& skill = "unknown", int NumofSurgery=0) 
		throw (SurgeonExceptions);// c'tor
	Surgeon(const Surgeon& other);// copy c'tor
						 // print f
	virtual void toOs(ostream& os) const override;
	//get f
	int getNumofSurgery()    const { return NumofSurgery; }

	//copy f
	const Surgeon& operator= (const Surgeon& s);
	virtual Employee* clone() const override { return new Surgeon(*this); }

	//files
	Surgeon(ifstream& inFile);// c'tor that reads from file
	virtual void save(ofstream & outFile) const override;
};
#endif 


