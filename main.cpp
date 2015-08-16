#include <iostream>
#include <string>
#include "Person.h"
#include "Student.h"
#include "Voter.h"
#include "StudentVoter.h"
#include "Faculty.h"
#include "GradStudent.h"
using namespace std;

int main(void)
{
	//Person::Debug(true);

	/*
	Person p;

	cin >> p;
	cout << p;

	Person p2(p);
	cout << p2;

	Person p3;
	p3 = p2;
	cout << p3;
	*/

	/*
	Student s;
	Person *p = new Student;

	cin >> s;
	cout << s;

	cin >> *p;
	cout << *p;

	delete p;
	*/

	/*
	Voter v, v2;
	cin >> v;
	cout << v;

	Voter v3(v);
	v2 = v;

	v.PartyAffiliation("Test");

	cout << "v.IsTotallyDifferent(v2) = " << v.IsTotallyDifferent(v2) << endl;
	cout << "v2.IsTotallyDifferent(v) = " << v2.IsTotallyDifferent(v) << endl;
	cout << "v3.IsTotallyDifferent(v2) = " << v3.IsTotallyDifferent(v2) << endl;

	cout << v << endl;
	cout << v2 << endl;
	cout << v3 << endl;
	*/

	Faculty f;
	string *sa;

	cin >> f;
	cout << f;

	Faculty f2(f);

	sa = const_cast<string *>(f2.Degrees());
	sa[1] = "Sociology";

	cout << f << endl;
	cout << f2 << endl;
	return 0;
}