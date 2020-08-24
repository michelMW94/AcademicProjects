#ifndef __NURSE_H
#define __NURSE_H

// CONSTANTS DECLARATION
const int MIN_YEAR_EXP = 0;
const int MAX_YEAR_EXP = 100;

// includes
#include "MedWorker.h"
#include "NurseExceptions.h"
//decleration of the class
class Nurse : public MedWorker
{
protected:
	int Years_of_Exp;
public:
	Nurse(const std::string& name = "unknown", int YearsofExp = 0) throw(NurseExceptions);
	Nurse(const Nurse& other);//copy c'tor
	const Nurse& operator=(const Nurse& e);
	virtual void toOs(ostream& os) const override;

	// get f
	int getWorkerExp()    const { return Years_of_Exp; }

	virtual Employee* clone() const override { return new Nurse(*this); }

	//files
	Nurse(ifstream& inFile);// c'tor that reads from file
	virtual void save(ofstream & outFile) const override;


};
#endif 

