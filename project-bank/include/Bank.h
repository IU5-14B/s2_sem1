#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>

#include "BankAccount.h"

class Bank {
public:
    Bank();

    std::string createAccount(const std::string& ownerName);
    BankAccount* getAccount(const std::string& accountNumber);
    double totalBankBalance() const;

private:
    std::vector<BankAccount> accounts_;
    int nextAccountNumber_;
};

#endif
