/*
	Student.cpp
*/

// Includes
#include <iostream>
#include <iomanip>
#include "Student.h"
using namespace std;

// Class constants
const float Student::DEFAULT_GPA = 0.0;

/////////////////////////////////
//                             //
// Constructors and Destructor //
//                             //
/////////////////////////////////

// Student::Student ///////////////////////////////////////
Student::Student(char const * const name, int age, string ssn, float gpa) : Person(name, age, ssn)
{
	if (Student::Debug())
	{
		Student::DebugHeader();
		cout << "Inside of Student::Student() constructor." << endl;
	}
	GPA(gpa);
	if (Student::Debug())
	{
		cout << "GPA has been set to " << GPA() << '\n';
		cout << "Leaving Student::Student() constructor." << endl;
		Student::DebugFooter();
	}
}

// Student::Student ///////////////////////////////////////
Student::Student(const Student &s) : Person(s)
{
	if (Student::Debug())
	{
		Student::DebugHeader();
		cout << "Inside of Student::Student() COPY constructor." << endl;
	}
	GPA(s.GPA());
	if (Student::Debug())
	{
		cout << "GPA has been set to " << GPA() << '\n';
		cout << "Leaving Student::Student() COPY constructor." << endl;
		Student::DebugFooter();
	}
}

// Student::~Student //////////////////////////////////////
Student::~Student()
{
	if (Student::Debug())
	{
		Student::DebugHeader();
		cout << "Inside of Student::~Student() destructor.\n";
		cout << "Leaving Student::~Student() destructor.\n";
		Student::DebugFooter();
	}
}

//////////////////////////
//                      //
// Comparison Functions //
//                      //
//////////////////////////

// Student::IsTotallyDifferent ////////////////////////////
bool Student::IsTotallyDifferent(const Student &s) const
{ // Checks to see if two Students are completely different objects
	return Person::IsTotallyDifferent(s) && (&m_gpa != &s.m_gpa);
}

//////////////////////////
//                      //
// Overloaded Operators //
//                      //
//////////////////////////

// Student::operator = ////////////////////////////////////
const Student &Student::operator =(const Student &right_side)
{
	// In this case, checking for the same object is trivial.
	*((Person *)this) = right_side;		// We check where it matters.  Right here.
	GPA(right_side.GPA());
	return *this;
}

///////////////
//           //
// Accessors //
//           //
///////////////

// Student::GPA ///////////////////////////////////////////
float Student::GPA(void) const
{
	return m_gpa;
}

//////////////
//          //
// Mutators //
//          //
//////////////

// Student::GPA ///////////////////////////////////////////
void Student::GPA(float gpa)
{
	if (gpa < 0.0 || gpa > 4.0)
	{
		m_gpa = -1.0;	// This means an error occurred.
	}
	else
	{
		m_gpa = gpa;
	}
}

///////////////////
//               //
// I/O Functions //
//               //
///////////////////

// Student::Read //////////////////////////////////////////
void Student::Read(istream &is)
{
	float gpa = -1.0;					// Assume error so a bad value gets stored on erroneous input.
	bool keyboard = (&is == &cin);		// Are we reading from the keyboard?

	// Read the stuff into the Person portion of the object
	Person::Read(is);
	if (!is)	// Check for errors by directly testing the stream.
	{
		return;
	}

	// Get the gpa
	if (keyboard) { cout << "Enter the GPA: "; }
	is >> gpa;
	is.ignore(100, '\n');
	GPA(gpa);
}

// Student::Write /////////////////////////////////////////
void Student::Write(ostream &os) const
{
	ios::fmtflags flags;
	int precision;

	// Write Person portion
	Person::Write(os);

	// Write the rest.
	if (&os == &cout || &os == &cerr)
	{
		// Get original state.
		precision = cout.precision();
		flags = os.flags();

		// Display GPA
		os << fixed << setprecision(2);
		os << "GPA:  " << GPA();
		if (Student::Debug())
		{
			os << "  (Address is 0x" << &m_gpa << ')';
		}

		// Restore original state.
		cout.precision(precision);
		os.flags(flags);
	}
	else
	{
		os << GPA();
	}
	os << '\n' << flush;
}