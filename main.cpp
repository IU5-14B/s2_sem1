#include <iostream>
#include <string>
#include <map>

#include "Bank.h"
#include "BankAccount.h"

enum class Language {
    ENGLISH,
    RUSSIAN,
    CHINESE
};

std::map<Language, std::string> languageNames = {
    {Language::ENGLISH, "English"},
    {Language::RUSSIAN, "Русский"},
    {Language::CHINESE, "中文"}
};

class Translator {
private:
    Language currentLanguage;
    
    std::map<Language, std::map<std::string, std::string>> translations = {
        {Language::ENGLISH, {
            {"create_accounts", "Creating accounts..."},
            {"withdraw_result", "Withdraw from "},
            {"succeeded", " succeeded"},
            {"failed", " failed"},
            {"deposit_result", "Deposit to "},
            {"statements", "Statements:"},
            {"total_balance", "Total bank balance: "},
            {"select_language", "Select language / Выберите язык / 选择语言:"},
            {"invalid_choice", "Invalid choice. Using English.\n"}
        }},
        {Language::RUSSIAN, {
            {"create_accounts", "Создание счетов..."},
            {"withdraw_result", "Снятие со счета "},
            {"succeeded", " выполнено"},
            {"failed", " не выполнено"},
            {"deposit_result", "Пополнение счета "},
            {"statements", "Выписки по счетам:"},
            {"total_balance", "Общий баланс банка: "},
            {"select_language", "Выберите язык / Select language / 选择语言:"},
            {"invalid_choice", "Неверный выбор. Используется английский.\n"}
        }},
        {Language::CHINESE, {
            {"create_accounts", "正在创建账户..."},
            {"withdraw_result", "从账户取款 "},
            {"succeeded", " 成功"},
            {"failed", " 失败"},
            {"deposit_result", "向账户存款 "},
            {"statements", "账户对账单:"},
            {"total_balance", "银行总余额: "},
            {"select_language", "选择语言 / Select language / Выберите язык:"},
            {"invalid_choice", "无效选择。将使用英语。\n"}
        }}
    };

public:
    Translator(Language lang = Language::ENGLISH) : currentLanguage(lang) {}
    
    void setLanguage(Language lang) {
        currentLanguage = lang;
    }
    
    std::string get(const std::string& key) const {
        auto langIt = translations.find(currentLanguage);
        if (langIt != translations.end()) {
            auto keyIt = langIt->second.find(key);
            if (keyIt != langIt->second.end()) {
                return keyIt->second;
            }
        }
        return key; // fallback to key if not found
    }
};

Language selectLanguage() {
    std::cout << "\n=== " << "Select language / Выберите язык / 选择语言" << " ===\n";
    std::cout << "1. English\n";
    std::cout << "2. Русский\n";
    std::cout << "3. 中文\n";
    std::cout << "Choice / Выбор / 选择: ";
    
    int choice;
    std::cin >> choice;
    std::cin.ignore(); // clear newline
    
    switch(choice) {
        case 1: return Language::ENGLISH;
        case 2: return Language::RUSSIAN;
        case 3: return Language::CHINESE;
        default: 
            std::cout << "Invalid choice. Using English.\n";
            return Language::ENGLISH;
    }
}

int main() {
    // Select language
    Language lang = selectLanguage();
    Translator t(lang);
    
    Bank bank;

    std::cout << "\n" << t.get("create_accounts") << "\n";
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
        std::cout << t.get("withdraw_result") << acc2 << (ok ? t.get("succeeded") : t.get("failed")) << "\n";
    }

    if (account3) {
        bool ok = account3->deposit(-50.0);
        std::cout << t.get("deposit_result") << acc3 << (ok ? t.get("succeeded") : t.get("failed")) << "\n";
    }

    std::cout << "\n" << t.get("statements") << "\n";
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

    std::cout << t.get("total_balance") << bank.totalBankBalance() << "\n";
    return 0;
}