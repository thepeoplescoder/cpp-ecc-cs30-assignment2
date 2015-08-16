/*
	Person.cpp
*/

// Suppress warnings
#define _CRT_SECURE_NO_WARNINGS

// Includes
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include "Person.h"

// Use standard namespace
using namespace std;

// Class constants
const string Person::DEFAULT_SSN = "000-00-0000";
const char * const Person::DEFAULT_NAME = NULL;

// Class variables
bool Person::c_DebugOn = false;

// Static constants
static const string INVALID_SSN = "Invalid SSN";

// Static function prototypes
static bool is_valid_ssn(const string &ssn);

// is_valid_ssn ///////////////////////////////////////////
static bool is_valid_ssn(const string &ssn)
{ // Ensures a given social security number is valid.
	int len = ssn.length();		// To avoid repeated calls to ssn.length()
	bool is_an_ssn;				// Is this a social security number?

	// A valid security number has 11 characters, including dashes.
	is_an_ssn = (len == 11);

	// Check each character in the string.
	for (int index = 0; index < len && is_an_ssn; index++)
	{
		switch (index)
		{
		case 3:
		case 6:  is_an_ssn = (ssn[index] == '-');        break;
		default: is_an_ssn = (isdigit(ssn[index]) != 0); break;
		}
	}

	// Return success or failure.
	return is_an_ssn;
}

///////////////////////////////////
//                               //
// Constructor(s) and Destructor //
//                               //
///////////////////////////////////

// Person::Person /////////////////////////////////////////
Person::Person(const char * const name, int age, string ssn) : m_ssn(ssn)
{
	// Debug code
	if (Person::Debug())
	{
		Person::DebugHeader();
		cout << "Inside of Person::Person(\"" << Person::ToStr(name) << "\", " << age << ", \"" << ssn << "\")" << endl;
	}

	// Set an empty string to trick the Name() mutator.
	// I'm using the Name() mutator because it checks for
	// errors, and handles trivial cases such as a NULL pointer
	// and empty strings.
	m_name = new char[1];
	*m_name = '\0';

	// Use mutators for primitive types.
	Name(name);				// Set the name via the mutator since it works the way we need.
	Age(age);				// Set the age via the mutator to check for invalid values.

	// Check validity of SSN.
	if (!is_valid_ssn(m_ssn))
	{
		if (Person::Debug())
		{
			cout << "Invalid social security number set in constructor." << endl;
		}
		m_ssn = INVALID_SSN;
	}

	// Debug code.  Show contents of object.
	if (Person::Debug())
	{
		cout << "Newly created object contains:\n" << *this << endl;
		cout << "Leaving Person::Person(\"" << Person::ToStr(name) << "\", " << age << ", \"" << ssn << "\")\n";
		Person::DebugFooter();
	}
}

// Person::Person /////////////////////////////////////////
Person::Person(const Person &p)
{
	if (Person::Debug())
	{
		Person::DebugHeader();
		cout << "Inside copy constructor Person::Person(reference to 0x" << &p << ")\n";
		cout << "This reference contains:\n";
		cout << p << '\n';
	}

	m_name = new char[strlen(p.Name()) + 1];	// Name
	strcpy(m_name, p.Name());					// This should always be set up the way we need.

	Age(p.Age());								// Age
	SSN(p.SSN());								// SSN

	if (Person::Debug())
	{
		cout << "Newly created object contains:\n" << *this << '\n';
		cout << "Leaving copy constructor Person::Person(reference to 0x" << &p << ")\n";
		Person::DebugFooter();
	}
}

// Person::~Person ////////////////////////////////////////
Person::~Person()
{
	// Debug code.
	if (Person::Debug())
	{
		Person::DebugHeader();
		cout << "Inside of destructor Person::~Person().\n";
		cout << "This object contains:\n" << *this << '\n';
	}

	// The name should never be a null pointer.
	delete[] m_name;

	if (Person::Debug())
	{
		cout << "Name buffer deleted.\n";
		Person::DebugFooter();
	}

	// Trash values so separate processes cannot access them.
	m_name = NULL;
	m_ssn.clear();
	m_age = -1;
}

//////////////////////////
//                      //
// Comparison Functions //
//                      //
//////////////////////////

// Person::IsTotallyDifferent /////////////////////////////
bool Person::IsTotallyDifferent(const Person &p) const
{ // Checks to see if two objects are totally different.
	return (this != &p) && (m_name != p.m_name) && (&m_age != &p.m_age) && (&m_ssn != &p.m_ssn);
}

//////////////////////////
//                      //
// Overloaded Operators //
//                      //
//////////////////////////

// Person::operator = /////////////////////////////////////
const Person &Person::operator =(const Person &right_side)
{
	// Display a message
	if (Person::Debug())
	{
		Person::DebugHeader();
		cout << "Inside overloaded assignment operator.\n";
		cout << "Address of right side: " << &right_side << '\n';
		cout << "Right side contains:\n" << right_side << '\n';
		cout << "Left side contains:\n" << *this << '\n';
	}

	// Don't waste any time if both sides are the same object.
	if (this != &right_side)
	{
		// Use the mutators to copy the information because
		// the error checking is included.
		Name(right_side.Name());
		Age(right_side.Age());
		SSN(right_side.SSN());
	}
	else if (Person::Debug())
	{
		cout << "Trying to copy the same object, so this action is being ignored.\n";
	}

	// Show the result of the copy.
	if (Person::Debug())
	{
		cout << "Copy finished.  Left side now contains:\n";
		cout << *this;
		Person::DebugFooter();
	}

	return *this;
}

///////////////
//           //
// Accessors //
//           //
///////////////

// Person::Name ///////////////////////////////////////////
const char * const Person::Name(void) const
{
	return m_name;
}

// Person::Age ////////////////////////////////////////////
int Person::Age(void) const
{
	return m_age;
}

// Person::SSN ////////////////////////////////////////////
string Person::SSN(void) const
{
	return m_ssn;
}

//////////////
//          //
// Mutators //
//          //
//////////////

// Person::Name ///////////////////////////////////////////
void Person::Name(const char * const name)
{ // Sets the Person's name.

	const char * const _name = name ? name : "";	// Treat NULL pointers like empty strings.
	int new_length, current_length;
	char *buffer;

	// Display debug code
	if (Person::Debug())
	{
		Person::DebugHeader();
		cout << "Inside of Person::Name(0x" << (void *)name << ")\n";
		cout << "Name will be changed to \"" << _name << "\"\n-\n";
		cout << "Name is currently \"" << m_name << "\"\n";
		cout << "Address of current name: 0x" << (void *)m_name << "\n-\n";
	}

	// Get the lengths of both strings
	new_length = (int)strlen(_name);
	current_length = (int)strlen(m_name);

	// Only allocate space for a new buffer if necessary
	if (new_length != current_length)
	{
		if (Person::Debug())
		{
			cout << "Resizing buffer to " << new_length + 1 << " bytes\n";
		}
		buffer = new char[new_length + 1];
	}
	else
	{
		if (Person::Debug())
		{
			cout << "Length of new string is the same, so the same buffer will be used.\n";
		}
		buffer = m_name;	// Use the same location if we are not resizing.
	}

	// Get the string
	strcpy(buffer, _name);

	// Delete old space and reassign if we are resizing.
	if (buffer != m_name)
	{
		delete[] m_name;
		if (Person::Debug())
		{
			cout << "Old buffer deleted.\n";
		}
		m_name = buffer;
	}

	// Display the new name.
	if (Person::Debug())
	{
		cout << "Name is now \"" << m_name << "\"\n";
		cout << "Address of new name: 0x" << (void *)m_name << "\n";
		cout << "Leaving Person::Name(0x" << (void *)name << ")\n";
		Person::DebugFooter();
	}
}

// Person::Age ////////////////////////////////////////////
void Person::Age(int age)
{ // Sets the person's age.

	// Invariant: Age cannot be negative.
	if (age >= 0)
	{
		m_age = age;
	}

	// Display a diagnostic on an invalid age.
	else
	{
		m_age = -1;
	}
}

// Person::SSN ////////////////////////////////////////////
void Person::SSN(string ssn)
{ // Sets the Person's social security number.

	// Only change the SSN if a valid one was passed.
	if (is_valid_ssn(ssn))
	{
		m_ssn = ssn;
	}

	// Otherwise display an error message.
	else
	{
		m_ssn = INVALID_SSN;
	}
}

///////////////////
//               //
// I/O Functions //
//               //
///////////////////

// Person::Read ///////////////////////////////////////////
void Person::Read(istream &is)
{
	bool keyboard = (&is == &cin);		// Are we reading from the keyboard?
	string name, ssn;
	int age;

	// Get the name
	if (keyboard) { cout << "Enter the person's name: "; }
	if (!getline (is, name))
	{
		return;
	}

	// Get the age
	if (keyboard) { cout << "Enter the person's age: "; }
	is >> age;
	if (is.bad())
	{
		return;
	}
	if (!getline(is, ssn))		// Guarantees that the newline is grabbed.
	{
		return;
	}

	// Get the social security number
	if (keyboard) { cout << "Enter the person's social security number: "; }
	getline(is, ssn);

	// Assign the new fields.
	Name(name.c_str());
	Age(age);
	SSN(ssn);
}

// Person::Write //////////////////////////////////////////
void Person::Write(ostream &os) const
{
	if (&os == &cout || &os == &cerr)
	{
		// Name
		os << "Name: " << Name();
		if (Person::Debug())
		{
			os << "  (Address is 0x" << (void *)Name() << ')';
		}
		os << '\n';

		// Age
		os << "Age:  " << Age();
		if (Person::Debug())
		{
			os << "  (Address is 0x" << &m_age << ')';
		}
		os << '\n';

		// SSN
		os << "SSN:  " << SSN();
		if (Person::Debug())
		{
			os << "  (Address is 0x" << &m_ssn << ')';
		}
		os << '\n';
	}
	else
	{
		os << Name() << '\n';
		os << Age() << '\n';
		os << SSN() << '\n';
	}
	os << flush;
}