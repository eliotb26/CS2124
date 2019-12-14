//Eliot Brown 
//Lab 14
//LAST LAB!!!!


#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;


struct TNode {
	TNode(int data = 0, TNode* left = nullptr, TNode* right = nullptr)
		: data(data), left(left), right(right) {}
	int data;
	TNode* left, * right;
};



//TASK ONE --------------------------------------------------
bool binaryEvenOnes(int val) {
	bool result;
	if (val == 1) return false;
	if (val == 0) return true;
	result = binaryEvenOnes(val / 2);
	if (val % 2) return !result;
	return result;
}

//TASK TWO -------------------------------------------------
//Write a recursive function to create and return a new list that is 
//the sum of the values in the two lists passed in.Do not assume that the two lists are the same length. (By a list, I mean a Node*, not an instance of a list class.)
struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;

};

//Node* sumOfTwo(Node* list1, Node* list2) {
//	Node* nextptr;
//	Node* headptr;
//	if (list1 == nullptr && list2 == nullptr) {
//		return nullptr;
//	}
//	else if (list1->next != nullptr && list2->next != nullptr) {
//		list1 = list1->next;
//		list2 = list2->next;
//		sumOfTwo(list1, list2);
//	}
//	else if (list1->next == nullptr) {
//		list1 = list1->next;
//		sumOfTwo(nullptr, list2);
//	}
//	else if (list2->next == nullptr) {
//		list2 = list2->next;
//		sumOfTwo(list1, nullptr);
//	}
//}

Node* sumOfTwo(Node* first, Node* second) {
	Node* nextptr;
	Node* headptr;
	if (first == nullptr && second == nullptr) {
		return nullptr;
	}
	else if (first == nullptr) {
		nextptr = sumOfTwo(first, second->next);
		headptr = new Node(second->data, nextptr);
	}
	else if (second == nullptr) {
		nextptr = sumOfTwo(first->next, second);
		headptr = new Node(first->data, nextptr);
	}
	else {
		nextptr = sumOfTwo(first->next, second->next);
		headptr = new Node(first->data + second->data, nextptr);
	}
	return headptr;
}

void listAddHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

Node* listBuild(const vector<int>& vals) {
	Node* result = nullptr;
	for (size_t index = vals.size(); index > 0; --index) {
		listAddHead(result, vals[index - 1]);
	}
	return result;
}

void listDisplay(Node* headPtr) {
	Node* p = headPtr;
	while (p != nullptr) {
		cout << p->data << ' ';
		p = p->next;  // bump
	}
	cout << endl;
}

//TASK 3-------------------------------------------
int max(TNode* root) {
	if (root == nullptr) throw invalid_argument("Error: Empty tree");
	int largest = root->data;

	if (root->left) {
		int num = max(root->left);
		if (largest < num) largest = num;
	}
	if (root->right) {
		int num = max(root->right);
		if (largest < num) largest = num;
	}

	return largest;
}

//TASK 4-----------------------------------------------------
bool palindrome(char array[], int size) {
	if (size <= 1) {
		return true;
	}
	if (array[0] == array[size - 1]) {
		return palindrome(array + 1, size - 2);
	}
	return false;
}


//TASK 5-------------------------------------------------------------------
int towers(int n, int start = 0, int target = 1, int spare = 2) {
	if (n == 1) {
		return 1;
	}
	return (towers(n - 1, start, spare, target) + towers(n - 1, spare, target, start) + 1);
}


//TASK 6 --------------------------------------------------------------------
void mystery(int n) {
	if (n > 1) {
		cout << 'a';
		mystery(n / 2);
		cout << 'b';
		mystery(n / 2);
	}
	cout << 'c';
}


int main() {
	int val = 10;
	cout << "TASK ONE \n"; 
	if (binaryEvenOnes(val)) cout << "TRUE" << endl;
	else cout << "FALSE" << endl;

	//TASK TWO

	vector <int> list1 = { 1,3,5 };
	vector <int> list2 = { 1,3,5 };
	Node* Node1 = listBuild(list1);
	Node* Node2 = listBuild(list2);
	//Node* list1 = new Node(); 
	//Node* NodeC = new Node(5);
	//Node* NodeB = new Node(3, NodeC);
	//Node* NodeA = new Node(1, NodeB);

	//Node* list2 = new Node();
	//Node* NodeC2 = new Node(5);
	//Node* NodeB2 = new Node(3, NodeC2);
	//Node* NodeA2 = new Node(1, NodeB2);
	Node* headptr = sumOfTwo(Node1, Node2);
	cout << "TASK TWO \n"; 
	listDisplay(headptr);
	cout << endl;

	//TASK 3 
	TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
	cout << max(&f) << endl;

	//Task 4
	char s[] = "racecar";
	if (palindrome(s, 7)) {
		cout << "Yes!\n";
	}

	//Task 5
	//#5) Testing towers
	cout<< towers(1, 'a', 'b', 'c') << endl; // 1
	cout << towers(2, 'a', 'b', 'c') << endl; // 3
	cout << towers(3, 'a', 'b', 'c') << endl;// 7
	cout << towers(4, 'a', 'b', 'c') << endl; // 15
	cout << towers(5, 'a', 'b', 'c') << endl; // 31
	cout << towers(6, 'a', 'b', 'c') << endl; // 63
	cout << towers(7, 'a', 'b', 'c') << endl; // 127
	cout << towers(8, 'a', 'b', 'c') << endl; // 255
	towers(9, 'a', 'b', 'c'); // 511
	towers(10, 'a', 'b', 'c'); // 1023

	//Task6
	mystery(4);

}
