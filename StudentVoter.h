/*
	StudentVoter.h
*/

// Only include this file once
#pragma once

// Includes
#include <iostream>
#include "Student.h"
#include "Voter.h"

// The StudentVoter class
class StudentVoter : public Student, public Voter
{
private:
public:

	// Constructors
	StudentVoter();
	StudentVoter(const char * const name, int age, string ssn, float gpa, string partyAffiliation);
	StudentVoter(const StudentVoter &sv);

	// Destructor
	~StudentVoter();

	// IsTotallyDifferent
	bool IsTotallyDifferent(const StudentVoter &sv) const;

	// Overloaded assignment operator.
	const StudentVoter &operator =(const StudentVoter &sv);

	// RTTI
	string Type(void) const { return "StudentVoter"; }

	// I/O Functions
	void Read(istream &is);
	void Write(ostream &os) const;
};