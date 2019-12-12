//Warrior CPP 

#include "Protector.h"
#include "Noble.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;


namespace WarriorCraft {

	Protector::Protector(const string& newName, int newStrength)
		: name(newName), strength(newStrength), hired(false)
		, boss(nullptr) {}

	ostream& operator << (ostream& os, const Protector& protector) {
		os << protector.getWarriorName() << ": " << protector.getStrength();
		return os;
	}

	const int Protector::getStrength() const { return strength; }
	void Protector::setStrength(int val) { strength = val; }
	const string& Protector::getWarriorName() const { return name; }
	const string& Protector::getBossName() const {
		return boss->getNobleName();
	}

	//hiring warrior methods
	bool Protector::setHired(bool Whired) {
		hired = Whired;
		return hired;
	}
	Noble* Protector::setBoss(Noble* newBoss) {
		boss = newBoss;
		return boss;
	}
	const bool Protector::isHired() const { return hired; }

	//allows the warrior to runaway by removing him first from the armyvector
	bool Protector::runaway() {
		if (hired) {
			bool result = boss->removeWarrior(*this);
			if (result) {
				cout << name << " flees in terror, aboandoning his lord, " <<
					boss->getNobleName() << endl;
				return true;
			}
		}
		return false;
	}
	void Protector::displayBattleCry() const {
		cout << "enter display" << endl;
	 }



	Wizard::Wizard(const std::string& name, int strength) : Protector(name, strength){}
	void Wizard::displayBattleCry() const{
		cout << "POOF" << endl;
	}



	Warrior::Warrior(const std::string& name, int strength) : Protector(name, strength) {}
	void Warrior::displayBattleCry() const {
		cout << getWarriorName() << " says: Take that in the name of my lord, "
			<< getBossName() << endl;
	}


	Archer::Archer(const std::string& name, int strength) : Warrior(name, strength) {}
	void Archer::displayBattleCry() const{
		cout << "TWANG!";
		Warrior::displayBattleCry();
	}


	Swordsman::Swordsman(const std::string& name, int strength) : Warrior(name, strength) {}
	void Swordsman::displayBattleCry() const {
		cout << "CLANG!";
		Warrior::displayBattleCry();
	}

}