cmake_minimum_required(VERSION 3.10)
project(project-bank)

set(CMAKE_CXX_STANDARD 17)

add_executable(bank_app
    main.cpp
    src/BankAccount.cpp
    src/Bank.cpp
)

target_include_directories(bank_app PRIVATE include)
