/*
Eliot Brown
hw05
Due: 10/16/19

Purpose: To create Nobles that can hire and fire
warriors in their army. The nobles can then create
battle with other nobles and their armies.
This code shows the winners, keeps track of the armies,
and prints out errors for faulty input.

*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


class Noble;

//Warrior Class
class Warrior {
	//output operator for Warrior 
	friend ostream& operator << (ostream& os, const Warrior& warrior) {
		os << warrior.name << ": " << warrior.strength;
		return os;
	}

public:
	//warrior constructor 
	Warrior(const string& newName, int newStrength)
		: name(newName), strength(newStrength) {
		hired = false;
	}

	//getters and setters for accessing 
	const int getStrength() const { return strength; }
	void setStrength(int val) { strength = val; }
	const string& getWarriorName() const { return name; }
	//hiring warrior methods
	bool setHired(bool Whired) { 
		hired = Whired;
		return hired;
	}
	const bool isHired() const { return hired; }

private:
	//fields in the Warrior class
	string name;
	int strength;
	bool hired; 
};

//Noble class
class Noble {
	//output operator iterates through army vector 
	friend ostream& operator << (ostream& os, const Noble& noble) {
		os << noble.name << " has an army of " << noble.armyVector.size()
			<< endl;
		//iterates through the vector to print out
		for (size_t index = 0; index < noble.armyVector.size(); index++) {
			os << "\t" << *(noble.armyVector[index]) << endl;
		}
		return os;
	}

public:
	//constructor 
	Noble(const string& newNobleName) 
		: name(newNobleName){
		dead = false;
	}

	const vector <Warrior*>& getArmyVector() const { return armyVector; }
	bool isDead() { return dead; }
	const string& getNobleName() const { return name; }

	//hires a warrior, and checks if can be hired
	bool hire(Warrior& warrior) {
		if (warrior.getStrength() == 0) {
			cout << "Warrior is dead, cannot be hired." << endl;  
		}
		else if (warrior.isHired()) {
			cout << "Warrior already works for another noble." << endl;
		}
		if (dead) {
			cout << "Dead noble cannot hire a warrior." << endl;
		}
		else {
			//adds to a armyVector
			warrior.setHired(true);
			armyVector.push_back(&warrior);
			return true;
		}
		return false;
	}

	//Gets the army's strength so can access
	const int getArmyStrength() const {
		int armyStrength = 0;
		//iterates through the armyVector to get the whole armies
		//strength
		for (size_t index = 0; index < armyVector.size(); index++) {
			armyStrength += (armyVector[index])->getStrength();
		}
		return armyStrength;
	}

	//Sets the Armys strength by calling the setStrength 
	void setArmyStrength(double newStrength) {
		for (int index = 0; index < armyVector.size(); index++) {
			int ratio = newStrength * (armyVector[index])->getStrength();
			(armyVector[index])->setStrength(ratio);
		}
	}

	//fire by switching then popping the last index
	//also sets to a nullpointer before removing 
	//still has garbage on the heap, but I beleive the week this  
	//hw is for was before we learned it. 
	bool fire(Warrior& warrior) {
		for (size_t index = 0; index < armyVector.size(); index++) {
			if (armyVector[index] == &warrior) {
				cout << "You don't work for me anymore " <<
					(armyVector[index])->getWarriorName() << "! -- "
					<< name << endl;
				armyVector[index]->setHired(false);
				armyVector[index] = nullptr;
				armyVector[index], armyVector[armyVector.size() - 1] =
					armyVector[armyVector.size() - 1], armyVector[index];
				armyVector.pop_back();
				return true;
			}
		}
		cout << "warrior not found." << endl;
		return false;
	}

	//second part of the Battle method where the 
	//armies strength is greater than 0
	void armiesNotZero(Noble& otherNoble) {
		//if one army is stronger than the other
		if (getArmyStrength() > otherNoble.getArmyStrength()) {
		cout << name << " defeats " << otherNoble.name << endl;
		//This sets the new strength through the formula so it spreads
		//it evenly
		setArmyStrength(1 - (double(otherNoble.getArmyStrength()) /
			double(getArmyStrength())));
		otherNoble.setArmyStrength(0);
		otherNoble.dead = true;
		}
		//if one army is stronger than the other
		else if (getArmyStrength() < otherNoble.getArmyStrength()) {
		cout << otherNoble.name << " defeats " << name << endl;
		otherNoble.setArmyStrength(1 - (double(getArmyStrength()) /
			double(otherNoble.getArmyStrength())));
		setArmyStrength(0);
		dead = true;
		}
		//tests if army strengths are the same
		else if (getArmyStrength() == otherNoble.getArmyStrength()) {
			cout << "Mutual Annihalation: " << name << " and " <<
				otherNoble.name
				<< " die at each other's hands" << endl;
			setArmyStrength(0);
			dead = true;
			otherNoble.setArmyStrength(0);
			otherNoble.dead = true;
		}
	}

	void battle(Noble& otherNoble) {
		cout << name << " battles " << otherNoble.name << endl;
		//Tests to see if armies are both non zero in strength
		//shortens this battle function by half (makes both <40 lines)
		if ((getArmyStrength() != 0) && (otherNoble.getArmyStrength()
			!= 0)) {
			armiesNotZero(otherNoble);
		}
		else {
			//tests if both armys strengths are 0 
			if ((getArmyStrength() == 0) && (otherNoble.getArmyStrength()
				== 0)) {
				cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
			}
			//if one army is 0 strength
			else if (getArmyStrength() == 0) {
				cout << "He's dead " << otherNoble.name << endl;
			}
			//if one is 0 strength
			else if (otherNoble.getArmyStrength() == 0) {
				cout << "He's dead " << name << endl;
			}
		}
	}

private:
	vector<Warrior*> armyVector;
	string name;
	//keeps track if the Noble is dead or alive
	bool dead;
}; 

//returns the index that the warrior is found
size_t getWarriorInd(const string& warriorName,
	const vector<Warrior*>& warriorVector);

//returns the index that the noble is found
size_t getNobleInd(const string& nobleName,
	const vector<Noble*>& nobleVector);

//checks if the Noble exitsts already and returns a bool 
bool nobleExists(const string& nobleName,
	const vector<Noble*>& nobleVector);

//checks if the Warrior exitsts already and returns a bool 
bool warriorExists(const string& warriorName,
	const vector<Warrior*>& warriorVector);

//removes all of the warriors and clears the vector
void removeWarriors(vector<Warrior*>& warriorVector);

//removes all of the nobles and clears the vector
void removeNobles(vector<Noble*>& nobleVector);

//Checks to see if a Noble can hire the warrior, then hires
void Hire(const string& nobleName, const string& warriorName,
	const vector <Warrior*>& warriorVector, const vector<Noble*>&
	nobleVector);

//This saves lines in the main, finds the warrior and noble
//and passes them into the method in Noble
void Fire(const string& nobleName, const string& warriorName,
	const vector <Warrior*>& warriorVector,
	const vector<Noble*>& nobleVector);

//Outputs the status of the Nobles and their armies
void Status(const vector <Warrior*>& warriorVector,
	const vector<Noble*>& nobleVector);

//Checks if noble exist and calls method Battle
void BattleFunc(const string& firstNobleName,
	const string& secNobleName,
	const vector<Noble*> nobleVector);


int main() {
	ifstream file("nobleWarriors.txt");

	if (!file) {
		cerr << "Could not open the file. \n";
		exit(1);
	}
	vector <Warrior*> warriorVector;
	vector <Noble*> nobleVector;
	string command;
	string nobleName;
	string warriorName;
	int strength;
	bool Nexists = false; 
	bool Wexists = false;
	while (file >> command) {
		/*int count = 0;*/
		if (command == "Noble") {
			file >> nobleName;
			if (nobleVector.size() == 0) {
				Noble* noblePoint = new Noble(nobleName);
				nobleVector.push_back(noblePoint);
			}
			else {
				Nexists = nobleExists(nobleName, nobleVector);
				if (Nexists == false) {
					Noble* noblePointer = new Noble(nobleName);
					nobleVector.push_back(noblePointer);
				}
				else {
					cout << "Noble already exists" << endl;
				}
			}
		}
		else if (command == "Warrior") {
			file >> warriorName >> strength;
			if (warriorVector.size() == 0) {
				Warrior* warriorPoint = new Warrior(warriorName, strength);
				warriorVector.push_back(warriorPoint);
			}
			else {
				Wexists = warriorExists(warriorName, warriorVector);
				if (Wexists == false) {
					Warrior* warriorPoint = new Warrior(warriorName,
						strength);
					warriorVector.push_back(warriorPoint);
				}
				else {
					cout << "Warrior already exists" << endl;
				}
			}
		}
		else if (command == "Hire") {
			file >> nobleName >> warriorName;
			//calls Hire function which runs the checks 
			Hire(nobleName, warriorName, warriorVector, nobleVector);
		}
		else if (command == "Status") {
			cout << "Status\n" << "======\n" << "Nobles: \n";
			//calls the Status function 
			Status(warriorVector, nobleVector);
		}
		else if (command == "Fire") {
			file >> nobleName >> warriorName;
			//calls Fire function which makes the first checks 
			Fire(nobleName, warriorName, warriorVector, nobleVector);
		}
		else if (command == "Battle") {
			string firstNobleName; 
			string secNobleName;
			file >> firstNobleName >> secNobleName;
			BattleFunc(firstNobleName, secNobleName, nobleVector);
		}
		else if (command == "Clear") {
			removeNobles(nobleVector);
			removeWarriors(warriorVector);
		}
	}
}



//returns the index that the warrior is found
size_t getWarriorInd(const string& warriorName,
	const vector<Warrior*>& warriorVector) {
	for (size_t index = 0; index < warriorVector.size(); ++index) {
		if (warriorVector[index]->getWarriorName() == warriorName) {
			return index;
		}
	}
	cout << "Warrior does not exist!" << endl;
	return -1;
}

//returns the index that the noble is found
size_t getNobleInd(const string& nobleName,
	const vector<Noble*>& nobleVector) {
	for (size_t index = 0; index < nobleVector.size(); ++index) {
		if (nobleVector[index]->getNobleName() == nobleName) {
			return index;
		}
	}
	cout << "Noble does not exist!" << endl;
	return -1;
}

//checks if the Noble exitsts already and returns a bool 
bool nobleExists(const string& nobleName,
	const vector<Noble*>& nobleVector) {
	for (size_t index = 0; index < nobleVector.size(); ++index) {
		if (nobleVector[index]->getNobleName() == nobleName) {
			return true;
		}
	}
	return false;
}

//checks if the Warrior exitsts already and returns a bool 
bool warriorExists(const string& warriorName,
	const vector<Warrior*>& warriorVector) {
	for (size_t index = 0; index < warriorVector.size(); ++index) {
		if (warriorVector[index]->getWarriorName() == warriorName) {
			return true;
		}
	}
	return false;
}
//removes all of the warriors and clears the vector
void removeWarriors(vector<Warrior*>& warriorVector) {
	for (size_t index = 0; index < warriorVector.size(); ++index) {
		delete (warriorVector[index]);
		warriorVector[index] = nullptr;
	}
	warriorVector.clear();
}
//removes all of the nobles and clears the vector
void removeNobles(vector<Noble*>& nobleVector) {
	for (size_t index = 0; index < nobleVector.size(); ++index) {
		delete (nobleVector[index]);
		nobleVector[index] = nullptr;
	}
	nobleVector.clear();
}

void Hire(const string& nobleName, const string& warriorName,
	const vector <Warrior*>& warriorVector, const vector<Noble*>&
	nobleVector) {
	bool Wexists = warriorExists(warriorName, warriorVector);
	bool Nexists = nobleExists(nobleName, nobleVector);
	if (Wexists == false) {
		cout << "Warrior does not exist" << endl;
	}
	else if (Nexists == false) {
		cout << "Noble does not exist" << endl;
	}
	else {
		size_t nobleInd = getNobleInd(nobleName, nobleVector);
		size_t warriorInd = getWarriorInd(warriorName, warriorVector);
		nobleVector[nobleInd]->hire(*(warriorVector[warriorInd]));
	}
}

//This saves lines in the main, finds the warrior and noble
//and passes them into the method in Noble
void Fire(const string& nobleName, const string& warriorName,
	const vector <Warrior*>& warriorVector,
	const vector<Noble*>& nobleVector) {
	bool Nexists = nobleExists(nobleName, nobleVector);
	bool Wexists = warriorExists(warriorName, warriorVector);
	if (Nexists == false) {
		cout << "Noble does not exist" << endl;
	}
	else if (Wexists == false) {
		cout << "Warrior does not exist" << endl;
	}
	size_t nobleIndex = getNobleInd(nobleName, nobleVector);
	size_t warriorIndex = getWarriorInd(warriorName, warriorVector);
	nobleVector[nobleIndex]->fire(*(warriorVector[warriorIndex]));
}

void Status(const vector <Warrior*>& warriorVector,
	const vector<Noble*>& nobleVector) {
	unsigned count = 0;
	if (nobleVector.size() > 0) {
		for (size_t index = 0; index < nobleVector.size(); ++index) {
			cout << *(nobleVector[index]);
			//calls ouput operator for each noble
		}
	}
	else {
		cout << "NONE" << endl;
	}
	cout << "Unemployed Warriors:\n";
	//checks if has a leaded and therefore is unemployed
	for (size_t index = 0; index < warriorVector.size(); ++index) {
		if (warriorVector[index]->isHired() == false) {
			cout << *(warriorVector[index]) << endl;
			count += 1;
		}
	}
	if (count == 0) { cout << "NONE" << endl; }
}

void BattleFunc(const string& firstNobleName, 
	const string& secNobleName, 
	const vector<Noble*> nobleVector) {
	bool first = true;
	bool second = true;
	first = nobleExists(firstNobleName, nobleVector);
	second = nobleExists(secNobleName, nobleVector);
	if (first == false) {
		cout << "First noble does not exist" << endl;
	}
	else if (second == false) {
		cout << "Second noble does not exist" << endl;
	}
	else {
		//gets the pointers to the Nobles 
		size_t firstNobleInd = getNobleInd(firstNobleName, nobleVector);
		size_t secNobleInd = getNobleInd(secNobleName, nobleVector);
		nobleVector[firstNobleInd]->battle(*(nobleVector[secNobleInd]));
	}
}