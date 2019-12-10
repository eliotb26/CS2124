//Eliot Brown
//rec02.cpp
//Lab 2

//Purpose: This program takes in a file from the user which is 
// of chemicals and their formulas and rearranges then in order
//of the lowest chemical formulas to the highest (lowest in Carbons).
// This also combines names if the formulas are the same thing and 
//prints it in the console. 

//NOTES
//Propyne C13H3
//ifs >> name  (gives: Propyne)  knows to stop when it sees a white space 
//ifs >> skip;   skip is C
// ifs >> numC    numC is now 13 
//ifs >> skip;  skip is H 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//structure of the vector made
struct chemicalsStruct {
	vector <string> names;
	//char element;
	int numC;
	//char secElement;
	int numH;
};

//opens the file and tries until it can  
void open(ifstream& chemFile);
// fills the vector with 
void fillVector(ifstream& chemFile, vector <chemicalsStruct>& 
	chemicalsVec);
//sorts the vector by lowest Carbon and Hydrogen amounts through
// bubble sort
void sortVec(vector <chemicalsStruct>& chemicalsVec);
// Displays the Vector made with the formula than the 
//possible names of that formula
void showVec(vector <chemicalsStruct> chemicalsVec);

//calls other functions and initializes a file and vector
int main() {
	// tell user to input a file 
	ifstream chemFile;
	open(chemFile);
	cout << "Sucess opening file" << endl;
	cout << endl;

	//initialize  TODO check if even need these here 
	vector <string> names;
	vector <chemicalsStruct> chemicalsVec;
	fillVector(chemFile, chemicalsVec);
	sortVec(chemicalsVec);
	showVec(chemicalsVec);

	chemFile.close();
}

//opens the file that the user input and tries until it can
void open(ifstream& chemFile) {
	//name of stream and name of the file
	string fileName;
	cout << "Input file name ";
	cin >> fileName;

	//checks if opened properly 
	chemFile.open(fileName);
	while (!chemFile) {
		fileName.clear();
		cerr << "Try again. ";
		cin >> fileName;
		chemFile.open(fileName); //trys to open again 
	}
}

// fills the vector with the information from the file
// adds names to the vector
void fillVector(ifstream& chemFile, vector <chemicalsStruct>& 
	chemicalsVec){
	string name;
	char skip;
	int numC;
	int numH;
	// goes through the file as long as it can read in these values
	while (chemFile >> name >> skip >> numC >> skip >> numH) {
		chemicalsStruct newChemical;
		newChemical.numC = numC;
		newChemical.numH = numH;
		newChemical.names.push_back(name);
		bool flag;
		flag = false;
		//goes through and pushes in the same names if they are for the 
		//same chemical equation
		for (size_t chemicalInd = 0; chemicalInd < chemicalsVec.size();
			++chemicalInd) {
			if (newChemical.numC == chemicalsVec[chemicalInd].numC && 
				newChemical.numH == chemicalsVec[chemicalInd].numH) {
				chemicalsVec[chemicalInd].names.push_back(name);
				flag = true; 
				break; 
			}
		}
		if (flag == false) {
			chemicalsVec.push_back(newChemical);  
		}
	}
}

// uses bubble sort to sort the vector based on the 
// values in the equation, ie. number of carbons and hydrogens
void sortVec(vector<chemicalsStruct>& chemicalsVec) {
	//bubble sort method
	for (size_t chemical = 0; chemical < chemicalsVec.size(); ++chemical) {
		for (size_t chemical2 = 0; chemical2 < chemicalsVec.size() - 1; ++chemical2) {
			if (chemicalsVec[chemical2].numC > chemicalsVec[chemical2 + 1].numC) {
				swap(chemicalsVec[chemical2], chemicalsVec[chemical2 + 1]);
			}
			//also checks difference of hydrogen numbers if the carbon numbers are 
			//the same in the chemical equation
			else if (chemicalsVec[chemical2].numC == chemicalsVec[chemical2].numC) {
				if (chemicalsVec[chemical2].numH > chemicalsVec[chemical2 + 1].numH) {
					swap(chemicalsVec[chemical2], chemicalsVec[chemical2 + 1]);
				}
			}
		}
	}
}

//displays the information in the vector and prints it to the console with the 
//formula formated first and then the names for that formula
void showVec(vector <chemicalsStruct> chemicalsVec) {
	//goes through vector and forms chemical equation 
	for (size_t chemicalInd = 0; chemicalInd < chemicalsVec.size();
		++chemicalInd) {
		cout << "C" << chemicalsVec[chemicalInd].numC << "H" << 
			chemicalsVec[chemicalInd].numH << " ";
		//then goes through and adds the names for that chemical equation
		for (size_t namesInd = 0; namesInd < chemicalsVec[chemicalInd].names.size();
			++namesInd) {
			cout << chemicalsVec[chemicalInd].names[namesInd] << " ";
		}
		cout << endl;
	}
}

