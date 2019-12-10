
#include "Student.h"
#include "Course.h"
#include "Registrar.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


namespace BrooklynPoly {

	Student::Student(const string& name) : name(name) {}
	ostream& operator<<(ostream& os, const Student& rhs) {
		os << rhs.name << ": ";
		vector<Course*> studentCourses = rhs.courses;
		if (studentCourses.size() > 0) {
			for (const Course* currCourse : studentCourses) {
				os << currCourse->getName() << " ";
			}
		}
		else {
			os << "No Courses";
		}
		os << "\n";
		return os;
	}
	const string& Student::getName() const {
		return name;
	}
	bool Student::addCourse(Course* coursePoint) {
		if (coursePoint != nullptr) {
			courses.push_back(coursePoint);
			return  true;
		}
		else {
			return false;
		}
	}
	void Student::removedFromCourse(Course* coursePoint) {
		for (size_t index = 0; index < courses.size(); ++index) {
			if (coursePoint == courses[index]) {
				swap(*courses[index], *courses[courses.size() - 1]);
			}
		}
		courses.pop_back();
	}

}