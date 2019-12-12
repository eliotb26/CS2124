// NOBLE CPP

#include "Noble.h"
#include "Protector.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;


namespace WarriorCraft {

	Noble::Noble(const string& newNobleName) :
		name(newNobleName), dead(false) {}
	ostream& operator << (ostream& os, const Noble& noble) {
		os << noble.getNobleName() << " has an army of " << endl;
		return os;
	}
	const bool Noble::isDead() const { return dead; }
	bool Noble::setDead(bool val) { 
		dead = val;
		return dead;
	}
	const string& Noble::getNobleName() const { return name; }



	//second part of the Battle method where the 
	//armies strength is greater than 0
	void Noble::armiesNotZero(Noble& otherNoble) {
		//if one army is stronger than the other
		if (getArmyStrength() > otherNoble.getArmyStrength()) {
			Noise();
			otherNoble.Noise();
			cout << getNobleName() << " defeats " << otherNoble.getNobleName() << endl;
			//This sets the new strength through the formula so it spreads
			//it evenly
			setArmyStrength(1 - ((double)(otherNoble.getArmyStrength())) /
				((double)(getArmyStrength())));
			otherNoble.setArmyStrength(0);
			otherNoble.setDead(true);
		}
		//if one army is stronger than the other
		else if (getArmyStrength() < otherNoble.getArmyStrength()) {
			Noise();
			otherNoble.Noise();
			cout << otherNoble.getNobleName() << " defeats " << getNobleName() << endl;
			otherNoble.setArmyStrength((1 - ((double)getArmyStrength()) /
				((double)(otherNoble.getArmyStrength()))));
			setArmyStrength(0);
			setDead(true);
		}
		//tests if army strengths are the same
		else if (getArmyStrength() == otherNoble.getArmyStrength()) {
			Noise();
			otherNoble.Noise();
			cout << "Mutual Annihalation: " << getNobleName() << " and " <<
				otherNoble.getNobleName()
				<< " die at each other's hands" << endl;
			setArmyStrength(0);
			setDead(true);
			otherNoble.setArmyStrength(0);
			otherNoble.setDead(true);
		}
	}

	void Noble::battle(Noble& otherNoble) {
		cout << getNobleName() << " battles " << otherNoble.getNobleName() << endl;
		//Tests to see if armies are both non zero in strength
		//shortens this battle function by half (makes both <40 lines)
		if (!dead && !otherNoble.dead) {
			armiesNotZero(otherNoble);
		}
		else {
			//tests if both armys strengths are 0 
			if ((dead) && (otherNoble.dead)) {
				cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
			}
			//if one army is 0 strength
			else if (dead) {
				cout << "He's dead " << otherNoble.getNobleName() << endl;
			}
			//if one is 0 strength
			else if (otherNoble.dead) {
				cout << "He's dead " << getNobleName() << endl;
			}
		}
	}



	//Lord 
	Lord::Lord(const string name) : Noble(name) {}
	//Gets the army's strength so can access
	const int Lord::getArmyStrength() const {
		int armyStrength = 0;
		//iterates through the armyVector to get the whole armies
		//strength
		for (size_t index = 0; index < armyVector.size(); index++) {
			armyStrength += (armyVector[index])->getStrength();
		}
		return armyStrength;
	}

	//Sets the Armys strength by calling the setStrength 
	void Lord::setArmyStrength(double newStrength) {
		for (int index = 0; index < armyVector.size(); index++) {
			int ratio = newStrength * (armyVector[index])->getStrength();
			(armyVector[index])->setStrength(ratio);
		}
	}

	//hires a warrior, and checks if can be hired
	bool Lord::hires(Protector& protector) {
		if (protector.getStrength() == 0) {
			cout << "Warrior is dead, cannot be hired." << endl;
		}
		else if (protector.isHired()) {
			cout << "Warrior already works for another noble." << endl;
		}
		if (isDead()) {
			//cout << "Dead noble cannot hire a warrior." << endl;
			return false;
		}
		else {
			//adds to a armyVector
			//protector.setHired(true);
			protector.setBoss(this);
			armyVector.push_back(&protector);
			return true;
		}
		return false;
	}
	bool Lord::removeWarrior(Protector& protector) {
		for (size_t index = 0; index < armyVector.size(); index++) {
			if (armyVector[index] == &protector) {
				armyVector[index]->setHired(false);
				armyVector[index] = nullptr;
				while (size_t ind = 0 < armyVector.size()){
					armyVector[index], armyVector[ind] = armyVector[ind], armyVector[index];
					index += 1;
				}
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
	bool Lord::fire(Protector& protector) {
		bool result = removeWarrior(protector);
		if (result) {
			cout << "You don't work for me anymore " <<
				protector.getWarriorName() << "! -- "
				<< getNobleName() << endl;
			return true;
		}
		cout << "warrior not found." << endl;
		return false;
	}
	void Lord::Noise() const {
		for (size_t index = 0; index < armyVector.size(); index++) {
			armyVector[index]->displayBattleCry();
		}
	}




	//PersonWithStrengthToFight
	PersonWithStrengthToFight::PersonWithStrengthToFight(const string name, int strength)
		: Noble(name), strength(strength){
		}
	//Gets the army's strength so can access
	const int PersonWithStrengthToFight::getArmyStrength() const {
		return strength;
	}
	void PersonWithStrengthToFight::setArmyStrength(double newStrength) {  
		strength = newStrength;
	}
	bool PersonWithStrengthToFight::removeWarrior(Protector& protector) {
		return false;
	}

	void PersonWithStrengthToFight::battleOutput() const{
		cout << "UGH!" << endl;
	}
	void PersonWithStrengthToFight::Noise() const {
		battleOutput();
	}

}