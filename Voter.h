/*
	Voter.h
*/

// Include this file only once
#pragma once

// Includes
#include <iostream>
#include <string>
#include "Person.h"
using namespace std;

// The Voter class
class Voter : virtual public Person
{
private:
	string m_partyAffiliation;

protected:
	// I/O helpers (for purposes of inheritance)
	void _writeVoterPortion(ostream &os) const;
	void _readVoterPortion(istream &is);

public:

	// Default values
	static const string DEFAULT_PARTY_AFFILIATION;

	// Constructors
	Voter(
		const char * const name = Voter::DEFAULT_NAME,
		int age                 = Voter::DEFAULT_AGE,
		string ssn              = Voter::DEFAULT_SSN,
		string partyAffiliation = Voter::DEFAULT_PARTY_AFFILIATION
	);
	Voter(const Voter &v);

	// Destructor
	~Voter();

	// IsTotallyDifferent
	bool IsTotallyDifferent(const Voter &v) const;

	// Overloaded assignment operator
	const Voter &operator =(const Voter &right_side);

	// RTII
	string Type(void) const { return "Voter"; }

	// Accessors
	const string &PartyAffiliation(void) const;

	// Mutators
	void PartyAffiliation(string s);
	void PartyAffiliation(const char * const s);

	// I/O Functions
	void Read(istream &is);
	void Write(ostream &os) const;
};