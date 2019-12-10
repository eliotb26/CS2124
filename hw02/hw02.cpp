/*
Eliot Brown
hw02.cpp

Purpose: The purpose is to get a file which has warriors and their 
strengths and to show their status and show the results of them 
battling. It then shows the final status of all of the warriors
after all of the battles are complete. 


Notes: 
get to choose the name 
If loose to opponent with more strength then die
if loose to less strength, then looses the strength of opponent
if have same strength then both loose
Doesnt require any strength to pick a fight


ONLY USE TECHNIQUES FROM LAST WEEK 

*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct WarriorInfo{
	string name;
	int strength;
};

//This is the battles, where it matches up the people with who they battle
//gives the output of the result of the battle
void Battle(string& name1, string& name2, vector<WarriorInfo>& warriorVector);

//if the status is read as the first word, it prints the information
// of the warriors and the number of warriors 
void Status(vector<WarriorInfo>& warriorVector);



//main function to call other methods and to open the file 
int main() {
	//opens file and checks if opens correctly
	ifstream warriorFile("warriors.txt");

	if (!warriorFile) {
		cerr << "Could not open the file.\n";
		exit(1); 
	}
	string command;
	string name;
	int strength;
	vector <WarriorInfo> warriorVector;
	//reads file and checks for the first 
	while (warriorFile >> command) {
		//each if compares the first word in the line
		//to see if its a Warrior, Status, or Battle
		//then calls that function 
		if (command == "Warrior") {
			warriorFile >> name  >> strength;
			WarriorInfo newWarrior;
			newWarrior.name = name;
			newWarrior.strength = strength;
			//adds to the vector the struct of Warrior
			warriorVector.push_back(newWarrior);  
		}
		//if command is Battle 
		else if (command == "Battle") {
			string name1;
			string name2;
			warriorFile >> name1 >> name2;
			Battle(name1, name2, warriorVector);
		}
		//if command is Status 
		else if (command == "Status") {
			Status(warriorVector);
		}
	}
	warriorFile.close();

}


//This is the battles, where it matches up the people with who they battle
//gives the output of the result of the battle
void Battle(string& name1, string& name2, vector<WarriorInfo>& warriorVector) {
	int firstStrength, secondStrength;
	//this iterates through the vector to find the first name
	for (size_t index = 0; index < warriorVector.size(); ++index) {
		if (warriorVector[index].name == name1) {
			firstStrength = warriorVector[index].strength;
			//iterates through the vector to find the second name 
			for (size_t secIndex = 0; secIndex < warriorVector.size(); ++secIndex)
			{
				if (warriorVector[secIndex].name == name2) {
					secondStrength = warriorVector[secIndex].strength;
					//prints who battles who
					cout << name1 << " battles " << name2 << endl;
					//these are if statements for each condition that they could
					//be battling in
					// first are to see if one of the warriors are already dead
					//if first warrior is dead
					if (firstStrength == 0) {
						if (secondStrength != 0) {
							cout << "He's dead, " << warriorVector[secIndex].name
								<< endl;
						}
						//if both are dead 
						else if (secondStrength == 0) {
							cout << "Oh, NO! They're both dead! Yuck!" << endl;
						}
					}
					//if second warrior is dead
					else if (secondStrength == 0) {
						if (firstStrength != 0) {
							cout << "He's dead, " << warriorVector[index].name
								<< endl;
						}
					}
					//these then are if both warriors are alive and 
					//need to compare and subtract strengths from each other
					else if (firstStrength == secondStrength) {
						warriorVector[index].strength = 0;
						warriorVector[secIndex].strength = 0;
						cout << "Mutal Annihilation: " << warriorVector[index].name
							<< " and " << warriorVector[secIndex].name
							<< " die at each other's hands" << endl;
					}
					//first warrior stronger than second
					// second warrior has 0 strength
					//first warrior looses second warriors strength
					else if (firstStrength > secondStrength) {
						firstStrength = firstStrength - secondStrength;
						warriorVector[secIndex].strength = 0;
						warriorVector[index].strength = firstStrength;
						cout << name1 << " defeats " << name2 << endl;
					}
					//second warrior stronger than first
					// first warrior has 0 strength
					//second warrior looses first warriors strength
					else if (secondStrength > firstStrength) {
						secondStrength = secondStrength - firstStrength;
						warriorVector[index].strength = 0;
						warriorVector[secIndex].strength = secondStrength;
						cout << name2 << " defeats " << name1 << endl;
					}

					break;
				}
			}
		}
	}
}

//if the status is read as the first word, it prints the information
// of the warriors and the number of warriors 
void Status(vector<WarriorInfo>& warriorVector) {
	string name;
	int strength;
	int numOfWarriors;
	numOfWarriors = warriorVector.size();
	cout << "There are: " << numOfWarriors << " warriors" << endl;
	for (size_t i = 0; i < warriorVector.size(); ++i) {
		name = warriorVector[i].name;
		strength = warriorVector[i].strength;
		cout << "Warrior: " << name << ", strength: " << strength << endl;
	}
}

