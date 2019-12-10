//Eliot Brown 
// Lab 12 

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class List {
	friend ostream& operator<<(ostream& os, const List& rhs) {
		if (rhs.head->next != rhs.tail) {
			Node* curr = rhs.head->next;
			for (int i = 0; i < rhs.listSize; ++i) {
				os << curr->data << " ";
				curr = curr->next;
			}
		}
		else {
			os << "No nodes\n";
		}
		return os;
	}
	struct Node {
		Node(int data = 0, Node* next = nullptr, Node* prev = nullptr) : data(data),
			next(next), prev(prev) {}
		int data;
		Node* next;
		Node* prev;
	};
public: 
	class iterator {
		friend List;
		friend bool operator==(const iterator& lhs, const iterator& rhs) {
			return lhs.nodePrt == rhs.nodePrt;
		}
		friend ostream& operator<<(ostream& os, iterator& rhs) {
			os << "node:\t" << rhs.nodePrt;
			os << "\ndata:\t" << *rhs;
			os << "\n\n";
			return os;
		}

		friend bool operator!=(const iterator& lhs, const iterator& rhs) {
			return lhs.nodePrt != rhs.nodePrt;
		}
	public:
		iterator(Node* nodePrt = nullptr) : nodePrt(nodePrt) {}
		iterator& operator++() {
			if(nodePrt)
				nodePrt = nodePrt->next;
			return *this;
		}
		iterator& operator--() {
			if(nodePrt && nodePrt->prev)
				nodePrt = nodePrt->prev;
			return *this;
		}

		//int getData()const { return nodePrt->data; }

		int operator*() const{
			return nodePrt->data;
		}
		int& operator*() { return nodePrt->data; }

	private: 
		Node* nodePrt;
	};


	List(): listSize(0) {
		head = new Node(); 
		tail = new Node();
		head->next = tail;
		tail->prev = head;
	}

	//assignment operator
	//List& operator=(List& rhs) {
	//	if (this != &rhs) {
	//		clear();
	//		for (int new_val : rhs) {
	//			push_back(new_val);
	//		}
	//	}
	//	return *this;
	//}

	void printInfo() const{
		if (head->next != tail) {
			Node* curr = head->next;
			for (int i = 0; i < listSize; ++i) {
				cout << "\ndata:\t" << curr->data;
				cout << "\nnode:\t" << curr;
				cout << "\nprev:\t" << curr->prev;
				cout << "\nnext:\t" << curr->next << '\n';
				curr = curr->next;
				cout << '\n';
			}
		}
		else {
			cout << "No nodes\n";
		}
	}

	void push_back(const int data) {
		Node* left = tail->prev;
		Node* newNode = new Node(data, tail, left);
		left->next = newNode;
		tail->prev = newNode;
		listSize++;
	}
	void pop_back() {
		if (listSize > 0) {
			Node* newLast = tail->prev->prev;
			delete tail->prev;
			newLast->next = tail;
			tail->prev = newLast;
			listSize--;
		}
		/*	Node* right = tail->prev;
			Node* left = tail->prev->prev;
			left->next = tail;
			right->next = nullptr;
			right->prev = nullptr;
			tail->prev = left;*/
	}
	int& front() {
		if (head->next != tail) {
			return head->next->data;
		}
		cout << "No front node\n";
	}
	int front() const {
		if (head->next != tail) {
			return head->next->data;
		}
		cout << "No front node\n";
	}
	int& back() {
		if (tail->prev != head) {
			return tail->prev->data;
		}
		cout << "No back node\n";
	}
	int back() const{
		if (tail->prev != head) {
			return tail->prev->data;
		}
		cout << "No back node\n";
	}
	int size() const{
		return listSize;
	}

	//TASK 2 ------------------------------
	void push_front(int data) {
		/*Node* right = head->next;
		Node* newNode = new Node(data, right, head);
		right->prev = newNode;
		head->next = newNode;
		listSize++;
	}*/
		Node* newNode = new Node(data, head->next, head);
		head->next->prev = newNode;
		head->next = newNode;
		listSize += 1;
	}
	bool is_empty() const { return head->next == tail; }

	void pop_front() {
		if (is_empty()) return;
		/*if (listSize > 0) {*/
		Node* nodeToDelete = head->next;
		Node* secondFromFirst = head->next->next;
		secondFromFirst->prev = head;
		head->next = secondFromFirst;
		//nodeToDelete = nullptr;
		delete nodeToDelete;
		listSize--;

			//Node* newFront = head->next->next;
			//delete head->next;
			//newFront->prev = head;
			//head->next = newFront;
			//listSize--;
		
	}
	//TASK 4--------------
	void clear() {
		while (listSize != 0) {
			pop_front();
		}
	}

	//TASK 4 -------------
	int operator[](int index) const{
		if (index < listSize && index >= 0) {
			Node* curr = head->next;
			for (int i = 0; i < index; i++) {
				curr = curr->next;
			}
			return curr->data;
		}
	}

	int& operator[] (int index) {
		if (index < listSize && index >= 0) {
			Node* curr = head->next;
			for (int i = 0; i < index; i++) {
				curr = curr->next;
			}
			return curr->data;
		}
	}

	//TASK 5 ----------------
	iterator begin() {
		return iterator(head->next);
	}

	iterator end() {
		return iterator(tail);
	}

	iterator insert(iterator iter, int val) {
		Node* node = iter.nodePrt;
		Node* newNode = new Node(val, node, node->prev);

		node->prev->next = newNode;
		node->prev = newNode;
		++listSize;
		return --iter;
	}
	iterator erase(iterator iter) {
		if (listSize == 0) {
			return iter;
		}
		Node* node = iter.nodePrt;
		node->prev->next = node->next; 
		node->next->prev = node->prev;
		--listSize; 
		Node* nextNode = node->next; 
		delete node;
		return iterator(nextNode);
	}
private: 
	int listSize; 
	Node* head; 
	Node* tail;
};


void printListInfo(const List& myList) {
	cout << "size: " << myList.size()
		<< ", front: " << myList.front()
		<< ", back(): " << myList.back()
		<< ", list: " << myList << endl;
}

void changeFrontAndBack(List& theList) {
	theList.front() = 17;
	theList.back() = 42;
}

void printListSlow(const List& myList) {
	for (size_t i = 0; i < myList.size(); ++i) {
		cout << myList[i] << ' ';
	}
	cout << endl;
}

// Task 8
void doNothing(List aList) {
	cout << "In doNothing\n";
	printListInfo(aList);
	cout << endl;
	cout << "Leaving doNothing\n";
}

int main() {

	// Task 1
	cout << "\n------Task One------\n";
	List myList;
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList.push_back(" << i * i << ");\n";
		myList.push_back(i * i);
		printListInfo(myList);
	}
	cout << "===================\n";

	cout << "Modify the first and last items, and display the results\n";
	changeFrontAndBack(myList);
	printListInfo(myList);
	cout << "===================\n";

	cout << "Remove the items with pop_back\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_back();
	}
	cout << "===================\n";

	// Task 2
	cout << "\n------Task Two------\n";
	cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList2.push_front(" << i * i << ");\n";
		myList.push_front(i * i);
		printListInfo(myList);
	}
	cout << "===================\n";
	cout << "Remove the items with pop_front\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_front();  
	}
	cout << "===================\n";

	// Task 3
	cout << "\n------Task Three------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		myList.push_back(i * i);
	}
	printListInfo(myList);
	cout << "Now clear\n";
	myList.clear();
	cout << "Size: " << myList.size() << ", list: " << myList << endl;
	cout << "===================\n";

	// Task 4
	cout << "\n------Task Four------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i)  myList.push_back(i * i);
	cout << "Display elements with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
	cout << endl;
	cout << "Add one to each element with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
	cout << "And print it out again with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
	cout << endl;
	cout << "Now calling a function, printListSlow, to do the same thing\n";
	printListSlow(myList);
	cout << "Finally, for this task, using the index operator to modify\n"
		<< "the data in the third item in the list\n"
		<< "and then using printListSlow to display it again\n";
	myList[2] = 42;
	printListSlow(myList);


	// Task 5
	cout << "\n------Task Five------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i)  myList.push_back(i * i);
	printListInfo(myList);
	cout << "Now display the elements in a ranged for\n";
	for (int x : myList) cout << x << ' ';
	cout << endl;
	cout << "And again using the iterator type directly:\n";
	// Note you can choose to nest the iterator class or not, your choice.
	//for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
	for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
		cout << *iter << ' ';
	}
	cout << endl;
	cout << "WOW!!! (I thought it was cool.)\n";
	
	// Task 6
	cout << "\n------Task Six------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
	printListInfo(myList);
	cout << "Filling an empty list with insert at begin(): "
		<< "i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i * i);
	printListInfo(myList);
	// ***Need test for insert other than begin/end***
	cout << "===================\n";

	// Task 7
	cout << "\n------Task Seven------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
	cout << "Erasing the elements in the list, starting from the beginning\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.erase(myList.begin());
	}
	// ***Need test for erase other than begin/end***
	cout << "===================\n";

	// Task 8
	//cout << "\n------Task Eight------\n";
	//cout << "Copy control\n";
	//cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	//myList.clear();
	//for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
	//printListInfo(myList);
	//cout << "Calling doNothing(myList)\n";
	//doNothing(myList);
	//cout << "Back from doNothing(myList)\n";
	//printListInfo(myList);

	//cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
	//List listTwo;
	//for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i * i);
	//printListInfo(listTwo);
	//cout << "listTwo = myList\n";
	//listTwo = myList;
	//cout << "myList: ";
	//printListInfo(myList);
	//cout << "listTwo: ";
	//printListInfo(listTwo);
	//cout << "===================\n";
}
