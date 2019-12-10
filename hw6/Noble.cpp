//NOBLE CPP

#include "Noble.h"
#include "Warrior.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;


namespace WarriorCraft {

	Noble::Noble(const string& newNobleName) :
		name(newNobleName), dead(false) {}
	ostream& operator << (ostream& os, const Noble& noble) {
		os << noble.name << " has an army of " << noble.armyVector.size()
			<< endl;
		//iterates through the vector to print out
		for (size_t index = 0; index < noble.armyVector.size(); index++) {
			os << "\t" << *(noble.armyVector[index]) << endl;
		}
		return os;
	}
	const bool Noble::isDead() { return dead; }
	const string& Noble::getNobleName() const { return name; }

	//hires a warrior, and checks if can be hired
	bool Noble::hire(Warrior& warrior) {
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
			warrior.setBoss(this);
			armyVector.push_back(&warrior);
			return true;
		}
		return false;
	}


	//Gets the army's strength so can access
	const int Noble::getArmyStrength() const {
		int armyStrength = 0;
		//iterates through the armyVector to get the whole armies
		//strength
		for (size_t index = 0; index < armyVector.size(); index++) {
			armyStrength += (armyVector[index])->getStrength();
		}
		return armyStrength;
	}

	//Sets the Armys strength by calling the setStrength 
	void Noble::setArmyStrength(double newStrength) {
		for (int index = 0; index < armyVector.size(); index++) {
			int ratio = newStrength * (armyVector[index])->getStrength();
			(armyVector[index])->setStrength(ratio);
		}
	}

	bool Noble::removeWarrior(Warrior& warrior) {
		for (size_t index = 0; index < armyVector.size(); index++) {
			if (armyVector[index] == &warrior) {
				armyVector[index]->setHired(false);
				armyVector[index] = nullptr;
				swap(armyVector[index], armyVector[armyVector.size() - 1]);
				armyVector.pop_back();
				return true;
			}
		}
		return false;
	}

	//fire by switching then popping the last index
	//also sets to a nullpointer before removing 
	//still has garbage on the heap, but I beleive the week this  
	//hw is for was before we learned it. 
	bool Noble::fire(Warrior& warrior) {
		bool result = removeWarrior(warrior);
		if (result) {
			cout << "You don't work for me anymore " << 
				warrior.getWarriorName() << "! -- "
				<< name << endl;
			return true;
		}
		cout << "warrior not found." << endl;
		return false;
	}

	//second part of the Battle method where the 
	//armies strength is greater than 0
	void Noble::armiesNotZero(Noble& otherNoble) {
		//if one army is stronger than the other
		if (getArmyStrength() > otherNoble.getArmyStrength()) {
			cout << name << " defeats " << otherNoble.name << endl;
			//This sets the new strength through the formula so it spreads
			//it evenly
			setArmyStrength(1 - ((double)(otherNoble.getArmyStrength())) /
				((double)(getArmyStrength())));
			otherNoble.setArmyStrength(0);
			otherNoble.dead = true;
		}
		//if one army is stronger than the other
		else if (getArmyStrength() < otherNoble.getArmyStrength()) {
			cout << otherNoble.name << " defeats " << name << endl;
			otherNoble.setArmyStrength((1 - ((double)getArmyStrength()) /
				((double)(otherNoble.getArmyStrength()))));
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
	void Noble::battle(Noble& otherNoble) {
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
}