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
        else cout << "Insufficient funds." << endl;
    }
    virtual void print() const {
        cout << "Account : " << accountNumber << "\nBalance: KES " << balance << endl;
    }
};

// Step 2: Checking Account Class

class checkingAccount : public bankAccount { 
private:
    double interestRate;
    double minimumBalance;
    double serviceCharges;

public:
    // Constructor
    checkingAccount(int acctNum, double bal, double intRate, double minBal, double servChg)
        : bankAccount(acctNum, bal) {
        interestRate = intRate;
        minimumBalance = minBal;
        serviceCharges = servChg;
    }

    // Setters and Getters
    void setInterestRate(double rate) { interestRate = rate; }
    double getInterestRate() const { return interestRate; }
    
    void setMinimumBalance(double minBal) { minimumBalance = minBal; }
    double getMinimumBalance() const { return minimumBalance; }
    
    void setServiceCharges(double servChg) { serviceCharges = servChg; }
    double getServiceCharges() const { return serviceCharges; }

    // Business Logic
    void postInterest() {
        balance += (balance * interestRate);
    }

    bool verifyMinimumBalance() const {
        return balance < minimumBalance;
    }

    void writeCheck(double amount) {
        withdraw(amount); 
    }

    // Override Withdraw to include service charges
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
        bankAccount::print(); // Call the base class print first
        cout << "Account Type: Checking\nInterest Rate: " << interestRate 
             << "\nMin Balance: KES " << minimumBalance << endl;
    }
};

// Main function to test only Step 2
int main() {
    cout << "STEP 2 TEST: Checking Account Logic" << endl;
    checkingAccount myCheck(1001, 1000.00, 0.03, 500.00, 20.00); 
    myCheck.print();

    cout << "\n...Writing Check for KES 600..." << endl;
    myCheck.writeCheck(600.00); 
    
    // Balance drops to 400. 400 < 500, so KES 20 fee applied. Final: 380.
    cout << "\nChecking Balance (Expect KES 380)..." << endl;
    myCheck.print(); 
    
    return 0;
}

