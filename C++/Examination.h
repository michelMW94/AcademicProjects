#ifndef __EXAMINATION_H
#define __EXAMINATION_H

// includes
#include "VisitPurpose.h"
//decleration of the class
class Examination : public VisitPurpose
{
public:
	Examination(){}//c'tor
	Examination(const Examination& other) {}//copy c'tor
	virtual~Examination() {}// d'tor
	virtual void toOs(ostream& os) const override {}//print f
	virtual VisitPurpose* clone() const override { return new Examination(*this); }//copy f


};
#endif 
