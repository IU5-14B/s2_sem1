#include "Bank.h"

Bank::Bank() : nextAccountNumber_(1001) {}

std::string Bank::createAccount(const std::string& ownerName) {
    std::string accountNumber = std::to_string(nextAccountNumber_++);
    accounts_.emplace_back(accountNumber, ownerName, 0.0);
    return accountNumber;
}

BankAccount* Bank::getAccount(const std::string& accountNumber) {
    for (auto& account : accounts_) {
        if (account.getAccountNumber() == accountNumber) {
            return &account;
        }
    }
    return nullptr;
}

double Bank::totalBankBalance() const {
    double total = 0.0;
    for (const auto& account : accounts_) {
        total += account.getBalance();
    }
    return total;
}
