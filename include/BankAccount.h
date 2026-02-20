#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>

class BankAccount {
public:
    BankAccount();
    BankAccount(const std::string& accountNumber, const std::string& ownerName, double balance = 0.0);

    bool deposit(double amount);
    bool withdraw(double amount);
    double getBalance() const;
    const std::string& getAccountNumber() const;
    const std::string& getOwnerName() const;

    void printStatement() const;

private:
    std::string accountNumber_;
    std::string ownerName_;
    double balance_;
};

#endif
