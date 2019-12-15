#include <string>
#include <vector>
#include <iostream>
using namespace std;



//CORRECT
class BroadWar /*: public Starcraft*/{
	friend ostream& operator<<(ostream& os, const BroadWar& rhs) {
		os << rhs.name << ": ";
		if (rhs.armyVect.size() != 0) {
			for (size_t ind = 0; ind < rhs.armyVect.size(); ++ind) {
				os << rhs.armyVect[ind] << ", ";
			}
		}
		else {
			os << "NO ARMY. ";
		}
		os << endl;
	}
public:
	BroadWar(const string& name, const int registration) : name(name) /*Starcraft(registration)*/{ }
	bool operator==(const BroadWar& rhs) const {
		if (armyVect.size() == rhs.armyVect.size()) {
			if (armyVect.size() == 0) {
				return true;
			}
			for (size_t ind = 0; ind < armyVect.size(); ++ind) {
				if (*armyVect[ind] != *rhs.armyVect[ind]) {
					return false;
				}
				return true;
			}
		}
		return false;
	}
	//Copy Control

	//Copy Constructor  
	//BroadWar first(aldkjf)
	//BroadWar sec(first)
	BroadWar(const BroadWar& rhs): name(rhs.name)/*, StarCraft(rhs.registration)*/{
		vector<string*> armyVect;
		for (size_t ind = 0; ind < rhs.armyVect.size(); ++ind) {
			string* result = new string(*rhs.armyVect[ind]);
			armyVect.push_back(result);
		}
	}

	//Deconstructor
	~BroadWar() { //only clear stuff on heap
		if (armyVect.size() != 0) {
			for (size_t ind = 0; ind < armyVect.size(); ++ind) {
				delete armyVect[ind];
			}
		}
		armyVect.clear();
	}

	//Assignment Operator
	BroadWar& operator=(const BroadWar& rhs) {
		//1 Delete 
		for (size_t ind = 0; ind < armyVect.size(); ++ind) {
			delete armyVect[ind];
		}
		armyVect.clear();
		//2 Allocate space
		if (rhs.armyVect.size() != 0) {
			for (size_t ind = 0; ind < armyVect.size(); ++ind) {
				armyVect.push_back(new string(*rhs.armyVect[ind]));
			}
		}
		else{ }
		//3 assign space
		name = rhs.name;
		//Starcraft::operator=(rhs);

		//4 return result 
		return *this;
	}
private:
	string name;
	vector</*Zergling*/string*> armyVect;
};

template<typename T> 
T multiply(const T& first, const T& sec) {
	return first * sec;
}

int main() {
	cout << multiply(1, 5);
}