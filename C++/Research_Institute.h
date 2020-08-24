#ifndef __RESEARCH_INSTITUTE_H
#define __RESEARCH_INSTITUTE_H

// includes
#include "DoctorResearcher.h"
#include "SurgeonResearcher.h"


//decleration of class
class Research_Institute
{
	set<Employee*, Employee_str> AllResearchers;
public:
	//C'tor
	Research_Institute() {}
	// copy C'tor
	Research_Institute(const Research_Institute& other);
	//D'tor
	~Research_Institute(){}
	// get f
	set<Employee*, Employee_str> getAllResearchers() const { return AllResearchers; }
	//printing f
	const Research_Institute& operator=(const Research_Institute& i);// operator = f


	friend class Hospital;
};
#endif 

