#ifndef __SURGEONEXCEPTIONS_H
#define __SURGEONEXCEPTIONS_H

#include <iostream>
#pragma warning(disable:4290)

using namespace std;
//decleration of class
class SurgeonExceptions
{
protected:
	int NumofSurgery;
public:
	SurgeonExceptions(int NumofSurgery) {}
	virtual void print() const = 0;
};
class InvalidNumofSurgeryExceptions : public SurgeonExceptions
{
public:
	InvalidNumofSurgeryExceptions(int NumofSurgery) : SurgeonExceptions(NumofSurgery) {}
	virtual void print() const { cout << "Wrong input for Number of Surgeries of a Surgeon." << endl << endl; }
};
#endif 



