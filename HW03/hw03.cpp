/*
Eliot Brown
HW03
DUE: September 29th

Purpose: This code has a purpose to open a file and store a warrior, 
their weapon and their weapons strength in a class (create an actual 
warrior). From this they also have a specific weapons information 
which reguards to their own strength. This code keeps track of the
warriors battling and can output their overall status's when called. 

*/


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


class WarriorInfo {
	friend ostream& operator<<(ostream& os, const WarriorInfo& theWarrior) {
		os << "Warrior: " << theWarrior.name << ", weapon: " 
			<< theWarrior.aWeapon.getName() << ", " 
			<< theWarrior.aWeapon.getStrength() << endl;
		return os;
	}

private:
	class Weapon {
		
	public:
		Weapon(string first, int second)
		: weaponName(first), weaponStrength(second) {}

		//getters and setters
		const int& getStrength() const {
			return weaponStrength;
		}
		const string& getName() const {
			return weaponName;
		}
		int& setStrength(int warriorStrength) {
			weaponStrength = warriorStrength; 
			return weaponStrength;
		}

	private:
		string weaponName;
		int weaponStrength;
	};

	//fields of WarriorInfo
	string name;
	Weapon aWeapon;


public:
	WarriorInfo(const string& aName, const string& weaponName, const int Strength)
		: name(aName), aWeapon(Weapon(weaponName, Strength)) {}

	//getters of the private variables
	const string& getName() const { return name; }	

	//shows the status of the warrior from the operator function
	void status(const WarriorInfo& theWarrior) {
		cout << theWarrior;
	}

	//Battle function to show the output of the battle
	void Battle(WarriorInfo& name1, WarriorInfo& name2) { 
			//prints who battles who
			cout << name1.name << " battles " << name2.name << endl;
			//these are if statements for each condition that they could
			//be battling in
			// first are to see if one of the warriors are already dead
			//if first warrior is dead
			if (name1.aWeapon.getStrength() == 0) {
				if (name2.aWeapon.getStrength() != 0) {
					cout << "He's dead, " << name2.name
						<< endl;
				}
				//if both are dead 
				else if (name2.aWeapon.getStrength() == 0) {
					cout << "Oh, NO! They're both dead! Yuck!" << endl;
				}
			}
			//if second warrior is dead
			else if (name2.aWeapon.getStrength() == 0) {
				if (name1.aWeapon.getStrength() != 0) {
					cout << "He's dead, " << name1.name
						<< endl;
				}
			}
			//these then are if both warriors are alive and 
			//need to compare and subtract strengths from each other
			else if (name1.aWeapon.getStrength() == name2.aWeapon.getStrength()) {
				name1.aWeapon.setStrength(0);
				name2.aWeapon.setStrength(0);
				cout << "Mutal Annihilation: " << name1.name
					<< " and " << name2.name
					<< " die at each other's hands" << endl;
			}
			//first warrior stronger than second
			// second warrior has 0 strength
			//first warrior looses second warriors strength
			else if (name1.aWeapon.getStrength() > name2.aWeapon.getStrength()) {
				name1.aWeapon.setStrength(name1.aWeapon.getStrength() - 
					name2.aWeapon.getStrength());
				name2.aWeapon.setStrength(0);
				cout << name1.name << " defeats " << name2.name << endl;
			}
			//second warrior stronger than first
			// first warrior has 0 strength
			//second warrior looses first warriors strength
			else if (name2.aWeapon.getStrength() > name1.aWeapon.getStrength()) {
				name2.aWeapon.setStrength((name2.aWeapon.getStrength() - 
					name1.aWeapon.getStrength()));
				name1.aWeapon.setStrength(0);
				cout << name2.name << " defeats " << name1.name << endl;
			}
		}
};


int main() {
	//open and check file if opened correctly
	ifstream warriorFile("warriorFile.txt");

	if (!warriorFile) {
		cerr << "Could not open the file. \n";
		exit(1);
	}

	string command;
	string name;
	string weaponName;
	int weaponStrength;
	vector <WarriorInfo> warriorVector;
	string name1, name2;
	int size;

	// goes through to file and checks what command is being made, 
	//either Warrior, Battle, or Status, then executes that command
	while (warriorFile >> command) {
		//each if compares the first word in the line
		//to see if its a Warrior, Status, or Battle
		//then calls that function 
		if (command == "Warrior") {
			warriorFile >> name >> weaponName >> weaponStrength;
			WarriorInfo newWarrior(name, weaponName, weaponStrength); 

			//adds to the vector the Warrior and its information
			warriorVector.push_back(newWarrior);
		}
		//if command is Battle 
		else if (command == "Battle") {
			warriorFile >> name1 >> name2;
			for (size_t ind = 0; ind < warriorVector.size(); ++ind) {
				if (warriorVector[ind].getName() == name1) {
					//warrior1 = warriorVector[ind];
					for (size_t sec = 0; sec < warriorVector.size(); ++sec) {
						if (warriorVector[sec].getName() == name2) {
							warriorVector[ind].Battle(warriorVector[ind], 
								warriorVector[sec]);
							break;
						}
					}
				}
			}
		}
		//if command is Status 
		else if (command == "Status") {
			size = warriorVector.size();
			cout << "There are: " << size << " warriors" << endl;
			//goes through the vector to call the status function to output 
			for (size_t i = 0; i < warriorVector.size(); ++i) {
				warriorVector[i].status(warriorVector[i]);  
				//this will call the status method in the class
			}
		}

	}
	warriorFile.close();
}
