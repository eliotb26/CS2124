/* 
Eliot Brown
hw08

Purpose: Create a polynomial class for manipulating expressions
This is completed by using a singly linked list.
*/

#include "polynomial.h" 
#include <iostream> 
#include <vector>
#include <string>
 
using namespace std;

//namespace poly {

	Polynomial::Node::Node(int data = 0, Node* next = nullptr) : data(data),
		next(next) {}

	//POLYNOMIAL CLASS
	Polynomial::Polynomial(const vector<int>& v1) : head(new Node(0))
		, degree(0) {
		if (v1.size() != 0) {
			head = new Node(v1[v1.size() - 1]);
			Node* priorNode = head;
			polyVect.push_back(v1[v1.size() - 1]);
			for (int ind = v1.size() - 2; ind >= 0; --ind) {
				Node* currNode = new Node(v1[ind]);  //TODO not sure why this wont work
				priorNode->next = currNode;
				priorNode = priorNode->next;
				degree += 1;
				polyVect.push_back(currNode->data);
			}
		}
		//does it in order
		/*for (size_t ind = 0; ind < v1.size(); ++ind) {
			Node* currNode = new Node(v1[ind]);
			if (head == nullptr) {
				head = currNode;
			}
			else {
				Node* nextNode = head->next;
				head->next = currNode;
				currNode->next = nextNode;
			}
			polyVect.push_back(v1[ind]);
			degree += 1;
		}
		--degree;*/
	}

	ostream& operator<<(ostream& os, const Polynomial& rhs) {
		//TEST PRINT to see how it is lined up in the linked list
	//	Polynomial::Node* currNodePtr = rhs.head;
	//	if (currNodePtr->next != nullptr) {
	//		if 
	//	}
	//}


	//	Polynomial::Node* headptr = rhs.head;
	//	if (rhs.degree == 0) {
	//		if (rhs.head != nullptr) {
	//			os << headptr->data;
	//		}
	//	}
	//	else if (headptr != nullptr) {
	//		rhs.display(os, headptr, 0);
	//	}
	//	return os;
	//}

		vector<int> myList = {};
		int count = 0;
		//for (size_t ind = 0; ind < rhs.polyVect.size(); ++ind) {
		//	myList.push_back(rhs.polyVect[ind]);
		//}
		Polynomial::Node* currNode = rhs.head;
		while (currNode) {  //TODO requires bool operator   not a null value
			myList.push_back(currNode->data);
		}
		//for (int ind = rhs.polyVect.size() -1 ; ind >= 0; --ind) {   //THIS WAY uses vector field
		//	myList.push_back(rhs.polyVect[ind]);
		//}

		//iterate backwards through vector
	//	for (size_t index = myList.size() - 1; index > 0; --index) {
	//		os << myList[index] << endl;
	//		if (myList[index] != 0) {
	//			if ((rhs.degree - count) > 0) {
	//				if (myList[index] != 1) {
	//					os << myList[index];
	//					if ((rhs.degree - count) == 1) {
	//						os << "x ";
	//					}
	//					else {
	//						os << "x^" << rhs.degree - count << " ";
	//					}
	//				}
	//				else {
	//					if ((rhs.degree - count) == 1) {
	//						os << "x ";
	//					}
	//					else {
	//						os << "x^ " << rhs.degree - count << " ";
	//					}
	//				}
	//			}
	//			else {
	//				os << myList[index] << " ";
	//			}
	//			if(index != myList.size() - 1) {
	//				os << "+ ";
	//			}
	//		}
	//		count += 1;
	//	}
			return os;
	}
	//void Polynomial::display(std::ostream& os, Node* currNode, int degree) const {
	//	if (currNode == nullptr) {
	//		std::cout << " ";
	//	}
	//	else {
	//		display(os, currNode->next, degree + 1);
	//		if (currNode->data != 0) {
	//			if (degree == 0) {
	//				std::cout << currNode->data << " ";
	//			}
	//			else if (degree == 1) {
	//				if (currNode->data == 1) {
	//					std::cout << "x + ";
	//				}
	//				else {
	//					std::cout << currNode->data << "x + ";
	//				}
	//			}
	//			else {
	//				if (currNode->data == 1) {
	//					std::cout << "x^" << degree << " + ";
	//				}
	//				else {
	//					std::cout << currNode->data << "x^" << degree << " + ";
	//				}
	//			}
	//		}
	//	}
	//}

	//Not equals operator
	bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
		return lhs != rhs;
	}

	//Destructor
	Polynomial::~Polynomial() {   //TODO Check this deconstructor  and copy Control!!!!!!!!!!!!!!!!!!
		Node* headptr;
		while (head != nullptr) {
			headptr = head->next;
			delete head;
			head = headptr;
		}
								  
								  
		//if (polyVect.size() != 0) {
		//	for (size_t ind = 0; ind < polyVect.size(); ++ind) {
		//		if (head != nullptr) {
		//			Node* headPtr = head->next;
		//			delete head;
		//			head = headPtr;
		//		}
		//		else {
		//			delete head;  //to delete the last node in the list
		//		}
		//	}
		//}
		//polyVect.clear();   //dont delete vector as not on the heap
		//degree = 0;
	}

	//Copy Constructor
	Polynomial::Polynomial(const Polynomial& rhs) {
		Node* head = rhs.head;
		degree = rhs.degree;
		polyVect = {};
		for (size_t ind = 0; ind < rhs.polyVect.size(); ++ind) {
			polyVect.push_back(rhs.polyVect[ind]);
		}
		for (size_t ind = 0; ind < polyVect.size(); ++ind) {
			Node* currNode = new Node(polyVect[ind]);
			if (head == nullptr) {
				head = currNode;
			}
			else {
				Node* nextNode = head->next;
				head->next = currNode;
				currNode->next = nextNode;
			}
		}
	}

	//Assigment Operator 
	Polynomial& Polynomial::operator=(const Polynomial& rhs){
		if (this != &rhs) {
			Node* tempDel;
			// delete everything in rhs
			while (head != nullptr) {
				tempDel = head->next;
				delete head;
				head = tempDel;
			}
			//tempDel=nullptr;

			head = new Node(rhs.head->data);
			// assign everything from self to rhs
			Node* lhptr = head;
			Node* rhptr = rhs.head->next;
			while (rhptr != nullptr) {
				lhptr->next = new Node(rhptr->data);
				rhptr = rhptr->next;
				lhptr = lhptr->next;
			}

			degree = rhs.degree;

		}
		return *this;
	}

	int Polynomial::getDegree() const { return degree; }

	// c1 += c2
	//c1.operator+=(c2);
	Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
		Node* right = rhs.head;
		Node* left = head;
		Node* newRight = rhs.head;
		Node* newLeft = head;

		int difference = abs(rhs.degree - degree);

		/* make the right && left point to the rightmost node;  */
		while (right != nullptr) {
			right = right->next;

		}
		for (int i = 0; i < difference; i++) {
			if (degree > rhs.degree) {
				right = new Node(0);
			}
			else if (degree < rhs.degree) {
				left->next = new Node(0);
			}
		}
		while (newRight != nullptr) {
			newLeft->data += newRight->data;
			newLeft = newLeft->next;
			newRight = newRight->next;
		}

		return *this;
	}
	//	int difference = abs(rhs.degree - degree);

	//	for (size_t ind = 0; ind < difference; ++ind) {
	//		polyVect[ind] += rhs.polyVect[ind];
	//	}
	//	Node* currNode = head;
	//	for (size_t ind = 0; ind < difference; ++ind) {
	//		currNode->data = polyVect[ind];
	//		currNode->next;
	//	}
	//	return *this;
	//}
		
	//	if (polyVect.size() == rhs.polyVect.size()) {
	//		for (size_t ind = 0; ind < polyVect.size(); ++ind) {
	//			polyVect[ind] += rhs.polyVect[ind];
	//		}
	//	}
	//	else if (polyVect.size() > rhs.polyVect.size()) {
	//		for (size_t ind = rhs.polyVect.size()-1; ind > 0; --ind) {
	//			polyVect[ind] += rhs.polyVect[ind];
	//		}
	//		//for (size_t ind = 0; ind < rhs.polyVect.size(); ++ind) {
	//		//	polyVect[ind] += rhs.polyVect[ind];
	//		//}
	//	}
	//	else {
	//		for (size_t ind = polyVect.size()-1; ind > 0; --ind) {
	//			polyVect[ind] += rhs.polyVect[ind];
	//		}
	//		//for (size_t ind = 0; ind < polyVect.size(); ++ind) {
	//		//	polyVect[ind] += rhs.polyVect[ind];
	//		//}
	//	}
	//	//Polynomial(polyVect);
	//	Node* tempHead = head;
	//	for (size_t ind = 0; ind <polyVect.size(); ++ind) {
	//		if (tempHead == nullptr) {
	//			//This is the last node, but it also is set up backwards. Remember that the vector should be stored in reverse than the linked list. 
	//		}
	//		else {
	//			tempHead->data = polyVect[ind];
	//			tempHead = tempHead->next;
	//		}
	//	}
	//	return *this;
	//}


	//}
	/*
	+=
	+
	copy control
	==
	!=
	<<  the ^ is the exponentiation
	evaluation -> returns values at that value of X
	*/

	//c1 + c2
	Polynomial operator+(const Polynomial& lhs, 
		const Polynomial& rhs) {
		//if () {

		//}
		//Polynomial result(lhs);  //allocates into result
		//result += rhs;        // adds rhs to allocated result 
		//return result;

		if (lhs.getDegree() > rhs.getDegree()) {
			Polynomial result(lhs);
			result += rhs;
			return result;
		}
		else {
			Polynomial result(rhs);
			result += lhs;
			return result;
		}
	}