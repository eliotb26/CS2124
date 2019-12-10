/*
Eliot Brown
rec07

Purpose: 
Create a registery of student with their classes
in multiple files/seperate compliation. There is 8 files
with one file containing everything and 7 others which are 
seperate classes. 

*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
	friend ostream& operator<<(ostream& os, const Course& rhs);
public:
	// Course methods needed by Registrar
	Course(const string& courseName);
	const string& getName() const;
	bool addStudent(Student*);
	void removeStudentsFromCourse();

private:
	string name;
	vector<Student*> students;
};

class Student {
	friend ostream& operator<<(ostream& os, const Student& rhs);
public:
	// Student methods needed by Registrar
	Student(const string& name);
	const string& getName() const;
	bool addCourse(Course*);

	// Student method needed by Course
	void removedFromCourse(Course*);

private:
	string name;
	vector<Course*> courses;
};

class Registrar {   //on heap, purge clears up heap space like the deconstructor 
	friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
	Registrar();
	bool addCourse(const string&);
	bool addStudent(const string&);
	bool enrollStudentInCourse(const string& studentName,
		const string& courseName);
	bool cancelCourse(const string& courseName);
	void purge();

private:
	size_t findStudent(const string&) const;
	size_t findCourse(const string&) const;

	vector<Course*> courses;
	vector<Student*> students;
};

//METHODS 
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

//STUDENT METHODS
	// Student methods needed by Registrar
Student::Student(const string& name) : name(name){}
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
const string& Student::getName() const{
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

// Student method needed by Course
void Student::removedFromCourse(Course* coursePoint) {
	for (size_t index = 0; index < courses.size(); ++index) {
		if (coursePoint == courses[index]) {
			swap(*courses[index], *courses[courses.size()-1]);
		}
	}
	courses.pop_back();
}

//Registrar method
Registrar::Registrar() {}
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
		swap(courses[courseIndex], courses[courses.size()-1]);
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


int main() {

	Registrar registrar;

	cout << "No courses or students added yet\n";
	cout << registrar << endl;

	cout << "AddCourse CS101.001\n";
	registrar.addCourse("CS101.001");
	cout << registrar << endl;

	cout << "AddStudent FritzTheCat\n";
	registrar.addStudent("FritzTheCat");
	cout << registrar << endl;

	cout << "AddCourse CS102.001\n";
	registrar.addCourse("CS102.001");
	cout << registrar << endl;

	cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
	registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
	cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
	registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
	cout << registrar << endl;

	cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
	cout << "Should fail, i.e. do nothing, "
		<< "since Bullwinkle is not a student.\n";
	registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
	cout << registrar << endl;

	cout << "CancelCourse CS102.001\n";
	registrar.cancelCourse("CS102.001");
	cout << registrar << endl;

	/*
	// [OPTIONAL - do later if time]
	cout << "ChangeStudentName FritzTheCat MightyMouse\n";
	registrar.changeStudentName("FritzTheCat", "MightyMouse");
	cout << registrar << endl;

	cout << "DropStudentFromCourse MightyMouse CS101.001\n";
	registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
	cout << registrar << endl;

	cout << "RemoveStudent FritzTheCat\n";
	registrar.removeStudent("FritzTheCat");
	cout << registrar << endl;
	*/

	cout << "Purge for start of next semester\n";
	registrar.purge();
	cout << registrar << endl;
}

