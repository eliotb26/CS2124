
//Eliot Brown
//rec 13



#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;





// Task 9
void printList(const list<int>& lst) {
	list<int>::const_iterator iter = lst.begin();
	while (iter != lst.end()) {
		cout << *iter << ' ';
		iter++;
	}
	cout << '\n';
}

// Task 10
void display_for_range(const list<int>& lst) {
	for (int curr : lst) {
		cout << curr << ' ';
	}
	cout << '\n';
}

//Task 11
void display_auto(const list<int>& lst) {
	for (const auto& item : lst) {
		cout << item << " "; 
	}
}

//Task 12
list<int>::const_iterator iter_find(const list<int>& lst, int numSearch) {
	cout<< "In find" << endl;
	for (list<int>::const_iterator iter = lst.begin(); iter != lst.end(); iter++) {
		if (*iter == numSearch) {
			return iter;
		}
	}
	return lst.end();

}

//Task 13
auto auto_iter_find(const list<int>& lst, int numSearch) {
	cout << "In auto find" << endl;
	for (auto iter = lst.begin(); iter != lst.end(); ++iter) {
		if (*iter == numSearch) {
			return iter;
		}
	}
	return lst.end();
}

//Task 15
bool isEven(int x) {
	if (x % 2 == 0) {
		return x % 2 == 0;
	}
	else {
		cout << "No even numbers";
		return -1;
	}
}

//Task 16
class IsEven {
public:
	bool operator() (int x) const {
		if (x % 2 == 0) {
			return true;
		}
		return false;
	}
};

//Task 18
void printArray(int arr[], size_t length) {
	for (size_t i = 0; i < length; i++) {
		cout << arr[i] << " ";
	}
}

list<int>::const_iterator ourFind(const list<int>& lst, int numberToFind) {
	cout << "MY NICE ** FUNCTION" << endl;
	for (list<int>::const_iterator iter = lst.begin(); iter != lst.end(); iter++) {
		if (*iter == numberToFind) {
			return iter;
		}
	}
	return lst.end();
}

//Task 20
template <typename first, typename sec>
first ourFindNew(first start, first end, sec numberToFind) {
	cout << "In my own Template" << endl;
	for (first iter = start; iter != end; iter++) {
		if (*iter == numberToFind) {
			return iter;
		}
	}
	return end;
}



int main() {

	// 1. Create a vector with some values and display using ranged for
	cout << "Task 1:\n";
	vector <int> vec1({3,5,7,1 });
	for (int num : vec1) {
		cout << num << " "; 
	}
	cout << endl;
	cout << "\n=======\n";

	// 2. Initalize a list as a copy of values from the vector
	cout << "Task 2:\n";
	list <int> lst({3,5,7,1 });
	for (int curr : lst) {
		cout << curr << " ";
	}
	cout << endl;
	cout << "\n=======\n";

	// 3. Sort the original vector.  Display both the vector and the list
	cout << "Task 3:\n";
	sort(vec1.begin(), vec1.end());
	for (int curr : vec1) {
		cout << curr << " "; 
	}
	cout << endl;

	for (int curr : lst) {
		cout << curr << " ";
	}
	cout << endl;

	cout << "\n=======\n";

	// 4. print every other element of the vector.
	cout << "Task 4:\n";
	for (size_t ind = 0; ind < vec1.size(); ++ind) {
		if (ind % 2 == 0) {
			cout << vec1[ind] << " ";
		}
	}
	cout << endl;
	cout << "\n=======\n";

	// 5. Attempt to print every other element of the list using the
	//    same technique.
	cout << "Task 5:\n";
	//for (size_t ind = 0; ind < lst.size(); ++ind) {
	//	int curr = lst[ind];       // doesn't compile
	//	if (ind % 2 == 0) {
	//		cout << curr << " ";
	//	}
	//}
	cout << "Its not supposed to compile" << endl;

	cout << "\n=======\n";

	//
	// Iterators
	//

	// 6. Repeat task 4 using iterators.  Do not use auto;
	cout << "Task 6:\n";
	vector<int>::iterator iter = vec1.begin();
	while (iter < vec1.end()) {
		cout << *iter << " ";
		iter += 2;
	}
	cout << endl;
	cout << "\n=======\n";

	// 7. Repeat the previous task using the list.  Again, do not use auto.
	//    Note that you cannot use the same simple mechanism to bump
	//    the iterator as in task 6.
	cout << "Task 7:\n";
	//list<int>::iterator lstIter = lst.begin();
	//while (lstIter != lst.end()) {
	//	cout << *lstIter << " ";
	//	++lstIter;
	//	if (lstIter != lst.end()) {
	//		++lstIter;
	//	}
	//}
			//either way works
	for (list<int>::iterator iter = lst.begin(); iter != lst.end(); iter++) {
		cout << *iter << " ";
		iter++;
	}
	cout << endl;
	cout << "\n=======\n";

	// 8. Sorting a list
	cout << "Task 8:\n";
	lst.sort();
	for (int sortedList : lst) {
		cout << sortedList << " ";
	}
	cout << endl;
	cout << "\n=======\n";

	// 9. Calling the function to print the list
	cout << "Task 9:\n";
	printList(lst);
	cout << endl;
	cout << "=======\n";

	// 10. Calling the function that prints the list, using ranged-for
	cout << "Task 10:\n";
	display_for_range(lst);
	cout << endl;
	cout << "=======\n";

	//
	// Auto
	//

	// 11. Calling the function that, using auto, prints alterate
	// items in the list
	cout << "Task 11:\n";
	display_auto(lst);
	cout << endl;
	cout << "=======\n";


	// 12.  Write a function find that takes a list and value to search for.
	//      What should we return if not found
	cout << "Task 12:\n";
	iter_find(lst, 3);
	cout << endl;
	cout << "=======\n";

	// 13.  Write a function find that takes a list and value to search for.
	//      What should we return if not found
	cout << "Task 13:\n";
	auto_iter_find(lst, 5);
	cout << endl;
	cout << "=======\n";

	//
	// Generic Algorithms
	//

	// 14. Generic algorithms: find
	cout << "Task 14:\n";
	auto result = find(lst.begin(), lst.end(), 5);
	if (result != lst.end()) {
		cout << *result;
	}
	else {
		cout << "Not Found";
	}
	cout << endl;
	cout << "=======\n";

	// 15. Generic algorithms: find_if
	cout << "Task 15:\n";
	cout << "list" << endl;
	auto firstEven = find_if(lst.begin(), lst.end(), isEven);
	cout << *firstEven << endl;

	cout << "vector" << endl;
	auto vecFirstEven = find_if(vec1.begin(), vec1.end(), isEven);
	cout << *vecFirstEven << endl;
	cout << endl;

	// 16. Functor
	cout << "Task 16:\n";
	auto firstEven2 = find_if(lst.begin(), lst.end(), IsEven());
	if (firstEven2 != lst.end()) {
		cout << *firstEven2; 
	}
	else {
		cout << "not found";
	}
	cout << endl;
	cout << "=======\n";

	// 17. Lambda
	cout << "Task 17:\n";
	auto firstEven3 = find_if(lst.begin(), lst.end(), [](int curr) { return curr % 2 == 0; });
	if (firstEven3 != lst.end()) {
		cout << *firstEven3 << endl;
	}
	else {
		cout << "Not found" << endl;
	}
	cout << "=======\n";

	// 18. Generic algorithms: copy to an array
	cout << "Task 18:\n";
	int arr[4];
	copy(vec1.begin(), vec1.end(), arr);
	printArray(arr, vec1.size());
	cout << endl;

	cout << "=======\n";

	//
	// Templated Functions
	//

	// 19. Implement find as a function for lists
	cout << "Task 19:\n";
	list<int>::const_iterator ourIter = ourFind(lst, 13);
	if (ourIter != lst.end()) { cout << "found"; }
	else cout << "Couldn't find the number" << endl;
	cout << "=======\n";

	// 20. Implement find as a templated function
	cout << "Task 20:\n";
	list<int>::const_iterator ourIter2 = ourFindNew(lst.begin(), lst.end(), 1);
	if (ourIter2 != lst.end()) { cout << "found" << endl; }
	else cout << "Could not find the number" << endl;

	cout << "=======\n";
	//
	// Associative collections
	//

	// 21. Using a vector of strings, print a line showing the number
	//     of distinct words and the words themselves.
	cout << "Task 21:\n";

	ifstream file("Text.txt");
	if (!file) {
		cerr << "Can't open file" << endl;
	}
	vector<string> vec2;
	string word;
	bool isWordThere;
	while (file >> word) {
		isWordThere = false;
		for (size_t ind = 0; ind < vec2.size(); ind++) {
			if (vec2[ind] == word) {
				isWordThere = true;
				break;
			}
		}
		if (isWordThere == false) {
			vec2.push_back(word);
		}
	}
	cout << vec2.size() << endl;
	file.close();
	cout << "\n=======\n";

	// 22. Repeating previous step, but using the set
	cout << "Task 22:\n";
	ifstream file2("Text.txt");
	if (!file2) {
		cerr << "Can't open file" << endl;
	}
	set<string> set1;
	string word2;
	bool wordThere;
	while (file2 >> word2) {
		set1.insert(word2);
	}
	cout << set1.size() << endl;

	file2.close();
	cout << "=======\n";

	// 23. Word co-occurence using map
	cout << "Task 23:\n";
	//myWordMap();
	ifstream file3("Text.txt");
	if (!file3) {
		cout << "Cant open the file" << endl;
	}
	string lastWords;
	map<string, vector<int>>wordMap;
	int position = 0;
	while (file3 >> lastWords) {
		wordMap[lastWords].push_back(position);
		++position;
	}
	for (const auto& place : wordMap) {
		cout << place.first << "->";
		for (size_t ind = 0; ind < place.second.size(); ++ind) {
			cout << place.second[ind] << " ";
		}
		cout << endl;
	}
	file3.close();
	cout << "=======\n";
}
