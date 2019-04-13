//****************************************************************************************
//	INCLUDE FILES
//****************************************************************************************
#include <iostream>
#include "GateControl.hpp"
using namespace std;

//****************************************************************************************
//	CONSTANT DEFINITIONS
//****************************************************************************************

//****************************************************************************************
//	CLASSES, TYPEDEFS AND STRUCTURES
//****************************************************************************************

//****************************************************************************************
//	PUBLIC DATA
//****************************************************************************************
extern	string	gCurrentDate;

extern	string	gCurrentTime;
//****************************************************************************************
//	PRIVATE DATA
//****************************************************************************************

//****************************************************************************************
//	FUNCTION PROTOTYPES
//****************************************************************************************

//****************************************************************************************
//	GateControl::AccessAllowed
//****************************************************************************************
bool	GateControl::AccessAllowed(CardNumber number)
{
	return true;
}
//****************************************************************************************
//	GateControl::AddAuthorization
//****************************************************************************************
bool	GateControl::AddAuthorization(CardNumber number, const string& name,
									  const string& startTime, const string& endTime)
{
	Authorization a1(number, name, startTime, endTime);

	return true;
}
//****************************************************************************************
//	GateControl::ChangeAuthorization
//****************************************************************************************
bool	GateControl::ChangeAuthorization(CardNumber number, const string& name,
										 const string& startTime, const string& endTime)
{
	return false;
}
//****************************************************************************************
//	GateControl::DeleteAuthorization
//****************************************************************************************
bool	GateControl::DeleteAuthorization(CardNumber number)
{
	return false;
}
//****************************************************************************************
//	GateControl::GetAllAuthorizations
//****************************************************************************************
void	GateControl::GetAllAuthorizations(AuthorizationVector& authorizationVector)
{
	AuthorizationIterator	iterator;
	//iterator.begin() = authorizationVector;
	//return;
}
//****************************************************************************************
//	GateControl::GetAllTransactions
//****************************************************************************************
void	GateControl::GetAllTransactions(TransactionVector& transactionVector)
{
	//return false;
}
//****************************************************************************************
//	GateControl::GetCardAuthorization
//****************************************************************************************
bool	GateControl::GetCardAuthorization(CardNumber number, Authorization& authorization)
{
	return false;
}
//****************************************************************************************
//	GateControl::GetCardTransactions
//****************************************************************************************
bool	GateControl::GetCardTransactions(CardNumber number,
										 TransactionVector& transactionVector)
{
	return false;
}
