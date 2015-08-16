/*
	Student.h
*/

// Include this file only once
#pragma once

// Includes
#include <iostream>
#include "Person.h"

// The Student class.
class Student : virtual public Person
{
private:
	float m_gpa;	// Student's GPA

public:

	// Default values
	static const float DEFAULT_GPA;

	// Constructors
	Student(
		char const * const name = Student::DEFAULT_NAME,	// Class variables derived
		int age                 = Student::DEFAULT_AGE,		// from the Person class.
		string ssn              = Student::DEFAULT_SSN,
		float gpa               = Student::DEFAULT_GPA
	);
	Student(const Student &s);

	// Destructor
	~Student();

	// IsTotallyDifferent
	bool IsTotallyDifferent(const Student &s) const;

	// Overloaded assignment operator
	const Student &operator =(const Student &right_side);

	// Run time type identification
	string Type(void) const { return "Student"; }

	// Accessors
	float GPA(void) const;

	// Mutators
	void GPA(float gpa);

	// Read and write functions
	void Read(istream &is);
	void Write(ostream &os) const;
};