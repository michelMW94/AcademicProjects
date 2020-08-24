#include "VisitPurpose.h"
//print f
ostream& operator <<(ostream& os, const VisitPurpose& e)
{
	os << "Visit purpose: " << typeid(e).name() + 6 << endl;
	e.toOs(os);
	return os;
}