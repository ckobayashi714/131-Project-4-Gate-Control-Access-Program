//****************************************************************************************
//
//	INCLUDE FILES
//
//****************************************************************************************
#include	<iostream>

#include	"GateControl.hpp"

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

//****************************************************************************************
//
//	PUBLIC DATA
//
//****************************************************************************************
	string	gCurrentDate;

	string	gCurrentTime;

//****************************************************************************************
//
//	PRIVATE DATA
//
//****************************************************************************************

//****************************************************************************************
//
//	FUNCTION PROTOTYPES
//
//****************************************************************************************
bool	CompareAuthorizations(AuthorizationVector& actualVector,
							  AuthorizationVector& expectedVector,
							  ostream& stream);

bool	CompareTransactions(TransactionVector& actualVector,
							TransactionVector& expectedVector,
							ostream& stream);

void	ShowAuthorizations(ostream& stream, AuthorizationVector& authorizationVector);

void	ShowTransactions(ostream& stream, TransactionVector& transactionVector);

uint64_t	TestAccess();

uint64_t	TestAdd();

uint64_t	TestCard();

uint64_t	TestChange();

uint64_t	TestDelete();

//****************************************************************************************
//
//	MAIN PROGRAM
//
//****************************************************************************************
int main (int argc, char * const argv[])
{
	//************************************************************************************
	//	LOCAL DATA
	uint64_t			score;
	
	TransactionVector	transactionVector;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	score = 0;
	
	score += TestAdd();
	
	score += TestDelete();
	
	score += TestChange();
	
	score += TestAccess();
	
	score += TestCard();
	
	cout << endl << "Total score: " << score << "/80" << endl;
	
	cout << endl << "** Finished **" << endl;

	return(0);
}

//****************************************************************************************
//
//	CompareAuthorizations
//
//****************************************************************************************
bool	CompareAuthorizations(AuthorizationVector& actualVector,
							  AuthorizationVector& expectedVector,
							  ostream& stream)
{
	//************************************************************************************
	//	LOCAL DATA
	bool	good;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	good = true;
	if (actualVector.size() == expectedVector.size())
	{
		for (uint64_t i = 0; i < actualVector.size(); ++i)
		{
			if ((actualVector[i].number_ != expectedVector[i].number_)
				||
				(actualVector[i].name_ != expectedVector[i].name_)
				||
				(actualVector[i].startTime_ != expectedVector[i].startTime_)
				||
				(actualVector[i].endTime_ != expectedVector[i].endTime_))
			{
				stream << "Authorizations don't match" << endl;
				good = false;
			}
		}
	}
	else
	{
		stream << "Sizes don't match" << endl;
		good = false;
	}
	
	if (!good)
	{
		stream << "Actual:"<< endl;
		ShowAuthorizations(stream, actualVector);

		stream << "Expected:"<< endl;
		ShowAuthorizations(stream, expectedVector);
	}

	return(good);
}

//****************************************************************************************
//
//	CompareTransactions
//
//****************************************************************************************
bool	CompareTransactions(TransactionVector& actualVector,
							TransactionVector& expectedVector,
							ostream& stream)
{
	//************************************************************************************
	//	LOCAL DATA
	bool	good;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	good = true;
	if (actualVector.size() == expectedVector.size())
	{
		for (uint64_t i = 0; i < actualVector.size(); ++i)
		{
			if ((actualVector[i].number_ != expectedVector[i].number_)
				||
				(actualVector[i].name_ != expectedVector[i].name_)
				||
				(actualVector[i].date_ != expectedVector[i].date_)
				||
				(actualVector[i].time_ != expectedVector[i].time_))
			{
				stream << "Transactions don't match" << endl;
				good = false;
			}
		}
	}
	else
	{
		stream << "Sizes don't match" << endl;
		good = false;
	}
	
	if (!good)
	{
		stream << "Actual:"<< endl;
		ShowTransactions(stream, actualVector);
		
		stream << "Expected:"<< endl;
		ShowTransactions(stream, expectedVector);
	}
	
	
	return(good);
}

//****************************************************************************************
//
//	ShowAuthorizations
//
//****************************************************************************************
void	ShowAuthorizations(ostream& stream, AuthorizationVector& authorizationVector)
{
	//************************************************************************************
	//	LOCAL DATA
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	if (!authorizationVector.empty())
	{
		for (uint64_t i = 0; i < authorizationVector.size(); ++i)
		{
			stream << i << ": "
			<< " " << authorizationVector[i].number_
			<< " " << authorizationVector[i].name_
			<< " " << authorizationVector[i].startTime_
			<< " " << authorizationVector[i].endTime_ << endl;
		}
	}
	else
	{
		stream << "<empty>" << endl;
	}
	
	stream << endl;
	
	return;
}

//****************************************************************************************
//
//	ShowTransactions
//
//****************************************************************************************
void	ShowTransactions(ostream& stream, TransactionVector& transactionVector)
{
	//************************************************************************************
	//	LOCAL DATA
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	if (!transactionVector.empty())
	{
		for (uint64_t i = 0; i < transactionVector.size(); ++i)
		{
			stream << i << ": "
			<< " " << transactionVector[i].number_
			<< " " << transactionVector[i].name_
			<< " " << transactionVector[i].date_
			<< " " << transactionVector[i].time_
			<< " " << boolalpha << transactionVector[i].accessAllowed_ << endl;
		}
	}
	else
	{
		stream << "<empty>" << endl;
	}
	
	stream << endl;
	
	return;
}

//****************************************************************************************
//
//	TestAccess
//
//****************************************************************************************
uint64_t	TestAccess()
{
	//************************************************************************************
	//	LOCAL DATA
	TransactionVector	actualVector;
	
	TransactionVector	expectedVector;
	
	GateControl			gateControl;
	
	bool				good;
	
	uint64_t			score;
	
	bool				success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Testing Access" << endl;
	score = 0;
	
	success = gateControl.AddAuthorization(111, "Smith, John", "0800", "1700");
	success = gateControl.AddAuthorization(222, "Brown, William", "0100", "2300");
	success = gateControl.AddAuthorization(333, "Jones, Peter", "0333", "2333");
	
	gCurrentDate = "01022019";
	gCurrentTime = "0100";
	success = gateControl.AccessAllowed(222);
	
	expectedVector.push_back(Transaction(222, "Brown, William", "01022019", "0100", true));
	gateControl.GetAllTransactions(actualVector);
	good = CompareTransactions(actualVector, expectedVector, cout);
	if (good)
	{
		score += 5;
	}
	else
	{
		cout << "Transaction log not as expected." << endl;
	}
	
	gCurrentDate = "01022019";
	gCurrentTime = "2300";
	success = gateControl.AccessAllowed(222);
	
	expectedVector.push_back(Transaction(222, "Brown, William", "01022019", "2300", true));
	gateControl.GetAllTransactions(actualVector);
	good = CompareTransactions(actualVector, expectedVector, cout);
	if (good)
	{
		score += 5;
	}
	else
	{
		cout << "Transaction log not as expected." << endl;
	}
	
	gCurrentDate = "01022019";
	gCurrentTime = "0059";
	success = gateControl.AccessAllowed(222);
	
	expectedVector.push_back(Transaction(222, "Brown, William", "01022019", "0059", false));
	gateControl.GetAllTransactions(actualVector);
	good = CompareTransactions(actualVector, expectedVector, cout);
	if (good)
	{
		score += 5;
	}
	else
	{
		cout << "Transaction log not as expected." << endl;
	}
	
	gCurrentDate = "01022019";
	gCurrentTime = "2312";
	success = gateControl.AccessAllowed(444);
	
	expectedVector.push_back(Transaction(444, "***", "01022019", "2312", false));
	gateControl.GetAllTransactions(actualVector);
	good = CompareTransactions(actualVector, expectedVector, cout);
	if (good)
	{
		score += 5;
	}
	else
	{
		cout << "Transaction log not as expected." << endl;
	}
	
	cout << "  Score: " << score << endl;
	
	return(score);
}

//****************************************************************************************
//
//	TestAdd
//
//****************************************************************************************
uint64_t	TestAdd()
{
	//************************************************************************************
	//	LOCAL DATA
	AuthorizationVector	actualVector;
	
	AuthorizationVector	expectedVector;
	
	GateControl			gateControl;
	
	bool				good;
	
	uint64_t			score;
	
	bool				success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Testing AddAuthorization" << endl;
	score = 0;
	
	gateControl.GetAllAuthorizations(actualVector);
	if (actualVector.empty())
	{
		score += 5;
	}
	
	expectedVector.push_back(Authorization(111, "Smith, John", "0800", "1700"));
	success = gateControl.AddAuthorization(111, "Smith, John", "0800", "1700");
	if (success)
	{
		gateControl.GetAllAuthorizations(actualVector);
		good = CompareAuthorizations(actualVector, expectedVector, cout);
		if (good)
		{
			score += 5;
		}
		else
		{
			cout << "Failed to add authorization for card 111." << endl;
		}
	}
	else
	{
		cout << "Failed to add authorization for card 111." << endl;
	}

	expectedVector.push_back(Authorization(222, "Brown, William", "0100", "2300"));
	success = gateControl.AddAuthorization(222, "Brown, William", "0100", "2300");
	if (success)
	{
		gateControl.GetAllAuthorizations(actualVector);
		good = CompareAuthorizations(actualVector, expectedVector, cout);
		if (good)
		{
			score += 5;
		}
		else
		{
			cout << "Failed to add authorization for card 222." << endl;
		}
	}
	else
	{
		cout << "Failed to add authorization for card 222." << endl;
	}
	
	success = gateControl.AddAuthorization(111, "Jones, Peter", "0800", "1700");
	if (!success)
	{
		score += 5;
	}
	else
	{
		cout << "Succeeded in adding authorization for card 111; should have failed, it's a duplicate." << endl;
	}
	
	cout << "  Score: " << score << endl;
	
	return(score);
}

//****************************************************************************************
//
//	TestCard
//
//****************************************************************************************
uint64_t	TestCard()
{
	//************************************************************************************
	//	LOCAL DATA
	TransactionVector	actualVector;
	
	Authorization		authorization;
	
	TransactionVector	expectedVector;
	
	GateControl			gateControl;
	
	bool				good;
	
	uint64_t			score;
	
	bool				success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Testing Card-Specific Functions" << endl;
	score = 0;
	
	success = gateControl.AddAuthorization(111, "Smith, John", "0800", "1700");
	success = gateControl.AddAuthorization(222, "Brown, William", "0100", "2300");
	success = gateControl.AddAuthorization(333, "Jones, Peter", "0333", "2333");
	
	success = gateControl.GetCardAuthorization(222, authorization);
	if ((authorization.name_ == "two")
		&&
		(authorization.startTime_ == "0100")
		&&
		(authorization.endTime_ == "2300"))
	{
		score += 5;
	}

	gCurrentDate = "01022019";
	gCurrentTime = "0900";
	success = gateControl.AccessAllowed(111);
	gCurrentTime = "0901";
	success = gateControl.AccessAllowed(222);
	gCurrentTime = "0902";
	success = gateControl.AccessAllowed(333);
	gCurrentTime = "0903";
	success = gateControl.AccessAllowed(111);
	gCurrentTime = "0904";
	success = gateControl.AccessAllowed(222);
	gCurrentTime = "0905";
	success = gateControl.AccessAllowed(333);
	
	expectedVector.push_back(Transaction(222, "Brown, William", "01022019", "0901", true));
	expectedVector.push_back(Transaction(222, "Brown, William", "01022019", "0904", true));
	gateControl.GetCardTransactions(222, actualVector);
	good = CompareTransactions(actualVector, expectedVector, cout);
	if (good)
	{
		score += 5;
	}
	else
	{
		cout << "Transaction log not as expected." << endl;
	}
	
	cout << "  Score: " << score << endl;
	
	return(score);
}

//****************************************************************************************
//
//	TestChange
//
//****************************************************************************************
uint64_t	TestChange()
{
	//************************************************************************************
	//	LOCAL DATA
	AuthorizationVector	actualVector;
	
	AuthorizationVector	expectedVector;
	
	GateControl			gateControl;
	
	bool				good;
	
	uint64_t			score;
	
	bool				success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Testing ChangeAuthorization" << endl;
	score = 0;
	
	success = gateControl.AddAuthorization(111, "Smith, John", "0800", "1700");
	success = gateControl.AddAuthorization(222, "Brown, William", "0100", "2300");
	success = gateControl.AddAuthorization(333, "Jones, Peter", "0333", "2333");
	
	success = gateControl.ChangeAuthorization(222, "twochanged", "1234", "1356");
	
	expectedVector.push_back(Authorization(111, "Smith, John", "0800", "1700"));
	expectedVector.push_back(Authorization(222, "Brown, William", "1234", "1356"));
	expectedVector.push_back(Authorization(333, "Jones, Peter", "0333", "2333"));
	
	gateControl.GetAllAuthorizations(actualVector);
	good = CompareAuthorizations(actualVector, expectedVector, cout);
	if (good)
	{
		score += 5;
	}
	else
	{
		cout << "Failed to change authorization for card 222." << endl;
	}
	
	success = gateControl.ChangeAuthorization(444, "", "", "");
	if (!success)
	{
		score += 5;
	}
	else
	{
		cout << "Succeeded in changing authorization for card 444; should have failed." << endl;
	}
	
	cout << "  Score: " << score << endl;
	
	return(score);
}

//****************************************************************************************
//
//	TestDelete
//
//****************************************************************************************
uint64_t	TestDelete()
{
	//************************************************************************************
	//	LOCAL DATA
	AuthorizationVector	actualVector;
	
	AuthorizationVector	expectedVector;
	
	GateControl			gateControl;
	
	bool				good;
	
	uint64_t			score;
	
	bool				success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Testing DeleteAuthorization" << endl;
	score = 0;
	
	success = gateControl.AddAuthorization(111, "Smith, John", "0800", "1700");
	success = gateControl.AddAuthorization(222, "Brown, William", "0100", "2300");
	success = gateControl.AddAuthorization(333, "Jones, Peter", "0333", "2333");
	
	success = gateControl.DeleteAuthorization(222);

	expectedVector.push_back(Authorization(111, "Smith, John", "0800", "1700"));
	expectedVector.push_back(Authorization(333, "Jones, Peter", "0333", "2333"));

	gateControl.GetAllAuthorizations(actualVector);
	good = CompareAuthorizations(actualVector, expectedVector, cout);
	if (good)
	{
		score += 5;
	}
	else
	{
		cout << "Failed to delete authorization for card 222." << endl;
	}

	success = gateControl.DeleteAuthorization(444);
	if (!success)
	{
		score += 5;
	}
	else
	{
		cout << "Succeeded in deleting authorization for card 444; should have failed." << endl;
	}

	cout << "  Score: " << score << endl;

	return(score);
}

#if 0
//****************************************************************************************
//
//	Class::Function
//
//****************************************************************************************
void	Class::Function()
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS

	return;
}

#endif
