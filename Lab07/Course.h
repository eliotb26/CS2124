#ifndef Course_h
#define Course_h

#include "Student.h"
#include "Registrar.h"
#include <ostream>
#include <string>
#include <vector>

namespace BrooklynPoly {
	class Student;
	class Registrar;

	class Course {
		friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
	public:
		// Course methods needed by Registrar
		Course(const std::string& courseName);
		const std::string& getName() const;
		bool addStudent(Student*);
		void removeStudentsFromCourse();

	private:
		std::string name;
		std::vector<Student*> students;
	};

}

#endif