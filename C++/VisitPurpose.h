#ifndef __VISITPURPOSE_H
#define __VISITPURPOSE_H
// includes
#include "Date.h"
//decleration of the class
class VisitPurpose
{
public:
	VisitPurpose(){}
	VisitPurpose(const VisitPurpose& other) {}
	virtual~VisitPurpose() {};//d'or
	virtual void toOs(ostream& os) const {}
	friend ostream& operator <<(ostream& os, const VisitPurpose& e);// opertor ostream f
	virtual VisitPurpose* clone() const = 0;
};
#endif 
