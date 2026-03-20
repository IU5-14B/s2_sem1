cmake_minimum_required(VERSION 3.10)
project(project-bank)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основное приложение
add_executable(bank_app
    main.cpp
    src/BankAccount.cpp
    src/Bank.cpp
)

# Тестовое приложение
add_executable(bank_tests
    test.cpp
    src/BankAccount.cpp
    src/Bank.cpp
)

# Общие include директории для обоих приложений
target_include_directories(bank_app PRIVATE include)
target_include_directories(bank_tests PRIVATE include)

# Для удобства сборки, можно сделать bank_tests зависимым от bank_app
# (не обязательно, но помогает при сборке)
add_dependencies(bank_tests bank_app)

# Опционально: добавить цель для запуска тестов
add_custom_target(run_tests
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bank_tests
    DEPENDS bank_tests
    COMMENT "Running bank system tests"
)