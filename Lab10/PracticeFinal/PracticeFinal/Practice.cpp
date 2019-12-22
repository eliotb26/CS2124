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

void throwIfNegativeOne(int val) throw (...) {
	if (val == -1) {
		string ErrorMessage ("Negative One");
		throw ErrorMessage;
	}
}

// towers of hanoi
//   n is the number of disks, start is the spindle that they start
//   on, target is where thery are being moved to, and spare is the
//   "unused" spindle.
void towers(int n, char start, char target, char spare) {
	if (n == 0) return;
	towers(n - 1, start, spare, target);
	cout << "Move disk: " << n << " from spindle: " << start
		<< " to spindle: " << target << endl;
	towers(n - 1, spare, target, start);
}

void bar(int n) {
	if (n > 200) {
		// What to do?
		//throw 42;
		// throw 3.14159;
		out_of_range myOOR("bar got passed a value more than 200");
		throw myOOR;
	}
}
void foo(int n) { bar(n); }

struct Thing { int val; };

int main() {
	//try {
	//	foo(300);
	//}
	//catch (out_of_range oor) {
	//	cerr << "Caught out of range specifically " << oor.what() << endl;
	//}
	//catch (exception & oor) {
	//	cerr << "Caught out of range: " << oor.what() << endl;
	//}



	//cout << multiply(1, 5) << endl;

	//towers
	//towers(3, 'A', 'C', 'B');

	Thing** data = new Thing* [100];

	for (size_t ind = 0; ind < 100; ind++) {
		data[ind] = new Thing();
		data[ind]->val = ind+1;
		cout << data[ind]->val << endl;
	}
	
	
	for (size_t ind = 0; ind < 100; ind++) {
		data[ind]->val += ind + 1;
	}
	for (size_t ind = 0; ind < 100; ind++) {
		for (size_t ind = 0; ind < 100; ind++) {
			delete data[ind];
			data[ind] = nullptr;
		}
		delete[] data;
		data = nullptr;
	}
}