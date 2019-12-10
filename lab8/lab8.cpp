/* 
Eliot Brown 
lab 8 
CS 2124 
Purpose: to create a class 
to store numbers as rational numbers

*/


#include <iostream>
#include <string>
#include <vector>

using namespace std;

int greatestCommonDivisor(int x, int y) {
	while (y != 0) {
		int temp = x % y;
		x = y;
		y = temp;
	}
	return x;
}

class Rational {
	//input operator 
	friend istream& operator>>(istream& is, Rational& rhs) {
		char divided; 
		int left, right; 
		is >> left >> divided >> right; 
		rhs.numerator = left; 
		rhs.denominator = right; 
		rhs.normalize(); 
		return is;
	}
	//output operator 
	friend ostream& operator<<(ostream& os, const Rational& rhs) {
		os << rhs.numerator << '/' << rhs.denominator;
		return os;
	}
	//== operator 
	friend bool operator==(const Rational& lhs, const Rational& rhs) {
		return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
	}
	// greater than
	friend bool operator>(const Rational& lhs, const Rational& rhs) {
		int newBottom = lhs.denominator * rhs.denominator;
		int leftTop = lhs.numerator * rhs.denominator;
		int rightTop = rhs.numerator * lhs.denominator;
		return (leftTop - rightTop) > 0;
	}

public: 
	Rational(int num = 0, int num2 = 1)
		: numerator(num), denominator(num2) {
		normalize();
	}

	Rational& operator+=(const Rational& rhs) {
		int newNumerator = numerator * rhs.denominator + 
						rhs.numerator * denominator;
		int newDenominator = denominator * rhs.denominator;
		numerator = newNumerator;
		denominator = newDenominator;
		normalize();
		return *this;
	}

	// Pre ++
	Rational& operator++() {
		*this += 1;
		return *this;
	}

	// Post ++ 
	//RETURNS a COPY as it is a local 
	Rational operator++(int dummy) {
		Rational temp = *this;
		*this += 1;
		return (temp);
	}

	// one.operator bool();
	explicit operator bool() const {
		return (numerator != 0);
	}
private: 
	int numerator; 
	int denominator; 
	//to switch negative sign from top to bottom
	void normalize() {
		if (numerator > 0 && denominator < 0) {
			denominator *= -1;
			numerator *= -1;
		}
		if (numerator < 0 && denominator < 0) {
			numerator *= -1;
			denominator *= -1;
		}
		int gcd = greatestCommonDivisor(abs(numerator), abs(denominator));
		numerator /= gcd;
		denominator /= gcd;
	}
};

//NON MEMEMBER 

Rational operator+(Rational& lhs, const Rational& rhs) {
	Rational result(lhs);
	result += rhs;
	return result;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
	return !(lhs == rhs);
}

// Pre -- operator
//returns actual reference 
Rational& operator--(Rational& rhs) {
	rhs += -1;
	return rhs;
}

//Post -- operator   //changing rational 
//returns a copy of rational as it is LOCAL
Rational operator--(Rational& rhs, int dummy) {
	Rational temp(rhs);
	rhs += -1;
	return temp;
}

// less than
bool operator<(const Rational& lhs, const Rational& rhs) {
	return !(lhs > rhs) && (lhs != rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
	return (lhs > rhs) || (lhs == rhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
	return !(lhs > rhs);
}

int main() {
	Rational twoThirds(2, 3);
	cout << twoThirds << endl;

	
	Rational a, b;
	cout << "Input a rational number, e.g. 6/9.\n";
	cout << "a: ";
	cin >> a;
	cout << "Input a rational number, e.g. 6/9.\n";
	cout << "b: ";
	cin >> b;
	const Rational one = 1;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "one = " << one << endl;
	cout << "a += b: " << (a += b) << endl;	// Implement as member
	cout << "a = " << a << endl;

	// Implement as non-member, but not a friend
	cout << "a + one: " << (a + one) << endl;
	cout << "a == one: " << boolalpha << (a == one) << endl;

	// How does this manage to work?
	// It does NOT require writing another == operator. 
	cout << "1 == one: " << boolalpha << (1 == one) << endl;

	// Do not implement as friend.
	cout << "a != one: " << boolalpha << (a != one) << endl;

	cout << "a = " << a << endl;
	cout << "++a = " << (++a) << endl;
	cout << "a = " << a << endl;
	cout << "a++ = " << (a++) << endl;
	cout << "a = " << a << endl;
	cout << "--a = " << (--a) << endl;
	cout << "a = " << a << endl;
	cout << "a-- = " << (a--) << endl;
	cout << "a = " << a << endl;
		
	cout << "++ ++a = " << (++ ++a) << endl;
	cout << "a = " << a << endl;
	cout << "-- --a = " << (-- --a) << endl;
	cout << "a = " << a << endl;
		//not good to do as returns copy of a before the +1 then adds one to it. 
		//calls a method it works but not good
	cout << "a++ ++ = " << (a++ ++) << endl;
	cout << "a = " << a << endl;

	//// Even though the above example, (a++ ++), compiled, the
	//// following shouldn't.
	//// But some compiler vendors might let it...  Is your compiler
	//// doing the right thing?

		//this should not work and as it calls a function on it 
		//not good to write as it is hard to understand and 
		//gives an unusal output as makes a copy
	//cout << "a-- -- = " << (a-- --) << endl;
	//cout << "a = " << a << endl;


	// Should report that 1 is true
	if (Rational(1)) {
		cout << "1 is true" << endl;
	}
	else {
		cout << "1 is false" << endl;
	}

	// Should report that 0 is false
	if (Rational(0)) {
		cout << "0 is true" << endl;
	}
	else {
		cout << "0 is false" << endl;
	}
}
