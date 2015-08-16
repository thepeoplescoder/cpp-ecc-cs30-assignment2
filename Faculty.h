/*
	Faculty.h
*/

// Include this file only once
#pragma once

// Includes
#include <iostream>
#include "Person.h"

// The Faculty class
class Faculty : public Person
{
private:
	int m_numberOfDegrees;
	string *m_degrees;

public:

	// Class constants
	static const int DEFAULT_NUMBER_OF_DEGREES = 0;
	static const string *DEFAULT_DEGREES;

	// Constructors
	Faculty(
		const char * const name      = Faculty::DEFAULT_NAME,
		int age                      = Faculty::DEFAULT_AGE,
		string ssn                   = Faculty::DEFAULT_SSN,
		int numberOfDegrees          = Faculty::DEFAULT_NUMBER_OF_DEGREES,
		const string * const degrees = Faculty::DEFAULT_DEGREES
	);
	Faculty(const Faculty &f);

	// Destructor
	~Faculty();

	// Overloaded assignment operator
	const Faculty &operator =(const Faculty &right_side);

	// RTII
	string Type(void) const { return "Faculty"; }

	// Accessors
	int NumberOfDegrees(void) const;
	const string *Degrees(void) const;

	// Mutators
	bool NumberOfDegrees(int numberOfDegrees);
	void Degrees(int numberOfDegrees, const string *degrees);

	// I/O Functions
	void Read(istream &is);
	void Write(ostream &os) const;
};