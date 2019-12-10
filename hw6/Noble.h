//NOBLE H

#ifndef NOBLE_H
#define NOBLE_H

#include <string>
#include <iostream>
#include <vector>

namespace WarriorCraft {
	class Warrior;

	class Noble {
		//output operator iterates through army vector 
		friend std::ostream& operator << (std::ostream& os, const Noble& noble);
		
	public:
		//constructor 
		Noble(const std::string& newNobleName);

		//const vector <Warrior*>& getArmyVector() const { return armyVector; }
		const bool isDead ();
		const std::string& getNobleName() const;

		//hires a warrior, and checks if can be hired
		bool hire(Warrior& warrior);

		//Gets the army's strength so can access
		const int getArmyStrength() const;

		//Sets the Armys strength by calling the setStrength 
		void setArmyStrength(double newStrength);

		bool removeWarrior(Warrior& warrior);

		//fire by switching then popping the last index
		//also sets to a nullpointer before removing 
		//still has garbage on the heap, but I beleive the week this  
		//hw is for was before we learned it. 
		bool fire(Warrior& warrior);

		//second part of the Battle method where the 
		//armies strength is greater than 0
		void armiesNotZero(Noble& otherNoble);

		void battle(Noble& otherNoble);

	private:
		std::vector<Warrior*> armyVector;
		std::string name;
		//keeps track if the Noble is dead or alive
		bool dead;
	};
}

#endif