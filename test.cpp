// test.cpp
#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>

#include "Bank.h"
#include "BankAccount.h"

// Класс для захвата вывода
class OutputCapture {
private:
    std::streambuf* oldCout;
    std::stringstream buffer;
public:
    OutputCapture() {
        oldCout = std::cout.rdbuf(buffer.rdbuf());
    }
    
    ~OutputCapture() {
        std::cout.rdbuf(oldCout);
    }
    
    std::string getOutput() {
        return buffer.str();
    }
    
    void clear() {
        buffer.str("");
        buffer.clear();
    }
};

void printTestHeader(const std::string& testName) {
    std::cout << "\n=== " << testName << " ===\n";
}

void printTestResult(bool passed, const std::string& message = "") {
    if (passed) {
        std::cout << "✓ PASSED: " << message << "\n";
    } else {
        std::cout << "✗ FAILED: " << message << "\n";
    }
}

void testBankAccountCreation() {
    printTestHeader("BankAccount Creation Test");
    
    BankAccount account("1001", "John Doe", 500.0);
    
    assert(account.getAccountNumber() == "1001");
    assert(account.getOwnerName() == "John Doe");
    assert(account.getBalance() == 500.0);
    
    printTestResult(true, "Account created successfully with correct data");
    std::cout << "  Account number: " << account.getAccountNumber() << "\n";
    std::cout << "  Owner name: " << account.getOwnerName() << "\n";
    std::cout << "  Balance: " << account.getBalance() << "\n";
}

void testBankAccountDeposit() {
    printTestHeader("BankAccount Deposit Test");
    
    BankAccount account("1001", "John Doe", 100.0);
    bool result;
    
    // Тест 1: Успешный депозит
    result = account.deposit(50.0);
    assert(result == true);
    assert(account.getBalance() == 150.0);
    printTestResult(true, "Valid deposit of 50.0 worked");
    
    // Тест 2: Депозит с отрицательной суммой
    result = account.deposit(-30.0);
    assert(result == false);
    assert(account.getBalance() == 150.0);
    printTestResult(true, "Invalid deposit of -30.0 rejected");
    
    // Тест 3: Депозит с нулевой суммой
    result = account.deposit(0.0);
    assert(result == false);
    assert(account.getBalance() == 150.0);
    printTestResult(true, "Invalid deposit of 0.0 rejected");
    
    std::cout << "  Final balance: " << account.getBalance() << "\n";
}

void testBankAccountWithdraw() {
    printTestHeader("BankAccount Withdraw Test");
    
    BankAccount account("1001", "John Doe", 200.0);
    bool result;
    
    // Тест 1: Успешное снятие
    result = account.withdraw(50.0);
    assert(result == true);
    assert(account.getBalance() == 150.0);
    printTestResult(true, "Valid withdrawal of 50.0 worked");
    
    // Тест 2: Снятие суммы больше баланса
    result = account.withdraw(200.0);
    assert(result == false);
    assert(account.getBalance() == 150.0);
    printTestResult(true, "Withdrawal of amount > balance rejected");
    
    // Тест 3: Снятие с отрицательной суммой
    result = account.withdraw(-30.0);
    assert(result == false);
    assert(account.getBalance() == 150.0);
    printTestResult(true, "Withdrawal of negative amount rejected");
    
    // Тест 4: Снятие нулевой суммы
    result = account.withdraw(0.0);
    assert(result == false);
    assert(account.getBalance() == 150.0);
    printTestResult(true, "Withdrawal of zero amount rejected");
    
    // Тест 5: Снятие точной суммы баланса
    result = account.withdraw(150.0);
    assert(result == true);
    assert(account.getBalance() == 0.0);
    printTestResult(true, "Withdrawal of exact balance amount worked");
    
    std::cout << "  Final balance: " << account.getBalance() << "\n";
}

void testBankAccountPrintStatement() {
    printTestHeader("BankAccount Print Statement Test");
    
    BankAccount account("1001", "John Doe", 500.0);
    OutputCapture capture;
    
    // Тест английского языка
    account.printStatement(Language::ENGLISH);
    std::string output = capture.getOutput();
    capture.clear();
    
    assert(output.find("Account: 1001") != std::string::npos);
    assert(output.find("Owner: John Doe") != std::string::npos);
    assert(output.find("Balance: 500.00") != std::string::npos);
    printTestResult(true, "English statement printed correctly");
    
    // Тест русского языка
    account.printStatement(Language::RUSSIAN);
    output = capture.getOutput();
    capture.clear();
    
    assert(output.find("Счет: 1001") != std::string::npos);
    assert(output.find("Владелец: John Doe") != std::string::npos);
    assert(output.find("Баланс: 500.00") != std::string::npos);
    printTestResult(true, "Russian statement printed correctly");
    
    // Тест китайского языка
    account.printStatement(Language::CHINESE);
    output = capture.getOutput();
    
    assert(output.find("账户: 1001") != std::string::npos);
    assert(output.find("持有人: John Doe") != std::string::npos);
    assert(output.find("余额: 500.00") != std::string::npos);
    printTestResult(true, "Chinese statement printed correctly");
    
    std::cout << "  All language outputs verified\n";
}

void testBankCreateAccount() {
    printTestHeader("Bank Create Account Test");
    
    Bank bank;
    
    std::string acc1 = bank.createAccount("Alice");
    std::string acc2 = bank.createAccount("Bob");
    std::string acc3 = bank.createAccount("Charlie");
    
    assert(acc1 == "1001");
    assert(acc2 == "1002");
    assert(acc3 == "1003");
    printTestResult(true, "Account numbers generated correctly");
    
    BankAccount* account = bank.getAccount("1001");
    assert(account != nullptr);
    assert(account->getOwnerName() == "Alice");
    assert(account->getBalance() == 0.0);
    printTestResult(true, "Account data stored correctly");
    
    std::cout << "  Created accounts: " << acc1 << ", " << acc2 << ", " << acc3 << "\n";
}

void testBankGetAccount() {
    printTestHeader("Bank Get Account Test");
    
    Bank bank;
    bank.createAccount("Alice");
    bank.createAccount("Bob");
    
    // Тест существующего аккаунта
    BankAccount* account = bank.getAccount("1001");
    assert(account != nullptr);
    assert(account->getOwnerName() == "Alice");
    printTestResult(true, "Existing account found");
    
    // Тест несуществующего аккаунта
    account = bank.getAccount("9999");
    assert(account == nullptr);
    printTestResult(true, "Non-existing account returns nullptr");
    
    // Тест с пустой строкой
    account = bank.getAccount("");
    assert(account == nullptr);
    printTestResult(true, "Empty account number returns nullptr");
}

void testBankTotalBalance() {
    printTestHeader("Bank Total Balance Test");
    
    Bank bank;
    
    assert(bank.totalBankBalance() == 0.0);
    printTestResult(true, "Empty bank balance is 0");
    
    std::string acc1 = bank.createAccount("Alice");
    std::string acc2 = bank.createAccount("Bob");
    
    BankAccount* account1 = bank.getAccount(acc1);
    BankAccount* account2 = bank.getAccount(acc2);
    
    account1->deposit(100.0);
    account2->deposit(200.0);
    
    assert(bank.totalBankBalance() == 300.0);
    printTestResult(true, "Total balance after deposits: 300.0");
    
    account1->withdraw(50.0);
    assert(bank.totalBankBalance() == 250.0);
    printTestResult(true, "Total balance after withdrawal: 250.0");
    
    std::cout << "  Final total balance: " << bank.totalBankBalance() << "\n";
}

void testBankCompleteScenario() {
    printTestHeader("Complete Bank Scenario Test");
    
    Bank bank;
    
    // Создаем аккаунты
    std::string aliceAcc = bank.createAccount("Alice Johnson");
    std::string bobAcc = bank.createAccount("Bob Smith");
    
    BankAccount* alice = bank.getAccount(aliceAcc);
    BankAccount* bob = bank.getAccount(bobAcc);
    
    // Операции с аккаунтами
    bool result;
    
    // Alice: депозит 500, снятие 120
    result = alice->deposit(500.0);
    assert(result == true);
    result = alice->withdraw(120.0);
    assert(result == true);
    
    // Bob: депозит 1000, попытка снять 2000 (должна провалиться)
    result = bob->deposit(1000.0);
    assert(result == true);
    result = bob->withdraw(2000.0);
    assert(result == false);
    
    // Проверяем балансы
    assert(alice->getBalance() == 380.0);
    assert(bob->getBalance() == 1000.0);
    assert(bank.totalBankBalance() == 1380.0);
    
    printTestResult(true, "All operations executed correctly");
    std::cout << "  Alice balance: " << alice->getBalance() << "\n";
    std::cout << "  Bob balance: " << bob->getBalance() << "\n";
    std::cout << "  Total balance: " << bank.totalBankBalance() << "\n";
}

void testEdgeCases() {
    printTestHeader("Edge Cases Test");
    
    Bank bank;
    std::string acc = bank.createAccount("Test User");
    BankAccount* account = bank.getAccount(acc);
    
    // Тест: депозит очень маленькой суммы
    bool result = account->deposit(0.01);
    assert(result == true);
    assert(account->getBalance() == 0.01);
    printTestResult(true, "Very small deposit (0.01) works");
    
    // Тест: депозит большой суммы
    result = account->deposit(1000000.0);
    assert(result == true);
    assert(account->getBalance() == 1000000.01);
    printTestResult(true, "Large deposit works");
    
    // Тест: снятие точной суммы
    result = account->withdraw(1000000.01);
    assert(result == true);
    assert(account->getBalance() == 0.0);
    printTestResult(true, "Withdrawal of exact balance works");
    
    // Тест: создание множества аккаунтов
    for (int i = 0; i < 100; i++) {
        bank.createAccount("User" + std::to_string(i));
    }
    
    BankAccount* lastAccount = bank.getAccount(std::to_string(1101));
    assert(lastAccount != nullptr);
    printTestResult(true, "Multiple account creation (100 accounts) works");
    
    // Тест: депозит отрицательной суммы
    result = account->deposit(-50.0);
    assert(result == false);
    printTestResult(true, "Negative deposit rejected");
    
    // Тест: снятие отрицательной суммы
    result = account->withdraw(-30.0);
    assert(result == false);
    printTestResult(true, "Negative withdrawal rejected");
    
    // Тест: депозит нуля
    result = account->deposit(0.0);
    assert(result == false);
    printTestResult(true, "Zero deposit rejected");
    
    // Тест: снятие нуля
    result = account->withdraw(0.0);
    assert(result == false);
    printTestResult(true, "Zero withdrawal rejected");
    
    std::cout << "  All edge cases handled correctly\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << "   BANK SYSTEM UNIT TESTS\n";
    std::cout << "========================================\n";
    
    try {
        testBankAccountCreation();
        testBankAccountDeposit();
        testBankAccountWithdraw();
        testBankAccountPrintStatement();
        testBankCreateAccount();
        testBankGetAccount();
        testBankTotalBalance();
        testBankCompleteScenario();
        testEdgeCases();
        
        std::cout << "\n========================================\n";
        std::cout << "   ALL TESTS PASSED SUCCESSFULLY!\n";
        std::cout << "========================================\n";
        
    } catch (const std::exception& e) {
        std::cout << "\n❌ TEST FAILED with exception: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cout << "\n❌ TEST FAILED with unknown exception\n";
        return 1;
    }
    
    return 0;
}