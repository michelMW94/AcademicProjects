#include "Operation.h"

Operation::Operation(int num_operation_room, int p_fasting_status) throw (OperationExceptions)
{
	if (num_operation_room < MIN_ROOM_NUM)
		throw InvalidRoomNumExceptions(num_operation_room, p_fasting_status);
	else if (p_fasting_status<YES || p_fasting_status>NO)
		throw InvalidFastingStatusExceptions(num_operation_room, p_fasting_status);

	setFastingStatus((ISFASTING)p_fasting_status);
	setOperationRoomNum(num_operation_room);
}
Operation::Operation(const Operation& other)
{
	*this = other;
}
//set f
void  Operation::setFastingStatus(ISFASTING p_fasting_status)
{
	this->p_fasting_status = p_fasting_status;
}
void  Operation::setOperationRoomNum(int num_operation_room)
{
	this->num_operation_room = num_operation_room;
}
const Operation& Operation::operator= (const Operation& e)
{
	if (this != &e)
	{
		setOperationRoomNum(e.getOperationRoomNum());
		setFastingStatus(e.getFastingStatus());
	}
	return *this;
}
void Operation::toOs(ostream& os) const
{
	os << "Fasting Status: " << isFasting[(int)getFastingStatus()] << endl;
	os << "Operation room number:" << getOperationRoomNum() << endl;
}