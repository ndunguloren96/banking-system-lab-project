#include <iostream>
using namespace std;

// STEP 1: The Base Class (bankAccount)

class bankAccount {
protected:
    int accountNumber;
    double balance;

public:
    bankAccount(int acctNum = 0, double bal = 0.0) {
        accountNumber = acctNum;
        balance = bal;
    }

    void setAccountNumber(int acctNum) { accountNumber = acctNum; }
    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount > 0) balance += amount;
        else cout << "Deposit amount must be positive." << endl;
    }

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

// Step 2: The Checking Account Class

class checkingAccount : public bankAccount { 
private:
    double interestRate;
    double minimumBalance;
    double serviceCharges;

public:
    checkingAccount(int acctNum, double bal, double intRate, double minBal, double servChg)
        : bankAccount(acctNum, bal) {
        interestRate = intRate;
        minimumBalance = minBal;
        serviceCharges = servChg;
    }

    void setInterestRate(double rate) { interestRate = rate; }
    double getInterestRate() const { return interestRate; }
    void setMinimumBalance(double minBal) { minimumBalance = minBal; }
    double getMinimumBalance() const { return minimumBalance; }
    void setServiceCharges(double servChg) { serviceCharges = servChg; }
    double getServiceCharges() const { return serviceCharges; }

    void postInterest() {
        balance += (balance * interestRate);
    }

    bool verifyMinimumBalance() const {
        return balance < minimumBalance;
    }

    void writeCheck(double amount) {
        withdraw(amount); 
    }

    void withdraw(double amount) override {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            if (verifyMinimumBalance()) {
                balance -= serviceCharges;
                cout << "Notice: Balance below minimum. Service charge applied: KES " << serviceCharges << endl;
            }
        } else {
            cout << "Insufficient funds to write check/withdraw." << endl;
        }
    }

    void print() const override {
        bankAccount::print();
        cout << "Account Type: Checking\nInterest Rate: " << interestRate 
             << "\nMin Balance: KES " << minimumBalance << endl;
    }
};



// Step 3: The Savings Account Class

class savingsAccount : public bankAccount { 
private:
    double interestRate;

public:
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
        bankAccount::withdraw(amount); 
    }

    void print() const override {
        bankAccount::print();
        cout << "Account Type: Savings\nInterest Rate: " << interestRate << endl;
    }
};


// Step 4: The Main Execution (Test)

int main() {
    cout << "BANKING SYSTEM TEST\n" << endl;

    // Test Checking Account
    cout << "Creating Checking Account..." << endl;
    checkingAccount myCheck(1001, 1000.00, 0.03, 500.00, 20.00); 
    myCheck.print();

    cout << "\nWriting Check for KES 600..." << endl;
    myCheck.writeCheck(600.00); 
    
    cout << "\nChecking Balance after transaction..." << endl;
    myCheck.print(); 
    
    cout << "\nPosting Interest..." << endl;
    myCheck.postInterest();
    myCheck.print();


    // Test Savings Account
    cout << "Creating Savings Account..." << endl;
    savingsAccount mySave(2002, 2000.00, 0.05); 
    mySave.print();

    cout << "\nDepositing KES 500..." << endl;
    mySave.deposit(500.00);
    
    cout << "\nPosting Interest..." << endl;
    mySave.postInterest(); 
    
    mySave.print();

    return 0;
}

