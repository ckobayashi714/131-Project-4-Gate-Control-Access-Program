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
class	Result
{
	public:
		Result(): maximum_(80), total_(0) {}
		
		void	Fail();

		void	Pass(uint64_t score);

		void	SetMaximum(uint64_t maximum);

		void	Show();

	private:
		uint64_t	maximum_;

		uint64_t	total_;
};

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

void	TestAccess(Result& result);

void	TestAdd(Result& result);

void	TestCard(Result& result);

void	TestChange(Result& result);

void	TestDelete(Result& result);

//****************************************************************************************
//
//	MAIN PROGRAM
//
//****************************************************************************************
int main (int argc, char * const argv[])
{
	//************************************************************************************
	//	LOCAL DATA
	Result	result;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	result.SetMaximum(80);

	TestAdd(result);

	TestDelete(result);

	TestChange(result);

	TestAccess(result);

	TestCard(result);

	cout << endl << "Final result: ";
	result.Show();

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
void	TestAccess(Result& result)
{
	//************************************************************************************
	//	LOCAL DATA
	TransactionVector	actualVector;

	TransactionVector	expectedVector;

	GateControl			gateControl;

	bool				good;

	bool				success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Testing Access" << endl;

	success = gateControl.AddAuthorization(111, "Smith, John", "0800", "1700");
	success = gateControl.AddAuthorization(222, "Brown, William", "0100", "2300");
	success = gateControl.AddAuthorization(333, "Jones, Peter", "0333", "2333");

	cout << "  Allowed 1 (6 points) ";
	gCurrentDate = "01022019";
	gCurrentTime = "0100";
	success = gateControl.AccessAllowed(222);

	expectedVector.push_back(Transaction(222, "Brown, William", "01022019", "0100", true));
	gateControl.GetAllTransactions(actualVector);
	good = CompareTransactions(actualVector, expectedVector, cout);

	if (good)
	{
		result.Pass(6);
	}
	else
	{
		result.Fail();
	}

	cout << "  Allowed 2 (5 points) ";
	gCurrentDate = "01022019";
	gCurrentTime = "2300";
	success = gateControl.AccessAllowed(222);

	expectedVector.push_back(Transaction(222, "Brown, William", "01022019", "2300", true));
	gateControl.GetAllTransactions(actualVector);
	good = CompareTransactions(actualVector, expectedVector, cout);
	if (good)
	{
		result.Pass(5);
	}
	else
	{
		result.Fail();
	}

	cout << "  Denied 1 (6 points) ";
	gCurrentDate = "01022019";
	gCurrentTime = "0059";
	success = gateControl.AccessAllowed(222);

	expectedVector.push_back(Transaction(222, "Brown, William", "01022019", "0059", false));
	gateControl.GetAllTransactions(actualVector);
	good = CompareTransactions(actualVector, expectedVector, cout);
	if (good)
	{
		result.Pass(6);
	}
	else
	{
		result.Fail();
	}

	cout << "  Denied 2 (5 points) ";
	gCurrentDate = "01022019";
	gCurrentTime = "2312";
	success = gateControl.AccessAllowed(444);

	expectedVector.push_back(Transaction(444, "***", "01022019", "2312", false));
	gateControl.GetAllTransactions(actualVector);
	good = CompareTransactions(actualVector, expectedVector, cout);
	if (good)
	{
		result.Pass(5);
	}
	else
	{
		result.Fail();
	}

	return;
}

//****************************************************************************************
//
//	TestAdd
//
//****************************************************************************************
void	TestAdd(Result& result)
{
	//************************************************************************************
	//	LOCAL DATA
	AuthorizationVector	actualVector;

	AuthorizationVector	expectedVector;

	GateControl			gateControl;

	bool				good;

	bool				success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Testing AddAuthorization" << endl;

	cout << "  Check Empty (5 points) ";
	gateControl.GetAllAuthorizations(actualVector);
	if (actualVector.empty())
	{
		result.Pass(5);
	}
	else
	{
		result.Fail();
	}

	cout << "  Add First (6 points) ";
	expectedVector.push_back(Authorization(111, "Smith, John", "0800", "1700"));
	success = gateControl.AddAuthorization(111, "Smith, John", "0800", "1700");
	if (success)
	{
		gateControl.GetAllAuthorizations(actualVector);
		good = CompareAuthorizations(actualVector, expectedVector, cout);
		if (good)
		{
			result.Pass(6);
		}
		else
		{
			result.Fail();
		}
	}
	else
	{
		result.Fail();
	}

	cout << "  Add Second (5 points) ";
	expectedVector.push_back(Authorization(222, "Brown, William", "0100", "2300"));
	success = gateControl.AddAuthorization(222, "Brown, William", "0100", "2300");
	if (success)
	{
		gateControl.GetAllAuthorizations(actualVector);
		good = CompareAuthorizations(actualVector, expectedVector, cout);
		if (good)
		{
			result.Pass(5);
		}
		else
		{
			result.Fail();
		}
	}
	else
	{
		result.Fail();
	}

	cout << "  Add Duplicate (6 points) ";
	success = gateControl.AddAuthorization(111, "Jones, Peter", "0800", "1700");
	if (!success)
	{
		result.Pass(6);
	}
	else
	{
		result.Fail();
	}

	return;
}

//****************************************************************************************
//
//	TestCard
//
//****************************************************************************************
void	TestCard(Result& result)
{
	//************************************************************************************
	//	LOCAL DATA
	TransactionVector	actualVector;

	Authorization		authorization;

	TransactionVector	expectedVector;

	GateControl			gateControl;

	bool				good;

	bool				success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Testing Card-Specific Functions" << endl;

	success = gateControl.AddAuthorization(111, "Smith, John", "0800", "1700");
	success = gateControl.AddAuthorization(222, "Brown, William", "0100", "2300");
	success = gateControl.AddAuthorization(333, "Jones, Peter", "0333", "2333");

	cout << "  GetCardAuthorization (6 points) ";
	success = gateControl.GetCardAuthorization(222, authorization);
	if ((authorization.name_ == "Brown, William")
		&&
		(authorization.startTime_ == "0100")
		&&
		(authorization.endTime_ == "2300"))
	{
		result.Pass(6);
	}
	else
	{
		result.Fail();
	}

	cout << "  GetCardTransactions (6 points) ";
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
		result.Pass(6);
	}
	else
	{
		result.Fail();
	}

	return;
}

//****************************************************************************************
//
//	TestChange
//
//****************************************************************************************
void	TestChange(Result& result)
{
	//************************************************************************************
	//	LOCAL DATA
	AuthorizationVector	actualVector;

	AuthorizationVector	expectedVector;

	GateControl			gateControl;

	bool				good;

	bool				success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Testing ChangeAuthorization" << endl;

	success = gateControl.AddAuthorization(111, "Smith, John", "0800", "1700");
	success = gateControl.AddAuthorization(222, "Brown, William", "0100", "2300");
	success = gateControl.AddAuthorization(333, "Jones, Peter", "0333", "2333");

	cout << "  Existing Card (6 points) ";
	success = gateControl.ChangeAuthorization(222, "Brown, Bill", "1234", "1356");

	expectedVector.push_back(Authorization(111, "Smith, John", "0800", "1700"));
	expectedVector.push_back(Authorization(222, "Brown, Bill", "1234", "1356"));
	expectedVector.push_back(Authorization(333, "Jones, Peter", "0333", "2333"));

	gateControl.GetAllAuthorizations(actualVector);
	good = CompareAuthorizations(actualVector, expectedVector, cout);
	if (good)
	{
		result.Pass(6);
	}
	else
	{
		result.Fail();
	}

	cout << "  Non-existent Card (6 points) ";
	success = gateControl.ChangeAuthorization(444, "", "", "");
	if (!success)
	{
		result.Pass(6);
	}
	else
	{
		result.Fail();
	}

	return;
}

//****************************************************************************************
//
//	TestDelete
//
//****************************************************************************************
void	TestDelete(Result& result)
{
	//************************************************************************************
	//	LOCAL DATA
	AuthorizationVector	actualVector;

	AuthorizationVector	expectedVector;

	GateControl			gateControl;

	bool				good;

	bool				success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Testing DeleteAuthorization" << endl;

	success = gateControl.AddAuthorization(111, "Smith, John", "0800", "1700");
	success = gateControl.AddAuthorization(222, "Brown, William", "0100", "2300");
	success = gateControl.AddAuthorization(333, "Jones, Peter", "0333", "2333");

	cout << "  Existing Card (6 points) ";
	success = gateControl.DeleteAuthorization(222);

	expectedVector.push_back(Authorization(111, "Smith, John", "0800", "1700"));
	expectedVector.push_back(Authorization(333, "Jones, Peter", "0333", "2333"));

	gateControl.GetAllAuthorizations(actualVector);
	good = CompareAuthorizations(actualVector, expectedVector, cout);
	if (good)
	{
		result.Pass(6);
	}
	else
	{
		result.Fail();
	}

	cout << "  Non-existent Card (6 points) ";
	success = gateControl.DeleteAuthorization(444);
	if (!success)
	{
		result.Pass(6);
	}
	else
	{
		result.Fail();
	}

	return;
}

//****************************************************************************************
//
//	Result::Fail
//
//****************************************************************************************
void	Result::Fail()
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Fail. ";

	Show();

	return;
}

//****************************************************************************************
//
//	Result::Pass
//
//****************************************************************************************
void	Result::Pass(uint64_t score)
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Pass. ";
	total_ += score;

	Show();

	return;
}

//****************************************************************************************
//
//	Result::SetMaximum
//
//****************************************************************************************
void	Result::SetMaximum(uint64_t maximum)
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	maximum_ = maximum;

	return;
}

//****************************************************************************************
//
//	Result::Show
//
//****************************************************************************************
void	Result::Show()
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << total_ << "/" << maximum_ << " points" << endl;

	return;
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
