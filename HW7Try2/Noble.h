#pragma once

//NOBLE H

#ifndef NOBLE_H
#define NOBLE_H

#include <string>
#include <iostream>
#include <vector>

namespace WarriorCraft {
	class Protector;

	class Noble {
		//output operator iterates through army vector 
		friend std::ostream& operator << (std::ostream& os, const Protector& protector);

	public:
		//constructor 
		Noble(const std::string& newNobleName);

		//const vector <Warrior*>& getArmyVector() const { return armyVector; }
		const bool isDead() const;
		bool setDead(bool val);
		const std::string& getNobleName() const;

		//Gets the army's strength so can access
		virtual const int getArmyStrength() const = 0; 

		//Sets the Armys strength by calling the setStrength 
		virtual void setArmyStrength(double newStrength) = 0;

		virtual bool removeWarrior(Protector& protector) = 0;

		void armiesNotZero(Noble& otherNoble);
		void battle(Noble& otherNoble);
		virtual void Noise() const = 0;

	private:
		std::string name;
		//keeps track if the Noble is dead or alive
		bool dead;
	};

	class Lord : public Noble {
	public: 
		Lord(const std::string name);
		const int getArmyStrength() const;
		void setArmyStrength(double newStrength);
		//hires a warrior, and checks if can be hired
		bool hires(Protector& protector);
		bool removeWarrior(Protector& protector);
		//fire by switching then popping the last index
		//also sets to a nullpointer before removing 
		//still has garbage on the heap, but I beleive the week this  
		//hw is for was before we learned it. 
		bool fire(Protector& protector);
		void Noise() const;
	

	private:
		std::vector<Protector*> armyVector;
	};

	class PersonWithStrengthToFight : public Noble { 
	public: 
		PersonWithStrengthToFight(const std::string name, int strength);
		const int getArmyStrength() const;
		void setArmyStrength(double newStrength);
		bool removeWarrior(Protector& protector);
		void battleOutput() const;
		void Noise() const;

	private:
		int strength;
	};

}

#endif
