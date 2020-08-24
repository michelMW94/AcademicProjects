#include "DoctorResearcher.h"
void DoctorReasearcher::toOs(ostream& os) const
{
	Doctor::toOs(os);
	Researcher::toOs(os);
}
DoctorReasearcher::DoctorReasearcher(ifstream& inFile) : Employee(inFile), Doctor(inFile), Researcher(inFile) {}
void DoctorReasearcher::save(ofstream & outFile) const
{
	Doctor::save(outFile);
	Researcher::allEssays.save_arr(outFile);
}