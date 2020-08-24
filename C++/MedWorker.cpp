#include "MedWorker.h"

int MedWorker::num_of_workers = 1;
MedWorker::MedWorker(const std::string& name) :Employee(name)
{
	setWorkerNum(num_of_workers);
	num_of_workers++;
}
MedWorker::MedWorker(const MedWorker& other) : Employee(other)
{
	*this = other;
}
//set f
bool MedWorker::setWorkerNum(int workerNum)
{
	this->workerNum = workerNum;
	return true;
}
const MedWorker& MedWorker::operator= (const MedWorker& e)
{
	if (this != &e)
	{
		setWorkerNum(e.getWorkerNum());
		theDepartment = e.theDepartment;
	}
	return *this;
}
void MedWorker::toOs(ostream& os) const
{
	os << "Worker's number: " << workerNum << endl;
	
}

//files
MedWorker::MedWorker(ifstream& inFile) : Employee(inFile)
{
	inFile.read((char*)& workerNum, sizeof(workerNum));
}
void  MedWorker::save(ofstream & outFile) const
{
	Employee::save(outFile);
	outFile.write((const char*)& workerNum, sizeof(workerNum));
}