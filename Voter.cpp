/*
	Voter.cpp
*/

// Includes
#include <iostream>
#include <string>
#include "Voter.h"
using namespace std;

// Class constants
const string Voter::DEFAULT_PARTY_AFFILIATION = "";

////////////////////////////////////
//                                //
// Protected I/O Helper Functions //
//                                //
////////////////////////////////////

// Voter::_writeVoterPortion //////////////////////////////
void Voter::_writeVoterPortion(ostream &os) const
{ // Writes the Voter portion of a Voter object to a stream.
	if (&os == &cout || &os == &cerr)
	{
		os << "Party Affiliation:  " << PartyAffiliation();
		if (Voter::Debug())
		{
			os << "  (Address is 0x" << &PartyAffiliation() << ')';
		}
	}
	else
	{
		os << PartyAffiliation();
	}
	os << endl;
}

// Voter::_readVoterPortion ///////////////////////////////
void Voter::_readVoterPortion(istream &is)
{ // Reads the Voter portion of a Voter object from a stream.
	string partyAffiliation = "";

	// Display a prompt if reading from the keyboard.
	if (&is == &cin)
	{
		cout << "Enter the party affiliation: ";
	}

	// Read and set the new affiliation.
	getline(is, partyAffiliation);
	PartyAffiliation(partyAffiliation);
}

/////////////////////////////////
//                             //
// Constructors and Destructor //
//                             //
/////////////////////////////////

// Voter::Voter ///////////////////////////////////////////
Voter::Voter(const char * const name, int age, string ssn, string partyAffiliation) : Person(name, age, ssn), m_partyAffiliation(partyAffiliation)
{
	if (Voter::Debug())
	{
		Voter::DebugHeader();
		cout << "Inside of Voter::Voter(name, age, ssn, partyAffiliation) constructor." << endl;
		cout << "Party Affiliation has been set to: " << PartyAffiliation() << '\n';
		cout << "Leaving Voter::Voter(name, age, ssn, partyAffiliation) constructor." << endl;
		Voter::DebugFooter();
	}
}

// Voter::Voter ///////////////////////////////////////////
Voter::Voter(const Voter &v) : Person(v), m_partyAffiliation(v.PartyAffiliation())
{
	if (Voter::Debug())
	{
		Voter::DebugHeader();
		cout << "Inside of Voter::Voter() copy constructor." << endl;
		cout << "Party Affiliation has been set to: " << PartyAffiliation() << '\n';
		cout << "Leaving Voter::Voter() copy constructor." << endl;
		Voter::DebugFooter();
	}
}

// Voter::~Voter //////////////////////////////////////////
Voter::~Voter()
{
	if (Voter::Debug())
	{
		Voter::DebugHeader();
		cout << "Inside of Voter::~Voter() destructor." << endl;
		cout << "Leaving Voter::~Voter() destructor." << endl;
		Voter::DebugFooter();
	}
}

//////////////////////////
//                      //
// Comparison Functions //
//                      //
//////////////////////////

// Voter::IsTotallyDifferent //////////////////////////////
bool Voter::IsTotallyDifferent(const Voter &v) const
{ // Checks to see if two Voter objects are completely different.
	return Person::IsTotallyDifferent(v) && (&m_partyAffiliation != &v.m_partyAffiliation);
}

//////////////////////////
//                      //
// Overloaded Operators //
//                      //
//////////////////////////

// Voter::operator = //////////////////////////////////////
const Voter &Voter::operator =(const Voter &right_side)
{
	if (Voter::Debug())
	{
		Voter::DebugHeader();
		cout << "Inside overloaded assignment operator Voter::operator =()\n";
		cout << "Right side contains:\n" << right_side << '\n';
		cout << "Left side contains:\n" << *this << '\n';
	}

	// In this version of the overloaded assignment operator,
	// I actually DO the check because we are not copying something
	// trivial.
	if (this != &right_side)
	{
		*((Person *)this) = right_side;
		PartyAffiliation(right_side.PartyAffiliation());
		if (Voter::Debug())
		{
			cout << "Left side now contains:\n" << *this << '\n';
		}
	}
	else if (Voter::Debug())
	{
		cout << "Same object.  Ignoring copy . . .\n";
	}

	if (Voter::Debug())
	{
		cout << "Leaving overloaded assignment operator Voter::operator =()\n";
		Voter::DebugFooter();
	}
	return *this;
}

///////////////
//           //
// Accessors //
//           //
///////////////

// Voter::PartyAffiliation ////////////////////////////////
const string &Voter::PartyAffiliation(void) const
{
	// Return a reference so that the copy constructor is not called.
	return m_partyAffiliation;
}

//////////////
//          //
// Mutators //
//          //
//////////////

// Voter::PartyAffiliation ////////////////////////////////
void Voter::PartyAffiliation(string s)
{
	m_partyAffiliation = s;
}

// Voter::PartyAffiliation ////////////////////////////////
void Voter::PartyAffiliation(const char * const s)
{
	// Call string::assign() to avoid making unnecessary copies of s.
	m_partyAffiliation.assign(s);
}

///////////////////
//               //
// I/O Functions //
//               //
///////////////////

// Voter::Read ////////////////////////////////////////////
void Voter::Read(istream &is)
{
	// Read the stuff into the Person portion of the object
	Person::Read(is);
	if (is)	// Check for errors by directly testing the stream.
	{
		_readVoterPortion(is);
	}
}

// Voter::Write ///////////////////////////////////////////
void Voter::Write(ostream &os) const
{

	// Write Person portion
	Person::Write(os);

	// Write the rest.
	_writeVoterPortion(os);
}