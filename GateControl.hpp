#pragma once

//****************************************************************************************
//
//	INCLUDE FILES
//
//****************************************************************************************
#include	<iostream>
#include	<map>
#include	<vector>

using namespace std;

//****************************************************************************************
//
//	CONSTANT DEFINITIONS
//
//****************************************************************************************

//****************************************************************************************
//
//	CLASSES, TYPEDEFS AND STRUCTURES
//
//****************************************************************************************
typedef uint32_t	CardNumber;

typedef uint32_t	GateNumber;

struct	Authorization
{
	Authorization() { }
	
	Authorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
	: number_(number), name_(name), startTime_(startTime), endTime_(endTime) { }

	CardNumber	number_;

	string		name_;
	
	string		startTime_;
	
	string		endTime_;
};

typedef map<CardNumber, Authorization>	AuthorizationMap;
typedef	AuthorizationMap::iterator		AuthorizationIterator;

typedef	vector<Authorization>	AuthorizationVector;

struct	Transaction
{
	Transaction() { }

	Transaction(CardNumber number, const string& name, const string& date, const string& time,
				bool accessAllowed)
	: number_(number), name_(name), date_(date), time_(time), accessAllowed_(accessAllowed) { }

	CardNumber	number_;
	
	string		name_;
	
	string		date_;

	string		time_;
	
	bool		accessAllowed_;
};

typedef	vector<Transaction>	TransactionVector;

class	GateControl
{
	public:
		bool	AccessAllowed(CardNumber number);
	
		bool	AddAuthorization(CardNumber number, const string& name,
								 const string& startTime, const string& endTime);
		
		bool	ChangeAuthorization(CardNumber number, const string& name,
										const string& startTime, const string& endTime);
		
		bool	DeleteAuthorization(CardNumber number);
		
		void	GetAllAuthorizations(AuthorizationVector& authorizationVector);
		
		void	GetAllTransactions(TransactionVector& transactionVector);
	
		bool	GetCardAuthorization(CardNumber number, Authorization& authorization);

		bool	GetCardTransactions(CardNumber number, TransactionVector& transactionVector);

	private:
		AuthorizationMap	authorizationMap_;
		
		TransactionVector	transactionVector_;
};

//****************************************************************************************
//
//	FUNCTION PROTOTYPES
//
//****************************************************************************************


