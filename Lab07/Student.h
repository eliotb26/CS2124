#ifndef Student_H
#define Student_H

#include "Course.h"
#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly {
	class Course; //forward declaration

	class Student {
		friend std::ostream& operator<<(std::ostream& os, const Student& rhs);
	public:
		// Student methods needed by Registrar
		Student(const std::string& name);
		const std::string& getName() const;
		bool addCourse(Course* coursePoint);

		// Student method needed by Course
		void removedFromCourse(Course* coursePoint);

	private:
		std::string name;
		std::vector<Course*> courses;
	};

}

#endif
