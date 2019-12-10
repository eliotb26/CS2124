#include "Student.h"
#include "Course.h"
#include "Registrar.h"
#include <iostream>

using namespace std;


namespace BrooklynPoly {

	ostream& operator<<(ostream& os, const Registrar& rhs) {
		vector<Course*> rhsCourses = rhs.courses;
		vector<Student*> rhsStudents = rhs.students;
		os << "Registrar's Report\nCourses:\n";
		for (Course* currCourse : rhsCourses) {
			os << *currCourse;
		}
		os << "Students:\n";
		for (Student* currStudent : rhsStudents) {
			os << *currStudent << " ";
		}
		return os;
	}

	Registrar::Registrar() {}

	bool Registrar::addCourse(const string& courseName) {
		for (size_t index = 0; index < courses.size(); ++index) {
			if (courseName == courses[index]->getName()) {
				return false;
			}
		}
		Course* course = new Course(courseName);
		courses.push_back(course);
		return true;
	}
	bool Registrar::addStudent(const string& studentName) {
		for (size_t index = 0; index < students.size(); ++index) {
			if (studentName == students[index]->getName()) {
				return false;
			}
		}
		Student* student = new Student(studentName);
		students.push_back(student);
		return true;
	}
	bool Registrar::enrollStudentInCourse(const string& studentName,
		const string& courseName) {
		for (size_t index = 0; index < courses.size(); ++index) {
			if (courses[index]->getName() == courseName) {  //could also check if the Student is already in the class
				for (size_t num = 0; num < students.size(); ++num) {
					if (students[num]->getName() == studentName) {
						Student* currStudent = students[num];
						Course* currCourse = courses[index];
						students[num]->addCourse(currCourse);
						currCourse->addStudent(currStudent);
						return true;
					}
				}
			}
		}
		return false;
	}
	bool Registrar::cancelCourse(const string& courseName) {
		size_t courseIndex = this->findCourse(courseName);
		if (courseIndex != courses.size()) {
			Course* oldCourse = courses[courseIndex];
			oldCourse->removeStudentsFromCourse();
			//for (size_t index = 0; index < students.size(); ++index) {
			//	students[index]->removedFromCourse(oldCourse);
			//}
			swap(courses[courseIndex], courses[courses.size() - 1]);
			//size_t last = courses.size(); 
			//Course* tempCoursePointer = oldCourse;
			//courses[courseIndex] = courses[last];
			//courses[last] = tempCoursePointer; 
			courses.pop_back();
			return true;
		}
		return false;
	}

	void Registrar::purge() {
		for (size_t index = 0; index < courses.size(); ++index) {
			courses[index]->removeStudentsFromCourse();
		}
		for (size_t num = 0; num < courses.size(); ++num) {
			courses.pop_back();
		}
		students.clear();
		courses.clear();
	}

	size_t Registrar::findStudent(const string& studentName) const {
		for (size_t index = 0; index < students.size(); ++index) {
			if (students[index]->getName() == studentName) {
				return index;
			}
		}
		return students.size();
	}

	size_t Registrar::findCourse(const string& courseName) const {
		for (size_t index = 0; index < courses.size(); ++index) {
			if (courses[index]->getName() == courseName) {
				return index;
			}
		}
		return courses.size();
	}


}