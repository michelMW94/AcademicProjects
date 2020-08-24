#ifndef __DOCTOR_H
#define __DOCTOR_H
// includes
#include "MedWorker.h"
#include "DoctorExceptions.h"
//decleration of the class
class Doctor : public MedWorker
{
protected:
	std::string skill;
public:
	//c'tor
	Doctor(const std::string& name = "unknown", const std::string& skill= "unknown") throw (DoctorExceptions);
	//set f
	void setSkill(const string&  skill) { this->skill = skill; }//set f

	// copy f
	virtual Employee* clone() const override { return new Doctor(*this); }
	//print f
	virtual void toOs(ostream& os) const override;

	//get f
	const string& getSkill()   const { return skill; }

	//files
	Doctor(ifstream& inFile);// c'tor that reads from file
	virtual void save(ofstream & outFile) const override;

};
#endif 

