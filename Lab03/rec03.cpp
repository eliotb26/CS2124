/* 
Eliot Brown 
Rec03
lab 3
9/20/19

Purpose: This lab does a lot. This lab keeps tracks of transactions in 
bank accounts and holds the information. 
*/

//This lab is so unoragized and hard to follow 
//also a lot was barely covered in class so far and 
// hard to understand. Also notes online do not show
// friends. 


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;



/*
Task 3 


	class Transactions {
	public: 
		Transactions(string first, int sec)
			: transactionType(first), amount(sec) {}
		const string& gettype() const { return transactionType ; }
		const int& getamount() const { return amount; }

	private:
		string transactionType;
		int amount;
	};
*/


//Task 2 & 3 & 4

class BankAccount {
	//get Name() and have ostream& as its own for part 1
	friend ostream& operator << (ostream& os, const BankAccount& bankAccount) {  //doesnt make this function part of the class
		os << "Name: " << bankAccount.name << "age: " << bankAccount.number;
		return os;
	}

	class Transactions {
		public:
			Transactions(const string& type, int amount) 
				: transactionType(type), amount(amount) {}
			const string& gettype() const { return transactionType; }
			const int& getamount() const { return amount; }

		private:
			string transactionType;
			int amount;
		};

	private:
		//creates and stores the transactions as well as balance
		string name;
		int number;
		int balance;
		vector<Transactions> transactionsVec;
	
	public:
		BankAccount(const string& bankName, int accountNum) : name(bankName), number(accountNum)
		{ }
		//const string& getName() const { return name; }
		//int getNumber() const { return number; }

		void display(ostream& os = cout) const {
			os << "BankAccount: " << name << " " << number << endl;
		}
		void showBalance(ostream& os = cout) const {
			os << "BankAccount: " << balance << endl;
		}

		void deposit(const int amount) {
			balance += amount;
			
			Transactions deposit_num("deposit", amount);
			transactionsVec.push_back(deposit_num);

		}
		void withdrawal(const int amount) {

			if ((balance - amount) < 0) {
				cerr << "Balanace is negative" << endl;
			}
			else {
				balance -= amount;
			}
			Transactions withdraw_num("withdraw", amount);
			transactionsVec.push_back(withdraw_num);
		}
		
	
		void displayBalance(ostream& os = cout) const { // to test code
			os << "Transactions" << balance << endl;
		}
		const string& gettype() const { return name; }
		const int& getamount() const { return number; }
	
	
};

//ostream& operator << (ostream& os, const BankAccount& account) {
//	os << account.getName() << "age: " << account.getNumber();
//	return os;
//}

void Task2(ifstream& accountsFile) {
	vector <BankAccount> accountsVec; 
	string name;
	int number;
	while (accountsFile >> name >> number) {
		//BankAccount new_account; //TODO check if this is write for beginning of 2
		//name = new_account.name;
		//number = new_account.number;
		//accountsVec.push_back(BankAccount(name, number));
		cout << "working";   //TODO can just put in the main 
		accountsVec.emplace_back(name, number); 
	}
	accountsFile.close();
	for (size_t person = 0; person < accountsVec.size(); ++person) {
		//accountsVec[person].display();
		cout << accountsVec[person];
	}
}


/* 
Task 1 
*/

struct Info {
	string bankName;
	int accountNum;
};

void Q1B(vector <Info> accountsVec, ifstream& accountsFile) {  //TODO can move all into the main 
	accountsVec.clear();
	//ifstream accountsFile("accounts.txt");
	string bankName;
	int accountNum;

	string name;
	int number;
	while (accountsFile >> name >> number) {
		cout << "working";
		Info InfoNew{name, number};
		accountsVec.push_back(InfoNew);
	}
	accountsFile.close();
	for (size_t person = 0; person < accountsVec.size(); ++person) {
		cout << accountsVec[person].bankName << ": " << accountsVec[person].accountNum << endl;
	}

}


int main() {
	//ifstream accountsFile;
	//open(accountsFile);
	ifstream accountsFile("accounts.txt");
	if (!accountsFile) {
		cerr << "Could not open the file.\n";
		exit(1);
	}
	string name;
	int number;
	vector<Info> accountsVec;
	while (accountsFile >> name >> number) {
		Info newInfo;
		newInfo.bankName = name;
		newInfo.accountNum = number;
		accountsVec.push_back(newInfo);
	}
	for (size_t person = 0; person < accountsVec.size(); ++person) {
		cout << accountsVec[person].bankName << ": " << accountsVec[person].accountNum << endl;
	}
	accountsVec.clear();

	//part B Question 1 
	//ifstream accountsFile;
	Q1B(accountsVec, accountsFile); //TODO something with vector


	Task2(accountsFile); //TODO class is made wrong

	ifstream files("transactionsFile.txt");
	if (!files) {
		cerr << "could not open the file .\n";
		exit(1);
	}


	vector<BankAccount> class_accounts;
	vector<BankAccount> allAccounts;
	string command;
	string name;
	int number;
	int amount;
	while (files >> command) {
		//This loop was used to determine whether I was depositing, withdrawing or making another account
		if (command == "Account") {
			files >> name >> number;
			BankAccount my_account(name, number);
			class_accounts.push_back(my_account);

		}

		if (command == "Deposit") {
			files >> number >> amount;
			for (BankAccount& current : class_accounts) {
				if (current.getamount() == number) {
					current.deposit(amount);
				}
			}

		}

		if (command == "Withdraw") {
			files >> number >> amount;
			for (BankAccount& current : class_accounts) {
				if (current.getamount() == number) {
					current.withdrawal(amount);
				}
			}
		}
	}


	accountsFile.close();
}

/*
int main() {
	makeAccount();
}
*/

