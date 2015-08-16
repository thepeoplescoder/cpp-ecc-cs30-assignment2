/*
	Faculty.cpp
*/

// Includes
#include <iostream>
#include <string>
#include "Faculty.h"
using namespace std;

// Class constants
const string *Faculty::DEFAULT_DEGREES = NULL;

/////////////////////////////////
//                             //
// Constructors and Destructor //
//                             //
/////////////////////////////////

// Faculty::Faculty ///////////////////////////////////////
Faculty::Faculty(const char * const name, int age, string ssn, int numberOfDegrees, const string * const degrees) :
Person(name, age, ssn), m_degrees(NULL), m_numberOfDegrees(0)
{
	// Use the mutator to set these fields since it does the
	// necessary checking.
	Degrees(numberOfDegrees, degrees);
}

// Faculty::Faculty ///////////////////////////////////////
Faculty::Faculty(const Faculty &f) :
Person(f), m_degrees(NULL), m_numberOfDegrees(0)
{
	// Use the mutator to set these fields since it does the
	// necessary checking.
	Degrees(f.NumberOfDegrees(), f.Degrees());
}

// Faculty::~Faculty //////////////////////////////////////
Faculty::~Faculty()
{
	if (Faculty::Debug())
	{
		Faculty::DebugHeader();
		cout << "Inside of destructor Faculty::~Faculty()\n";
	}
	NumberOfDegrees(0);		// This code should free the buffer.
	if (Faculty::Debug())
	{
		cout << "Leaving destructor Faculty::~Faculty()\n";
		Faculty::DebugFooter();
	}
}

//////////////////////////
//                      //
// Overloaded Operators //
//                      //
//////////////////////////

// Faculty::operator = ////////////////////////////////////
const Faculty &Faculty::operator =(const Faculty &right_side)
{
	if (this != &right_side)
	{
		*((Person *)this) = right_side;
		Degrees(right_side.NumberOfDegrees(), right_side.Degrees());
	}
	return *this;
}

///////////////
//           //
// Accessors //
//           //
///////////////

// Faculty::NumberOfDegrees ///////////////////////////////
int Faculty::NumberOfDegrees(void) const
{
	return m_numberOfDegrees;
}

// Faculty::Degrees ///////////////////////////////////////
const string *Faculty::Degrees(void) const
{
	return m_degrees;
}

//////////////
//          //
// Mutators //
//          //
//////////////

// Faculty::NumberOfDegrees ///////////////////////////////
bool Faculty::NumberOfDegrees(int numberOfDegrees)
{ // Changes the number of degrees.  This can only be used to decrease the number.

	// Fail if we are trying to increase the number.
	if (numberOfDegrees > NumberOfDegrees())
	{
		return false;
	}

	// Otherwise try to change the number of degrees.
	else if (numberOfDegrees < NumberOfDegrees())
	{
		Degrees(numberOfDegrees, Degrees());
	}
	return true;
}

// Faculty::Degrees ///////////////////////////////////////
void Faculty::Degrees(int numberOfDegrees, const string * const degrees)
{ // Changes the degrees and the amount of the degrees.
	string *dest_buffer;

	// Debug code
	if (Faculty::Debug())
	{
		Faculty::DebugHeader();
		cout << "Inside of Faculty::Degrees(" << numberOfDegrees << ", string array)\n";
		cout << "Current number of degrees: " << NumberOfDegrees() << '\n';
		cout << "New number of degrees: " << numberOfDegrees << '\n';
	}

	// Leave if a number less than one is passed.
	if (numberOfDegrees < 1)
	{
		// Free the buffer and reset member variables if
		// we need to do so.
		if (NumberOfDegrees())
		{
			delete[] m_degrees;
			m_degrees = NULL;		// Reset member variables.
			m_numberOfDegrees = 0;

			// Debug code
			if (Faculty::Debug())
			{
				cout << "Number less than one passed, so the buffer was freed, and\n";
				cout << "all member variables have been reset.\n";
			}
		}
	}

	// Otherwise, resize or set new values in the buffer.
	else
	{
		// Keep the same destination buffer on the same number of degrees.
		if (numberOfDegrees == NumberOfDegrees())
		{
			dest_buffer = m_degrees;
		}
		else
		{
			dest_buffer = new string[numberOfDegrees];	// Otherwise, make a new one.
			m_numberOfDegrees = numberOfDegrees;		// Okay to update value here since we're not using it anywhere else.
		}

		// Initialize the buffer based on what we need to do.
		// This is automatically skipped if a number less than 1
		// is passed.
		if (degrees)
		{
			for (int index = 0; index < numberOfDegrees; index++)
			{
				dest_buffer[index] = degrees[index];
			}
		}

		// Dispose of the old buffer if we need to do so.
		if (dest_buffer != m_degrees)
		{
			delete[] m_degrees;
			m_degrees = dest_buffer;
		}
	}

	// Debug code
	if (Faculty::Debug())
	{
		cout << "Leaving Faculty::Degrees(" << numberOfDegrees << ", string array)\n";
		Faculty::DebugFooter();
	}
}

///////////////////
//               //
// I/O Functions //
//               //
///////////////////

// Faculty::Read //////////////////////////////////////////
void Faculty::Read(istream &is)
{
	bool keyboard = (&is == &cin);		// Are we reading from the keyboard?
	int numberOfDegrees = 0;			// The number of degrees.
	string newline;

	// Read the Person portion.
	Person::Read(is);

	// Continue reading if everything succeeded.
	if (is)
	{
		// Get the number of degrees.
		if (keyboard)
		{
			cout << "Enter the number of degrees: ";
		}
		is >> numberOfDegrees;
		getline(is, newline);		// Force the extraction of the newline.

		// Allocate space for the buffer.
		if (numberOfDegrees > 0)
		{
			// Free any buffer we may currently have allocated.
			NumberOfDegrees(0);

			// We will do a direct assignment here, to avoid unnecessary
			// multiple copies.
			m_degrees = new string[numberOfDegrees];

			// Get each degree.
			for (int index = 0; index < numberOfDegrees && is; index++)
			{
				if (keyboard)
				{
					cout << "Please enter degree #" << index + 1 << ": ";
				}
				getline(is, m_degrees[index]);
			}
		}

		// Set the new number of degrees.
		m_numberOfDegrees = (numberOfDegrees > 0) ? numberOfDegrees : 0;
	}
}

// Faculty::Write /////////////////////////////////////////
void Faculty::Write(ostream &os) const
{ // Writes a Faculty object to a given stream.
	bool screen = (&os == &cout || &os == &cerr);	// Are we writing to the screen?
	int index, len = NumberOfDegrees();

	// Write the Person portion of the object.
	Person::Write(os);

	// Write the number of degrees to the file.
	if (!screen)
	{
		os << NumberOfDegrees() << '\n';
	}

	// Are we writing to the screen?
	if (screen)
	{
		for (index = 0; index < len; index++)
		{
			os << "Degree #" << index + 1 << ": " << m_degrees[index] << '\n';
		}
	}
	else
	{
		for (index = 0; index < len; index++)
		{
			os << m_degrees[index] << '\n';
		}
	}

	// Flush the data to the screen/file.
	os << flush;
}