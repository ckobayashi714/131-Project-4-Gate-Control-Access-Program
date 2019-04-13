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
									  const string& startTime, const string& endTime) {
	Authorization a1(number, name, startTime, endTime);
	AuthorizationIterator temp;
	temp = authorizationMap_.find(a1.number_);
	if (temp == authorizationMap_.end()) {
		authorizationMap_.emplace(number, a1);
		return true;
	}
	else
		return false;
}
//****************************************************************************************
//	GateControl::ChangeAuthorization
//****************************************************************************************
bool	GateControl::ChangeAuthorization(CardNumber number, const string& name,
										 const string& startTime, const string& endTime)
{
	AuthorizationIterator temp;
	temp = authorizationMap_.find(number);
	if (temp == authorizationMap_.end())
		return false;
  else
		return true;
}
//****************************************************************************************
//	GateControl::DeleteAuthorization
//****************************************************************************************
bool	GateControl::DeleteAuthorization(CardNumber number) {
	AuthorizationIterator temp;
	temp = authorizationMap_.find(number);
	if (temp == authorizationMap_.end()) {
		return false;
	}
	else {
		authorizationMap_.erase(temp);
		return true;
	}
}
//****************************************************************************************
//	GateControl::GetAllAuthorizations
//****************************************************************************************
void	GateControl::GetAllAuthorizations(AuthorizationVector& authorizationVector) {
	AuthorizationIterator	iterator;
	iterator = authorizationMap_.begin();
	authorizationVector.clear();
	if (authorizationMap_.empty())
		return;
	for (; iterator != authorizationMap_.end(); ++iterator){
		authorizationVector.push_back(iterator->second);
	}
}
//****************************************************************************************
//	GateControl::GetAllTransactions
//****************************************************************************************
void	GateControl::GetAllTransactions(TransactionVector& transactionVector) {
	//return false;
}
//****************************************************************************************
//	GateControl::GetCardAuthorization
//****************************************************************************************
bool	GateControl::GetCardAuthorization(CardNumber number, Authorization& authorization) {
		AuthorizationIterator temp;
		temp = authorizationMap_.find(number);
		if (temp == authorizationMap_.end())
			return false;
		else
			authorization = authorizationMap_.at(number);
			return true;
}
//****************************************************************************************
//	GateControl::GetCardTransactions
//****************************************************************************************
bool	GateControl::GetCardTransactions(CardNumber number,
										 TransactionVector& transactionVector) {
	return false;
}
