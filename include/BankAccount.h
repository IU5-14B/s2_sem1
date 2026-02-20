#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>

enum class Language {
    ENGLISH,
    RUSSIAN,
    CHINESE
};

class BankAccount {
private:
    std::string accountNumber_;
    std::string ownerName_;
    double balance_;

public:
    BankAccount();
    BankAccount(const std::string& accountNumber, const std::string& ownerName, double balance);

    bool deposit(double amount);
    bool withdraw(double amount);
    
    double getBalance() const;
    const std::string& getAccountNumber() const;
    const std::string& getOwnerName() const;
    
    void printStatement(Language lang = Language::ENGLISH) const;
};

#endif // BANKACCOUNT_H