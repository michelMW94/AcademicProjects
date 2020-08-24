#ifndef __OPERATION_H
#define __OPERATION_H

// includes
#include "VisitPurpose.h"
#include "OperationExceptions.h"
// CONSTANTS DECLARATION
const int MIN_ROOM_NUM = 1;
typedef enum { YES, NO } ISFASTING;
//decleration of the class
class Operation : public VisitPurpose
{
	int num_operation_room;
	ISFASTING p_fasting_status;
public:
	const char* isFasting[NAME_LENGTH] = { "Yes", "No" };
	Operation(int num_operation_room =1, int p_fasting_status =NO) throw (OperationExceptions);// c'tor
	Operation(const Operation& other);//copy c'tor
	virtual~Operation() {}//d'tor
	 //set f
	void  setOperationRoomNum(int num_operation_room);
	void  setFastingStatus(ISFASTING p_fasting_status);
	
	const Operation& operator= (const Operation& e);
	virtual void toOs(ostream& os) const override;

	//get f
	int getOperationRoomNum()    const { return num_operation_room; }
	ISFASTING getFastingStatus()    const { return p_fasting_status; }

	//copy f
	virtual VisitPurpose* clone() const override { return new Operation(*this); }


};
#endif 

