#include "BankAccount.h"
#include <iomanip>
#include <iostream>

BankAccount::BankAccount() : accountNumber_(""), ownerName_(""), balance_(0.0) {}

BankAccount::BankAccount(const std::string& accountNumber, const std::string& ownerName, double balance)
    : accountNumber_(accountNumber), ownerName_(ownerName), balance_(balance) {}

bool BankAccount::deposit(double amount) {
    if (amount <= 0.0) {
        return false;
    }
    balance_ += amount;
    return true;
}

bool BankAccount::withdraw(double amount) {
    if (amount <= 0.0 || amount > balance_) {
        return false;
    }
    balance_ -= amount;
    return true;
}

double BankAccount::getBalance() const { return balance_; }

const std::string& BankAccount::getAccountNumber() const { return accountNumber_; }

const std::string& BankAccount::getOwnerName() const { return ownerName_; }

void BankAccount::printStatement(Language lang) const {
    switch(lang) {
        case Language::ENGLISH:
            std::cout << "Account: " << accountNumber_ << "\n"
                      << "Owner: " << ownerName_ << "\n"
                      << "Balance: " << std::fixed << std::setprecision(2) << balance_ << "\n";
            break;
            
        case Language::RUSSIAN:
            std::cout << "Счет: " << accountNumber_ << "\n"
                      << "Владелец: " << ownerName_ << "\n"
                      << "Баланс: " << std::fixed << std::setprecision(2) << balance_ << "\n";
            break;
            
        case Language::CHINESE:
            std::cout << "账户: " << accountNumber_ << "\n"
                      << "持有人: " << ownerName_ << "\n"
                      << "余额: " << std::fixed << std::setprecision(2) << balance_ << "\n";
            break;
    }
}