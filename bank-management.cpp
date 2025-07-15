// BankManagementSystem.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Account {
protected:
    string name;
    int accNumber;
    double balance;

public:
    Account(string n, int num, double bal) : name(n), accNumber(num), balance(bal) {}

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    virtual void display() const {
        cout << "Name: " << name << "\nAccount Number: " << accNumber
             << "\nBalance: $" << fixed << setprecision(2) << balance << "\n";
    }

    int getAccountNumber() const { return accNumber; }
};

class Bank {
    vector<Account> accounts;
    const string dataFile = "accounts.txt";

public:
    Bank() { loadAccounts(); }

    ~Bank() { saveAccounts(); }

    void createAccount() {
        string name;
        int accNum;
        double initBal;

        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Account Number: ";
        cin >> accNum;
        cout << "Initial Balance: ";
        cin >> initBal;

        accounts.emplace_back(name, accNum, initBal);
        cout << "Account created successfully!\n";
    }

    void depositToAccount() {
        int accNum;
        double amount;
        cout << "Enter Account Number: ";
        cin >> accNum;
        cout << "Enter Deposit Amount: ";
        cin >> amount;

        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNum) {
                acc.deposit(amount);
                cout << "Deposit successful!\n";
                return;
            }
        }
        cout << "Account not found.\n";
    }

    void withdrawFromAccount() {
        int accNum;
        double amount;
        cout << "Enter Account Number: ";
        cin >> accNum;
        cout << "Enter Withdrawal Amount: ";
        cin >> amount;

        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNum) {
                if (acc.withdraw(amount))
                    cout << "Withdrawal successful!\n";
                else
                    cout << "Insufficient balance.\n";
                return;
            }
        }
        cout << "Account not found.\n";
    }

    void viewAccount() {
        int accNum;
        cout << "Enter Account Number: ";
        cin >> accNum;

        for (const auto& acc : accounts) {
            if (acc.getAccountNumber() == accNum) {
                acc.display();
                return;
            }
        }
        cout << "Account not found.\n";
    }

    void listAccounts() {
        cout << "\n--- All Accounts ---\n";
        for (const auto& acc : accounts) {
            acc.display();
            cout << "------------------------\n";
        }
    }

private:
    void loadAccounts() {
        ifstream infile(dataFile);
        if (!infile) return;
        string name;
        int num;
        double bal;
        while (infile >> name >> num >> bal) {
            accounts.emplace_back(name, num, bal);
        }
        infile.close();
    }

    void saveAccounts() {
        ofstream outfile(dataFile);
        for (const auto& acc : accounts) {
            outfile << acc.getAccountNumber() << " " << acc.getAccountNumber() << " " << acc.getAccountNumber() << "\n";
        }
        outfile.close();
    }
};

int main() {
    Bank bank;
    int choice;

    do {
        cout << "\n--- Bank Management System ---\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. View Account\n";
        cout << "5. List All Accounts\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.depositToAccount(); break;
            case 3: bank.withdrawFromAccount(); break;
            case 4: bank.viewAccount(); break;
            case 5: bank.listAccounts(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
