#!/bin/bash

# Build and run the banking application

echo "=== Building Banking Application ==="

# Compile all C++ files
g++ -std=c++11 -o bank_app main.cpp Bank.cpp BankAccount.cpp

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo ""
    echo "=== Running Banking Application ==="
    ./bank_app
else
    echo "Build failed!"
    exit 1
fi