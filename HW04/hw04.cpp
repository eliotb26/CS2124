/*
Eliot Brown 
HW 04 
October 7th 2019

Purpose: This is a code for the purpose of tracking battles between 
nobles who have warriors. The battle is won by the noble with greater
strength in their army of the warriors. The damage done in the battle 
is evenly distributed through the warriors in the winning army. 
The noble can hire and fire warriors. 

*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Warrior Class
class Warrior {
	//output operator for Warrior 
	friend ostream& operator << (ostream& os, const Warrior& warrior) {
		os << warrior.name << ": " << warrior.strength;
		return os;
	}

public:
	//warrior constructor 
	Warrior(const string& newName, int newStrength) {
		name = newName; 
		strength = newStrength;
		hired = false;
	}

	//getters and setters for accessing 
	const int getStrength() const { return strength; }
	void setStrength(int val) { strength = val; }
	const string getName() const { return name; }
	//hiring warrior methods
	void hireWarrior() { hired = true; }
	void fireWarrior() { hired = false; }
	bool isHired() { return hired; }

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
			os << "    " << *(noble.armyVector[index]) << endl;
		}
		return os;
	}

public:
	//constructor 
	Noble(const string& newNobleName) {
		name = newNobleName;
		dead = false;
	}

	bool isDead() { return dead; }

	//hires a warrior, and checks if can be hired
	void hire(Warrior& warrior) {
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
			warrior.hireWarrior();
			armyVector.push_back(&warrior);
		}
	}

	//fire by switching then popping the last index
	//also sets to a nullpointer before removing 
	//still has garbage on the heap, but I beleive the week this  
	//hw is for was before we learned it. 
	void fire(Warrior& warrior) {
		for (size_t index = 0; index < armyVector.size(); index++) {
			if (armyVector[index] == &warrior) {
				cout << "You don't work for me anymore " << 
					(armyVector[index])->getName() << "! -- " << name << endl; 
				armyVector[index] = nullptr; 
				armyVector[index], armyVector[armyVector.size() - 1] = 
					armyVector[armyVector.size() - 1], armyVector[index];
				armyVector.pop_back();
				return;
			}
		}
		cout << "warrior not found." << endl;
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

	void battle(Noble& otherNoble) {
		cout << name << " battles " << otherNoble.name << endl;
		//tests if both armys strengths are 0 
		if ((getArmyStrength() == 0) && (otherNoble.getArmyStrength()
			== 0)) {
			cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
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
		//if one army is 0 strength
		else if (getArmyStrength() == 0) {
			cout << "He's dead " << otherNoble.name << endl;
		}
		//if one is 0 strength
		else if (otherNoble.getArmyStrength() == 0) {
			cout << "He's dead " << name << endl;
		}
		//if one army is stronger than the other
		else if (getArmyStrength() > otherNoble.getArmyStrength()) {
			cout << name << " defeats " << otherNoble.name << endl;
			//This sets the new strength through the formula so it spreads
			//it evenly
			setArmyStrength(1 - (double(otherNoble.getArmyStrength())/
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
	}


private:
	vector<Warrior*> armyVector;
	string name;
	//keeps track if the Noble is dead or alive
	bool dead; 

};


int main() {

	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	cout << "==========\n"
		<< "Status before all battles, etc.\n";
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
	cout << "==========\n";

	art.fire(cheetah);
	cout << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

	cout << "==========\n"
		<< "Status after all battles, etc.\n";
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
	cout << "==========\n";

}