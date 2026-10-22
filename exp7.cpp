
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class BankException : public exception {
protected:
    string message;

public:
    BankException(string msg) {
        message = msg;
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InsufficientFundsException : public BankException {
public:
    InsufficientFundsException()
        : BankException("Error: Insufficient balance for withdrawal.") {
    }
};

class InvalidAmountException : public BankException {
public:
    InvalidAmountException()
        : BankException("Error: Amount must be greater than zero.") {
    }
};

class BankAccount {
private:
    string name;
    double balance;

public:
    BankAccount(string n, double b) {
        name = n;
        balance = b;
    }

    void deposit(double amount) {
        if (amount <= 0)
            throw InvalidAmountException();

        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0)
            throw InvalidAmountException();

        if (amount > balance)
            throw InsufficientFundsException();

        balance -= amount;
    }

    void display() {
        cout << "Account Holder: " << name << endl;
        cout << "Balance: Rs. " << balance << endl;
    }
};

int main() {
    BankAccount account("Pranav", 8000);

    cout << "Initial Account Details:" << endl;
    account.display();

    try {
        cout << "\nDepositing Rs. 2500..." << endl;
        account.deposit(2500);

        cout << "Withdrawing Rs. 3500..." << endl;
        account.withdraw(3500);

        cout << "Withdrawing Rs. 12000..." << endl;
        account.withdraw(12000);
    }
    catch (const InsufficientFundsException &e) {
        cout << e.what() << endl;
    }
    catch (const InvalidAmountException &e) {
        cout << e.what() << endl;
    }
    catch (const BankException &e) {
        cout << "Bank Exception: " << e.what() << endl;
    }
    catch (const exception &e) {
        cout << "General Exception: " << e.what() << endl;
    }

    cout << "\nFinal Account Details:" << endl;
    account.display();

    return 0;
}
