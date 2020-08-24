#include "Researcher.h"
#include <iostream>
#include "Date.h"
// copy c'tor
Researcher::Researcher(const Researcher& other) : Employee(other)
{
	*this = other;
}
//printing function
void Researcher::toOs(ostream& os) const
{
	if (!(allEssays.getlogicalSize()))
		os << "No available Essayes" << endl;
	else
	{
		os << allEssays << endl;
	}
}
// operator = f
const Researcher& Researcher::operator= (const Researcher& e)
{

	if (this != &e)
	{
		allEssays = e.allEssays;
	}
	return *this;
}
bool Researcher::operator > (const  Researcher&  other) const
{
	return (allEssays.getlogicalSize() > other.allEssays.getlogicalSize());
}
//files
Researcher::Researcher(ifstream& inFile) :Employee(inFile)
{
	allEssays.load_arr(inFile);
}
void  Researcher::save(ofstream & outFile) const
{
	Employee::save(outFile);
	allEssays.save_arr(outFile);
}