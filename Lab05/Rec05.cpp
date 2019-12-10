/*
Eliot Brown 
rec05
CS - 2124 OOP

Purpose: To be able to track student records in 
class sections, through Instructors grade input
*/


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

/*Delegation; if class holds data, need to ask class to change it
Destructor: when class made things on the heap, only that 
class needs a destructor
Copy Constructor: copy student objects in heap, so that copy of section 
points to copy of student*/

//Class of the section which holds TimeSlot and Student Records in it
class Section{ 
	//output operator, how it prints when it is called 
	friend ostream& operator<<(ostream& os, const Section& rhs){
		os << "Section: " << rhs.theName << ", "<< rhs.SectionTime << " " ; 
		//checks if the vector is empty
		if (rhs.recordsVec.size() == 0) {
			os << "Students: None";
		}
		else {
			os << "Students: " << endl;
			//goes through the vector to dereference the students 
			for (size_t student = 0; student < rhs.recordsVec.size(); student++) {
				os << *(rhs.recordsVec[student]);
			}
		}
		return os;
	}
	class TimeSlot
	{
		//output operator when Timeslot is called 
		friend ostream& operator<<(ostream& os, const TimeSlot& rhs) {
			os << "Time slot: [Day: " << rhs.day << ", Start time: " << rhs.time; 
			if (rhs.time > 12) {
				os << "pm], ";
			}
			else {
				os << "am],";
			}
			return os;
		}
	public:
		//constructor
		TimeSlot(const string& aday, const int atime) {
			day = aday;
			time = atime;
		}
		
	private:
		//fields of the TimeSlot class
		string day;
		unsigned time;
	};

	//StudentRecord Class
	class StudentRecord {
		//how it prints when called 
		friend ostream& operator<<(ostream& os, const StudentRecord& aStudent) {
			os << "Name: " << aStudent.aname << ", Grades : ";
			//iterates through the vector to get student grade 
			for (size_t grade = 0; grade < aStudent.studentGrades.size()
				; grade++) {
				os << aStudent.studentGrades[grade] << " ";
			}
			os << endl;
			return os;
		}
	public:
		//Student record constructor 
		StudentRecord (const string& name, const int grade) {
			aname = name;
			agrade = grade;
			vector <int> vectorGrades(14, -1);
			studentGrades = vectorGrades;
		}
		//Get aname so can access it through the method
		const string getStudent() const { return aname; }

		//Adds grades to the vector for each week 
		void addGradeStudent(const int grade, const int week) {
			studentGrades[week-1] = grade;
		}


	private:
		//fields of the class Student Records
		string aname;
		int agrade;
		vector <int> studentGrades;
	};

public:
	//constructor
	Section(const string& section, const string& day, const int time)
		: SectionTime(day, time) {
		theName = section;
	}
	//Adds student to the vector of student pointers 
	void addStudent(const string& studentName) {
		StudentRecord* aStudent = new StudentRecord(studentName, -1); 
		recordsVec.push_back(aStudent);
	}

	void accessVector(const string name, const int grade, const int week) {
		for (size_t student = 0; student < recordsVec.size(); student++) {
			if (name == (recordsVec[student])->getStudent()) {
				recordsVec[student]->addGradeStudent(grade, week);
			}

		}
	}
	//Destructor, prints out what is being deleted and sets that 
	//the a nullpointer so no garabage data. 
	~Section() {
		cout << "Section " << theName << " is being deleted" << endl;
		for (size_t student = 0; student < recordsVec.size(); student++) {
			cout << "Deleting " << recordsVec[student]->getStudent() << endl;
			delete recordsVec[student];
			recordsVec[student] = nullptr;
		}
	}
	
	//Copy Constructor  --> says that it is optional on the
	//lab. Attempted it and was unsuccessful. 
	//It says that it is optional and I am getting an error on it
	//was looking at his code from class, and was wondering if 
	//I could get an explaination for it so I can understand
	/*
	Section(const Section& theSection) {
		for (size_t index = 0; index < theSection.recordsVec.size(); index ++) {
			recordsVec[index] = theSection.recordsVec[index]; 
		}
	}
	*/
	

private:
	string theName;
	TimeSlot SectionTime;
	vector <StudentRecord*> recordsVec; //student has vector of 
	//student grades, which is of pointers to mem
};


class LabWorker{
	//output operator and what it prints when it is called
	friend ostream& operator<<(ostream& os, const LabWorker& labWorker ) {
		//check if the section is a nullpointer
		if (labWorker.section == nullptr) {
			os << labWorker.LabWorkername << " does not have a section" << endl;
		}
		else {
			os << labWorker.LabWorkername << " has Section: " << *(labWorker.section);
		}
		return os;
	}
public:
	//constructor
	/*
	LabWorker(Section& theSection, const string& name) : section(nullptr){
		LabWorkername = name;
	}
	*/
	LabWorker(const string& name) : section(nullptr){
		LabWorkername = name;
	}

	//Add Section for the instructor 
	void addSection(Section& theSection) {
		//this will add the section to the labworker with all the students in it
		//points to the address of the section
		section = &theSection;

	}

	//This is the beginning of many calls to eventually add a grade, inputed
	//from the instructor
	void addGrade(const string name, const int grade, const int week) {
		//put in for that student then go into records and add to the 
		//index of the week-1 their grade 
		section->accessVector(name, grade, week);
	}

private:
	string LabWorkername;
	Section* section;
};



// Test code
void doNothing(Section sec) { 
	//cout << sec << endl; 
}

int main() {

	cout << "Test 1: Defining a section\n";
	Section secA2("A2", "Tuesday", 16);
	cout << secA2 << endl;

	cout << "\nTest 2: Adding students to a section\n";
	secA2.addStudent("John");
	secA2.addStudent("George");
	secA2.addStudent("Paul");
	secA2.addStudent("Ringo");
	cout << secA2 << endl;

	cout << "\nTest 3: Defining a lab worker.\n";
	LabWorker moe( "Moe" );
	cout << moe << endl;

	cout << "\nTest 4: Adding a section to a lab worker.\n";
	moe.addSection( secA2 );
	cout << moe << endl;

	cout << "\nTest 5: Adding a second section and lab worker.\n";
	LabWorker jane( "Jane" );
	Section secB3( "B3", "Thursday", 11 );
	secB3.addStudent("Thorin");
	secB3.addStudent("Dwalin");
	secB3.addStudent("Balin");
	secB3.addStudent("Kili");
	secB3.addStudent("Fili");
	secB3.addStudent("Dori");
	secB3.addStudent("Nori");
	secB3.addStudent("Ori");
	secB3.addStudent("Oin");
	secB3.addStudent("Gloin");
	secB3.addStudent("Bifur");
	secB3.addStudent("Bofur");
	secB3.addStudent("Bombur");
	jane.addSection( secB3 );
	cout << jane << endl;

	cout << "\nTest 6: Adding some grades for week one\n";
	moe.addGrade("John", 17, 1);  
	moe.addGrade("Paul", 19, 1);  
	moe.addGrade("George", 16, 1);  
	moe.addGrade("Ringo", 7, 1);  
	cout << moe << endl;

	cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
	moe.addGrade("John", 15, 3);  
	moe.addGrade("Paul", 20, 3);  
	moe.addGrade("Ringo", 0, 3);  
	moe.addGrade("George", 16, 3);  
	cout << moe << endl;

	cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
		<< "those students (or rather their records?)\n";

	cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
		<< "then make sure the following call works:\n";
	// doNothing(secA2);
	// cout << "Back from doNothing\n\n";

} // main
