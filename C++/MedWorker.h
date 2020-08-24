#ifndef __MEDWORKER_H
#define __MEDWORKER_H

// includes
#include "Employee.h"

//decleration of the class
class Department;
class MedWorker :  virtual public Employee
{
	static int num_of_workers;
protected:
	int workerNum;
	vector<Department*> theDepartment;
public:
	MedWorker(const std::string& name = "unknown");
	MedWorker(const MedWorker& other);
	//set f
	bool setWorkerNum(int workerNum);
	//Print f
	virtual void toOs(ostream& os) const override;

	//get f
	int getWorkerNum()    const { return workerNum; }

	// copy f
	const MedWorker& operator= (const MedWorker& e);
	virtual Employee* clone() const override { return new MedWorker(*this); }
	vector<Department*> getTheDepartment() const { return theDepartment; }

	//files
	MedWorker(ifstream& inFile) ;
	virtual void save(ofstream & outFile) const override;

	friend class Hospital;
};
#endif 


