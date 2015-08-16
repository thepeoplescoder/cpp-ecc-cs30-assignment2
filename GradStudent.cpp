/*
	GradStudent.cpp
*/

// Includes
#include <iostream>
#include <string>
#include "GradStudent.h"
using namespace std;

// Class constants
const string GradStudent::DEFAULT_RESEARCH_AREA = "";

/////////////////////////////////
//                             //
// Constructors and Destructor //
//                             //
/////////////////////////////////

// GradStudent::GradStudent ///////////////////////////////
GradStudent::GradStudent(const char * const name, int age, string ssn, float gpa, string researchArea) :
Student(name, age, ssn, gpa), m_researchArea(researchArea)
{
}

// GradStudent::GradStudent ///////////////////////////////
GradStudent::GradStudent(const GradStudent &gs) :
Student(gs), m_researchArea(gs.ResearchArea())
{
}

// GradStudent::~GradStudent //////////////////////////////
GradStudent::~GradStudent()
{
}

//////////////////////////
//                      //
// Overloaded Operators //
//                      //
//////////////////////////

// GradStudent::operator = ////////////////////////////////
const GradStudent &GradStudent::operator =(const GradStudent &right_side)
{
	if (this != &right_side)
	{
		*((Student *)this) = right_side;
		ResearchArea(right_side.ResearchArea());
	}
	return *this;
}

///////////////
//           //
// Accessors //
//           //
///////////////

// GradStudent::ResearchArea //////////////////////////////
const string &GradStudent::ResearchArea(void) const
{
	return m_researchArea;
}

//////////////
//          //
// Mutators //
//          //
//////////////

// GradStudent::ResearchArea //////////////////////////////
void GradStudent::ResearchArea(string s)
{
	m_researchArea = s;
}

///////////////////
//               //
// I/O Functions //
//               //
///////////////////

// GradStudent::Read //////////////////////////////////////
void GradStudent::Read(istream &is)
{
	// Read the student portion first
	Student::Read(is);

	// Display everything else.
	if (is)
	{
		if (&is == &cin)
		{
			cout << "Enter the research area: ";
		}
		getline(is, m_researchArea);
	}
}

// GradStudent::Write /////////////////////////////////////
void GradStudent::Write(ostream &os) const
{
	// Write the Student portion first.
	Student::Write(os);

	// Display everything else.
	if (&os == &cout || &os == &cerr)
	{
		os << "Research area: ";
	}
	os << ResearchArea() << endl;
}