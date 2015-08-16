/*
	StudentVoter.cpp
*/

// Includes
#include <iostream>
#include <string>
#include "StudentVoter.h"
using namespace std;

/////////////////////////////////
//                             //
// Constructors and Destructor //
//                             //
/////////////////////////////////

// StudentVoter::StudentVoter /////////////////////////////
StudentVoter::StudentVoter() : Person(), Student(), Voter()
{
	if (StudentVoter::Debug())
	{
		StudentVoter::DebugHeader();
		cout << "Inside of constructor StudentVoter::StudentVoter()" << endl;
		cout << "Leaving constructor StudentVoter::StudentVoter()" << endl;
		StudentVoter::DebugFooter();
	}
}

// StudentVoter::StudentVoter /////////////////////////////
StudentVoter::StudentVoter(const char * const name, int age, string ssn, float gpa, string partyAffiliation) :
Person(name, age, ssn), Student(name, age, ssn, gpa), Voter(name, age, ssn, partyAffiliation)
{
	if (StudentVoter::Debug())
	{
		StudentVoter::DebugHeader();
		cout << "Inside of constructor StudentVoter::StudentVoter(name, age, ssn, gpa, partyAffiliation" << endl;
		cout << "Leaving constructor StudentVoter::StudentVoter(name, age, ssn, gpa, partyAffiliation" << endl;
		StudentVoter::DebugFooter();
	}
}

// StudentVoter::StudentVoter /////////////////////////////
StudentVoter::StudentVoter(const StudentVoter &sv) :
Person(sv), Student(sv), Voter(sv)
{
	if (StudentVoter::Debug())
	{
		StudentVoter::DebugHeader();
		cout << "Inside of copy constructor StudentVoter::StudentVoter(sv)" << endl;
		cout << "Leaving copy constructor StudentVoter::StudentVoter(sv)" << endl;
		StudentVoter::DebugFooter();
	}
}

// StudentVoter::~StudentVoter /
StudentVoter::~StudentVoter()
{
	if (StudentVoter::Debug())
	{
		StudentVoter::DebugHeader();
		cout << "Inside of destructor StudentVoter::~StudentVoter()" << endl;
		cout << "Leaving destructor StudentVoter::~StudentVoter()" << endl;
		StudentVoter::DebugFooter();
	}
}

//////////////////////
//                  //
// Comparison Stuff //
//                  //
//////////////////////

// IsTotallyDifferent
bool StudentVoter::IsTotallyDifferent(const StudentVoter &sv) const
{ // Compares two StudentVoter instances to ensure they are completely different.
	return Student::IsTotallyDifferent(sv) && (&PartyAffiliation() != &sv.PartyAffiliation());
}

// Overloaded assignment operator.
const StudentVoter &StudentVoter::operator =(const StudentVoter &sv)
{
	// Do the check this time because copying a string is not a trivial thing.
	if (this != &sv)
	{
		*((Student *)this) = sv;
		PartyAffiliation(sv.PartyAffiliation());
	}
	return *this;
}

///////////////////
//               //
// I/O Functions //
//               //
///////////////////

// StudentVoter::Read /////////////////////////////////////
void StudentVoter::Read(istream &is)
{ // Reads a StudentVoter from a stream.
	Student::Read(is);
	_readVoterPortion(is);
}

// StudentVoter::Write ////////////////////////////////////
void StudentVoter::Write(ostream &os) const
{ // Writes a StudentVoter to a stream.
	Student::Write(os);
	_writeVoterPortion(os);
}