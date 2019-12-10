#include "Course.h"
//#include ".h"
#include <iostream>
#include <string>
using namespace std;

namespace BrooklynPoly {

	Course::Course(const string& courseName) : name(courseName) {}
	ostream& operator<<(ostream& os, const Course& rhs) {
		os << rhs.name << ": ";
		if (rhs.students.size() > 0) {
			for (const Student* currStudent : rhs.students) {
				os << currStudent->getName() << " ";
			}
		}
		else {
			os << "No Students";
		}
		os << "\n";
		return os;
	}
	const string& Course::getName() const {
		return name;
	}
	bool Course::addStudent(Student* studentPoint) {
		if (studentPoint != nullptr) {
			students.push_back(studentPoint);
			return true;
		}
		else {
			return false;
		}
	}
	void Course::removeStudentsFromCourse() {
		for (size_t index = 0; index < students.size(); ++index) {
			students[index]->removedFromCourse(this);
		}
		students.clear();
	}
}