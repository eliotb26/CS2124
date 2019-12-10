//Warrior CPP 

#include "Warrior.h"
#include "Noble.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;


namespace WarriorCraft {

	Warrior::Warrior(const string& newName, int newStrength)
		: name(newName), strength(newStrength), hired(false)
		, boss(nullptr) {}

	ostream& operator << (ostream& os, const Warrior& warrior) {
		os << warrior.getWarriorName() << ": " << warrior.getStrength();
		return os;
	}

	const int Warrior::getStrength() const { return strength; }
	void Warrior::setStrength(int val) { strength = val; }
	const string& Warrior::getWarriorName() const { return name; }


	//hiring warrior methods
	bool Warrior::setHired(bool Whired) {
		hired = Whired;
		return hired;
	}
	Noble* Warrior::setBoss(Noble* newBoss) {
		boss = newBoss;
		return boss;
	}
	const bool Warrior::isHired() const { return hired; }

	//allows the warrior to runaway by removing him first from the armyvector
	bool Warrior::runaway() {
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
}
