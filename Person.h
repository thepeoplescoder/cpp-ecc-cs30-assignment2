/*
	Person.h
*/

// Make sure this file is only included once
#pragma once

// Includes
#include <iostream>
#include <string>

// Use standard namespace
using namespace std;

// Person
class Person
{
private:
	char *m_name;
	int m_age;
	string m_ssn;

	// Debug flag
	static bool c_DebugOn;

public:

	// Defaults
	static const string DEFAULT_SSN;
	static const int DEFAULT_AGE = 0;
	static const char * const DEFAULT_NAME;

	// Constructors
	Person(
		const char * const name = Person::DEFAULT_NAME,
		int age                 = Person::DEFAULT_AGE,
		string ssn              = Person::DEFAULT_SSN
	);
	Person(const Person &p);

	// Destructor
	virtual ~Person();

	// Character pointer conversion
	static const char * const ToStr(const char * const s) { return s ? s : ""; }

	// Debug stuff
	static bool Debug(void) { return Person::c_DebugOn; }
	static void Debug(bool state) { Person::c_DebugOn = state; }
	static void DebugHeader(void) { for (int x = 0; x < 50; x++) { cout << '-'; } cout << '\n'; }
	static void DebugFooter(void) { Person::DebugHeader(); cout << endl; }

	// Checks to see if a Person is a deep copy of another Person
	bool IsTotallyDifferent(const Person &p) const;

	// Overloaded operators
	const Person &operator =(const Person &right_side);

	// Runtime Type Identification
	virtual string Type(void) const { return "Person"; }

	// Accessors
	const char * const Name(void) const;
	int Age(void) const;
	string SSN(void) const;

	// Mutators
	void Name(const char * const name);
	void Age(int age);
	void SSN(string ssn);

	// I/O routines
	virtual void Read(istream &is);
	virtual void Write(ostream &os) const;
};

// Insertion operator
inline ostream &operator <<(ostream &os, const Person &p)
{
	p.Write(os);
	return os;
}

// Extraction operator
inline istream &operator >>(istream &is, Person &p)
{
	p.Read(is);
	return is;
}