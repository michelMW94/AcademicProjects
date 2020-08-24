#include "SurgeonResearcher.h"
void SurgeonResearcher::toOs(ostream& os) const
{
	Surgeon::toOs(os);
	Researcher::toOs(os);
}

//files
SurgeonResearcher::SurgeonResearcher(ifstream& inFile) :Employee(inFile), Surgeon(inFile), Researcher(inFile) {}
void SurgeonResearcher::save(ofstream & outFile) const
{
	Surgeon::save(outFile);
	Researcher::allEssays.save_arr(outFile);
}