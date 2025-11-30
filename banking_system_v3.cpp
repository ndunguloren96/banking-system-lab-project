#include <iostream>
using namespace std;

class bankAccount {
protected:
    int accountNumber;
    double balance;
public:
    bankAccount(int acctNum = 0, double bal = 0.0) {
        accountNumber = acctNum;
        balance = bal;
    }
    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }
    virtual void withdraw(double amount) {
        if (amount > 0 && balance >= amount) balance -= amount;
    }
    virtual void print() const {
        cout << "Account : " << accountNumber << "\nBalance: KES " << balance << endl;
    }
};

// STEP 3: The Savings Account Class

class savingsAccount : public bankAccount { 
private:
    double interestRate;

public:
    // Constructor
    savingsAccount(int acctNum, double bal, double intRate)
        : bankAccount(acctNum, bal) {
        interestRate = intRate;
    }

    void setInterestRate(double rate) { interestRate = rate; }
    double getInterestRate() const { return interestRate; }

    void postInterest() {
        balance += (balance * interestRate);
    }

    void withdraw(double amount) override {
        bankAccount::withdraw(amount); // Use standard withdrawal logic
    }

    void print() const override {
        bankAccount::print();
        cout << "Account Type: Savings\nInterest Rate: " << interestRate << endl;
    }
};

// Test Step 3
int main() {
    cout << "STEP 3 TEST: Savings Account Logic " << endl;
    savingsAccount mySave(2002, 2000.00, 0.05); 
    mySave.print();

    cout << "\n...Posting Interest (5%)..." << endl;
    mySave.postInterest(); 
    mySave.print(); // Expect KES 2100

    return 0;
}

