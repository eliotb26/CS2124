#pragma once
//Warrior H

#ifndef PROTECTOR_H
#define PROTECTOR_H	

#include <string>
#include <iostream>
#include <vector>

namespace WarriorCraft {
	class Noble;

	/*Protector Class*/
	class Protector {
		//output operator for Warrior 
		friend std::ostream& operator << (std::ostream& os, const Protector& protector);
	public:
		//warrior constructor 
		Protector(const std::string& newName, int newStrength);
		//getters and setters for accessing 
		const int getStrength() const;
		void setStrength(int val);
		const std::string& getWarriorName() const;
		const std::string& getBossName() const;

		// hiring warrior methods
		bool setHired(bool Whired);
		Noble* setBoss(Noble* newBoss);
		const bool isHired() const;
		bool runaway();
		virtual void displayBattleCry() const;

	private:
		//fields in the Warrior class
		std::string name;
		int strength;
		Noble* boss;
		bool hired;
	};

	class Wizard : public Protector {
	public: 
		Wizard(const std::string& name, int strength);
		void displayBattleCry() const;

	private: 
	};

	class Warrior : public Protector {
	public: 
		Warrior(const std::string& name, int strength);
		void displayBattleCry()const;
	private: 

	};

	class Archer : public Warrior {
	public:
		Archer(const std::string& name, int strength);
		void displayBattleCry() const;

	private:

	};

	class Swordsman : public Warrior {
	public: 
		Swordsman(const std::string& name, int strength);
		void displayBattleCry()const;
	private: 

	};

}
#endif