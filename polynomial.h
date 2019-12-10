#pragma once

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <string>
#include <vector>
#include <iostream>



class Polynomial {
	struct Node {  //TODO check if this right way for .h file
		Node(int data, Node* next);
		int data;
		Node* next;
	};
	friend std::ostream& operator << (std::ostream& os, const Polynomial& rhs);   //can use a string instead of vector
	friend bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
public:
	Polynomial(const std::vector<int>& v1 = {});
	//Copy Control
	~Polynomial();
	Polynomial(const Polynomial& rhs);
	void display(std::ostream& os, Node* currNode, int degree) const;

	Polynomial& operator=(const Polynomial& rhs);

	int getDegree() const;

	// c1 += c2
	//c1.operator+=(c2);
	Polynomial& operator+=(const Polynomial& rhs);


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

private:
	std::vector<int> polyVect;    //TODO make vector in output operator     private only degree and head!!!
	int degree;
	Node* head;
};

//c1 = c2 + c3;
//operator+(c1, c2);
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

#endif