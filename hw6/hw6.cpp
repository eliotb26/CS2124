//Eliot Brown 
//HW 6
//This uses seperate compilation to create Nobles that can
//hire and fire
//warriors in their army. The warriors are also able now
//to run away from their army. The nobles can then create
//battle with other nobles and their armies.
//This code shows the winners, keeps track of the armies,
//and prints out errors for faulty input.

//10/28/19

#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace WarriorCraft;



int main() {
	vector <Warrior*> warriorVector;
	vector <Noble*> nobleVector;
	bool Nexists = false;
	bool Wexists = false;
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

	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;

	cheetah.runaway();
	cout << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
}