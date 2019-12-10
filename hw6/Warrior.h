//Warrior H

#ifndef WARRIOR_H
#define WARRIOR_H

#include <string>
#include <iostream>
#include <vector>

namespace WarriorCraft{
	class Noble;

	/*Warrior Class*/
	class Warrior {
		//output operator for Warrior 
		friend std::ostream& operator << (std::ostream& os, const Warrior& warrior);
	public:
		//warrior constructor 
		Warrior(const std::string& newName, int newStrength);
		//getters and setters for accessing 
		const int getStrength() const;
		void setStrength(int val);
		const std::string& getWarriorName() const;

		// hiring warrior methods
		bool setHired(bool Whired);
		Noble* setBoss(Noble* newBoss);
		const bool isHired() const;
		bool runaway();


	private:
		//fields in the Warrior class
		std::string name;
		int strength;
		Noble* boss;
		bool hired;
	};

}
#endif