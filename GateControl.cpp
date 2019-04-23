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
//  This function will validate access to a card's number. The attempt will be logged
//  regarless if access is allowed or denied.
//****************************************************************************************

bool	GateControl::AccessAllowed(CardNumber number) {
	AuthorizationIterator temp;
	temp = authorizationMap_.find(number);

	if (temp == authorizationMap_.end()){
		Transaction t1(number, "***", gCurrentDate, gCurrentTime, false);
		transactionVector_.push_back(t1);
		return false;
	}
	bool passed = false;
	if ((temp->second.startTime_ >= gCurrentTime) && (temp->second.endTime_ <= gCurrentTime))
		passed = true;
	Transaction t2(number, temp->second.name_ , gCurrentDate, gCurrentTime, passed);
	transactionVector_.push_back(t2);
	return true;
}

//****************************************************************************************
//	GateControl::AddAuthorization
//  This function will check to see if a card number already exists, if not the
//  new card number will be added to list.
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
	return false;
}

//****************************************************************************************
//	GateControl::ChangeAuthorization
//  This function will search for a card number, when it finds it, it will update the user's
//  name, start time, and end time. If no card number is found, nothing gets updated.
//****************************************************************************************

bool	GateControl::ChangeAuthorization(CardNumber number, const string& name,
										 const string& startTime, const string& endTime) {
	AuthorizationIterator temp;
	temp = authorizationMap_.find(number);
	if (temp == authorizationMap_.end())
		return false;
	temp->second.name_ = name;
	temp->second.startTime_ = startTime;
	temp->second.endTime_ = endTime;
	return true;
}

//****************************************************************************************
//	GateControl::DeleteAuthorization
//  This function will search for a card number, when it finds it, it will delete the card
//  number and the authorization attached to it. If no card number is found, nothing gets
//  deleted.
//****************************************************************************************

bool	GateControl::DeleteAuthorization(CardNumber number) {
	AuthorizationIterator temp;
	temp = authorizationMap_.find(number);
	if (temp == authorizationMap_.end())
		return false;
	authorizationMap_.erase(temp);
	return true;
}

//****************************************************************************************
//	GateControl::GetAllAuthorizations
//  This function will receive all the authorization records. It will traverse the
// 	authorization map and copy each element into the vector.
//****************************************************************************************

void	GateControl::GetAllAuthorizations(AuthorizationVector& authorizationVector) {
	AuthorizationIterator	iterator;
	iterator = authorizationMap_.begin();
	authorizationVector.clear();
	if (authorizationMap_.empty())
		return;
	for (; iterator != authorizationMap_.end(); ++iterator)
		authorizationVector.push_back(iterator->second);
}

//****************************************************************************************
//	GateControl::GetAllTransactions
//  This function will receive the complete set of the transaction records. It will first
//  check to see if the transaction vector is empty, if so the vector will be cleared.
//  If not, it will assign the contents to the vector.
//****************************************************************************************

void	GateControl::GetAllTransactions(TransactionVector& transactionVector) {
	if (transactionVector_.empty())
		transactionVector.clear();
	else
		transactionVector.assign(transactionVector_.begin(), transactionVector_.end());
}

//****************************************************************************************
//	GateControl::GetCardAuthorization
//  This function will search for a card number's authorization. If no card number is
//  found, then no authorization exists.
//****************************************************************************************

bool	GateControl::GetCardAuthorization(CardNumber number, Authorization& authorization) {
		AuthorizationIterator temp;
		temp = authorizationMap_.find(number);
		if (temp == authorizationMap_.end())
			return false;
		authorization = authorizationMap_[number];
		return true;
}

//****************************************************************************************
//	GateControl::GetCardTransactions
//  This function will receive the transaction records for the specified card number.
//  It will search the vector and store the transaction each time the card number is found.
//  If the vector is empty, it will clear the vector.
//****************************************************************************************

bool	GateControl::GetCardTransactions(CardNumber number,
										 TransactionVector& transactionVector) {
	TransactionVector::iterator it = transactionVector_.begin();
	if (transactionVector_.empty()){
		transactionVector.clear();
		return false;
	}
	for (; it < transactionVector_.end(); ++it) {
		if (it->number_ == number)
			transactionVector.push_back(*it);
	}
	return true;
}
