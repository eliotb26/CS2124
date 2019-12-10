        //
//  Lab 3 Correct 
//Eliot Brown
//  OOP Lab 3
//
//
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

struct Accounts{
    string name;
    int account_number;
};
    
class Full_Account{
    friend ostream& operator<<(ostream& os, const Full_Account& thePerson);
    //This creates the class transactions class that will be used with full accounts
    class Transactions {
        //friend ostream& operator<<(ostream& os, const Full_Account& thePerson);
        private:
            string type;
            int amount;

        
        public:
        
        Transactions(string first, int sec)
        : type(first), amount(sec) {}
        
        const string& gettype() const { return type; }
        const int& getamount() const { return amount; }
        
        
    };
    
    private:
        //This creates and stores the transactions as well as the balances
        vector <Transactions> transactions;
        string name;
        int account_number ;
        int balance = 0;
    
    public:
    
    Full_Account(string first_name, int all_numbers )
    : name(first_name), account_number(all_numbers) {}
    
    void deposit(int amount){
        //This is for depositing the amount into the account
        balance += amount;
        
        Transactions deposit_num ("deposit ", amount);
        transactions.push_back(deposit_num);
    }
    void withdraw(int amount){
        //This is for withdrawing money from the account as well as placing an error if the balance would be negative
        if ((balance - amount) < 0){
            cerr << "Balance is negative" << endl;
        }else{
            balance -= amount ;
        }
        
        Transactions withdraw_num ("withdraw ", amount);
        transactions.push_back(withdraw_num);
    }
    
    const string& gettype() const { return name; }
    const int& getamount() const { return account_number; }
    
    
};

 ostream& operator<<(ostream& os, const Full_Account& thePerson) {
     //This is how my balances as well as poeple and amounts will be displayed
    os << "Person: " << thePerson.name <<' '<< thePerson.account_number << ' ' << thePerson.balance << endl ;
    for (const Full_Account :: Transactions & full : thePerson.transactions){
        os << full.gettype() << full.getamount() << endl ;
        
    }
    return os;
    
}

void Fill_vector(ifstream & file ,vector<Accounts> & my_vector){
    // This function was used to fill my vector
    string name ;
    int number;
    while (file >> name >> number){
        Accounts Bank_account ;
        Bank_account.name = name;
        Bank_account.account_number = number ;
        my_vector.push_back(Bank_account);
        
    }
}

void Fill_second_vector(ifstream & file ,vector<Accounts> & my_vector){
    // This function was used to fill my vector with Bank Accounts
    file.open("accounts.txt");
    string name ;
    int number;
    while (file >> name >> number){
        Accounts Bank_account{name,number};
        my_vector.push_back(Bank_account);
    }
    file.close();
}
    
void Fill_third_vector(ifstream & file, vector<Full_Account> & my_accounts){
    //This vector was used to fill my vector will the complete accounts
    file.open("accounts.txt");
    string name ;
    int number;
    while (file >> name >> number){
//        Full_Account my_class(name,number);
//        my_accounts.emplace_back(my_class);
        my_accounts.emplace_back(Full_Account(name, number));
    }
}





void Display_vector(const vector<Accounts> & full){
    // this function was specifically made to jsut display my account objects
    for (const Accounts & objects : full ){
        cout << objects.name << ' '<< objects.account_number << endl ;
        }
    
    }



void Display_class_vector(const vector<Full_Account> & full){
    //This function was made to display all my objects from the class
for (const Full_Account & object : full ){
    //cout << object.getName() << ' '<< object.getNumber()<< endl ;
    cout<< object <<endl;
    }

}


int main() {
    
    ifstream file("accounts.txt");
       if (!file){
           cerr << "could not open the file .\n";
           exit(1);
       }
    
    vector<Accounts> full_objects ;
    
    vector<Full_Account> class_accounts;
    
//    Fill_vector(file,full_objects);
//    Display_vector(full_objects);
    full_objects.clear();
    file.close();
    
//
//    Fill_second_vector(file,full_objects);
//    Display_vector(full_objects);
    
//
//    Fill_third_vector(file,class_accounts);
//    Display_class_vector(class_accounts);
//
    ifstream files("transactions.txt");
    if (!files){
        cerr << "could not open the file .\n";
        exit(1);
    }
    
    string command;
    string name ;
    int number;
    int amount;
    while(files >> command ){
        //This loop was used to determine whether I was depositing, withdrawing or making another account
        if (command == "Account"){
            files >> name >> number;
            Full_Account my_account(name,number);
            class_accounts.push_back(my_account);
            
        }
        
        if (command == "Deposit"){
            files >> number >> amount ;
            for (Full_Account & current : class_accounts){
                if (current.getamount() == number){
                    current.deposit(amount);
                }
            }
            
        }
        
        if (command == "Withdraw"){
            files >> number >>  amount ;
            for (Full_Account & current : class_accounts){
                if (current.getamount() == number){
                    current.withdraw(amount);
                }
            }
        }
    }
    Display_class_vector(class_accounts);
    

   
}
