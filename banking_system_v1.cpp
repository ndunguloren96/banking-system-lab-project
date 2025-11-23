#include <iostream>
using namespace std;

// The Base Class (bankAccount)

class bankAccount {
protected:
    int accountNumber;
    double balance;

public:
    // Constructor
    bankAccount(int acctNum = 0, double bal = 0.0) {
        accountNumber = acctNum;
        balance = bal;
    }

    // Standard Operations
    void setAccountNumber(int acctNum) { accountNumber = acctNum; }
    int getAccountNumber() const { return accountNumber; }
    
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount > 0)
            balance += amount;
        else
            cout << "Deposit amount must be positive." << endl;
    }

    // Virtual function to allow overriding by children later
    virtual void withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
        } else {
            cout << "Insufficient funds or invalid amount." << endl;
        }
    }

    virtual void print() const {
        cout << "Account : " << accountNumber << "\nBalance: KES " << balance << endl;
    }
};

// Main function to test ONLY Step 1
int main() {
    cout << "STEP 1 TEST: Base Account Logic" << endl;
    bankAccount myAcct(100, 500.00);
    myAcct.print();
    
    cout << "\nDepositing KES100..." << endl;
    myAcct.deposit(100);
    myAcct.print();
    
    return 0;
}

