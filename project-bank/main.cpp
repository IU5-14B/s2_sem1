#include <iostream>

#include "Bank.h"

int main() {
    Bank bank;

    std::string acc1 = bank.createAccount("Alice Johnson");
    std::string acc2 = bank.createAccount("Bob Smith");
    std::string acc3 = bank.createAccount("Charlie Brown");

    BankAccount* account1 = bank.getAccount(acc1);
    BankAccount* account2 = bank.getAccount(acc2);
    BankAccount* account3 = bank.getAccount(acc3);

    if (account1) {
        account1->deposit(500.0);
        account1->withdraw(120.0);
    }

    if (account2) {
        account2->deposit(1000.0);
        bool ok = account2->withdraw(2000.0);
        std::cout << "Withdraw from " << acc2 << (ok ? " succeeded" : " failed") << "\n";
    }

    if (account3) {
        bool ok = account3->deposit(-50.0);
        std::cout << "Deposit to " << acc3 << (ok ? " succeeded" : " failed") << "\n";
    }

    std::cout << "\nStatements:\n";
    if (account1) {
        account1->printStatement();
        std::cout << "\n";
    }
    if (account2) {
        account2->printStatement();
        std::cout << "\n";
    }
    if (account3) {
        account3->printStatement();
        std::cout << "\n";
    }

    std::cout << "Total bank balance: " << bank.totalBankBalance() << "\n";
    return 0;
}
