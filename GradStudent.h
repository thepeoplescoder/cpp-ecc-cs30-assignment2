/*
	GradStudent.h
*/

// Only include this file once
#pragma once

// Includes
#include <iostream>
#include <string>
#include "Student.h"
using namespace std;

// The GradStudent class
class GradStudent : public Student
{
private:
	string m_researchArea;
public:

	// Class constants
	static const string DEFAULT_RESEARCH_AREA;

	// Constructors
	GradStudent(
		const char * const name = GradStudent::DEFAULT_NAME,
		int age                 = GradStudent::DEFAULT_AGE,
		string ssn              = GradStudent::DEFAULT_SSN,
		float gpa               = GradStudent::DEFAULT_GPA,
		string researchArea     = GradStudent::DEFAULT_RESEARCH_AREA
	);
	GradStudent(const GradStudent &gs);

	// Destructor
	~GradStudent();

	// Overloaded assignment operator
	const GradStudent &operator =(const GradStudent &right_side);

	// RTTI
	string Type(void) const { return "GradStudent"; }

	// Accessors
	const string &ResearchArea(void) const;

	// Mutators
	void ResearchArea(string s);

	// I/O functions
	void Read(istream &is);
	void Write(ostream &os) const;
};