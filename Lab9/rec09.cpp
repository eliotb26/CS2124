/* 
Eliot Brown
Lab 9 

*/

#include <iostream>
#include <vector>
using namespace std;


//	THIS I WAS PRACTICING 
//class PrintedMaterial {
//public: 
//	PrintedMaterial(unsigned pages) : numOfPages(pages){}
//protected:
//private:
//	unsigned numOfPages;
//};
//
//class Magazine : public PrintedMaterial {
//public: 
//	Magazine(unsigned pages) : PrintedMaterial(pages){}
//protected: 
//private: 
// unsigned pages;
//};





class PrintedMaterial {
public:
	PrintedMaterial(unsigned numPages)
		: pages(numPages)
	{}
	//pure virtual method
	virtual void displayNumPages() const = 0;
protected:
private:
	unsigned pages;
};

void PrintedMaterial::displayNumPages() const {
	cout << pages << endl;
}

class Magazine : public PrintedMaterial {
public:
	Magazine(unsigned numPages)
		: PrintedMaterial(numPages)
	{}
	void displayNumPages() const {
		cout << "Magazine Object ";
		PrintedMaterial::displayNumPages();
	}
protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book(unsigned numPages)
		: PrintedMaterial(numPages)
	{}
protected:
private:
};

class TextBook : public Book {
public:
	TextBook(unsigned numPages, unsigned numIndxPgs)
		: Book(numPages),
		numOfIndexPages(numIndxPgs)
	{}
	void displayNumPages() const {
		cout << "Pages: ";
		PrintedMaterial::displayNumPages();
		cout << "Index pages: ";
		cout << numOfIndexPages << endl;
	}
protected:
private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel(unsigned numPages)
		: Book(numPages)
	{}
	void displayNumPages() const {
		cout << "Novel object ";
		PrintedMaterial::displayNumPages();
		cout << endl;
	}
protected:
private:
};

//void PrintedMaterial::displayNumPages() const{
//	cout << pages << endl;
//}

// tester/modeler code
int main()
{
	TextBook t(5430, 234);
	Novel n(213);
	Magazine m(6);

	/*t.displayNumPages();
	n.displayNumPages();
	m.displayNumPages();*/

	//PrintedMaterial pm = t; // like putting a t into a vector of PrintedMaterials
	//pm.displayNumPages();

	//PrintedMaterial* pmPtr;
	//pmPtr = &t;
	//pmPtr->displayNumPages();


	cout << "\nUsing PrintedMaterial* to \"store\" a TextBook object\n";
	cout << "Now with the virtual mechanism involved\n";
	// should work now that the virtual mechanism is being invoked
	PrintedMaterial* pmPtr;
	pmPtr = &t; // like putting a t into a vector
				// of pointers to PrintedMaterial
				// (that is, pointers to the Base class)
	//pmPtr->displayNumPages();

	//	DELETED 
	// print some stuff by calling a generic function
	//cout << "\nUse a generic function for printing\n";
	//displayNumberOfPages(m);
	//displayNumberOfPages(n);
	//displayNumberOfPages(t);
	PrintedMaterial pm = t; // like putting a t into a vector of PrintedMaterials
	pm.displayNumPages();

	cout << "NOW in VECTOR" << endl;
	vector <PrintedMaterial*> allPrints;
	allPrints.push_back(&t);
	allPrints.push_back(&n);
	allPrints.push_back(&m);
	allPrints[0]->displayNumPages();
	for (size_t ind = 0; ind < allPrints.size(); ++ind) {
		allPrints[ind]->displayNumPages();
		cout << endl;
	}
}