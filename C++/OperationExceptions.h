#ifndef __OPERATIONEXCEPTIONS_H
#define __OPERATIONEXCEPTIONS_H

#include <iostream>
#include <string.h>
#include "Date.h"
#pragma warning(disable:4290)

using namespace std;
//decleration of class
class OperationExceptions
{
protected:
	int num_operation_room;
	int p_fasting_status;
public:
	OperationExceptions(int num_operation_room, int p_fasting_status) {}
	virtual void print() const = 0;
};
class InvalidRoomNumExceptions : public OperationExceptions
{
public:
	InvalidRoomNumExceptions(int num_operation_room, int p_fasting_status) : OperationExceptions(num_operation_room, p_fasting_status) {}
	virtual void print() const { cout << "Wrong input for Operation Room number of an Operation." << endl << endl; }
};
class InvalidFastingStatusExceptions : public OperationExceptions
{
public:
	InvalidFastingStatusExceptions(int num_operation_room, int p_fasting_status) : OperationExceptions(num_operation_room, p_fasting_status) {}
	virtual void print() const { cout << "Wrong input for Fasting Status of an Operation." << endl << endl; }
};
#endif 
