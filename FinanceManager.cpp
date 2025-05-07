#include "FinanceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <unordered_map>
#include <vector>

using namespace std;

FinanceManager::FinanceManager() : totalIncome(0), totalExpenses(0), monthlyBudget(0) {}

void FinanceManager::addIncome(double amount, string category, string date) {
    transactions.push_back(new Income(amount, category, date));
    totalIncome += amount;
}

void FinanceManager::addExpense(double amount, string category, string date) {
    transactions.push_back(new Expense(amount, category, date));
    totalExpenses += amount;
}

void FinanceManager::displayTransactions() const {
    cout << "\n--- Transaction History ---\n";
    for (const auto& transaction : transactions) {
        transaction->displayTransaction();
    }
    cout << "-----------------------------\n";
}

void FinanceManager::displayCategoryTotals() const {
    unordered_map<string, double> categoryTotals;
    for (const auto& transaction : transactions) {
        categoryTotals[transaction->getCategory()] += transaction->getAmount();
    }

    cout << "\n--- Category Totals ---\n";
    for (const auto& category : categoryTotals) {
        cout << category.first << ": $" << category.second << endl;
    }
    cout << "------------------------\n";
}

void FinanceManager::setMonthlyBudget(double budget) {
    monthlyBudget = budget;
}

void FinanceManager::checkBudgetStatus() const {
    cout << "\n--- Budget Status ---\n";
    cout << "Monthly Budget: $" << monthlyBudget << "\n";
    cout << "Total Expenses: $" << totalExpenses << "\n";
    if (totalExpenses > monthlyBudget) {
        cout << "Warning: Budget exceeded by $" << (totalExpenses - monthlyBudget) << "!\n";
    } else {
        cout << "Budget status: Within limit.\n";
    }
    cout << "----------------------\n";
}

void FinanceManager::displaySummary() const {
    cout << "\n--- Financial Summary ---\n";
    cout << "Total Income: $" << totalIncome << "\n";
    cout << "Total Expenses: $" << totalExpenses << "\n";
    cout << "Net Balance: $" << (totalIncome - totalExpenses) << "\n";
    cout << "------------------------\n";
}

void FinanceManager::exportIncomeStatement(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        file << "Date,Category,Amount\n";
        for (const auto& transaction : transactions) {
            file << transaction->getDate() << ","
                 << transaction->getCategory() << ","
                 << transaction->getAmount() << "\n";
        }
        file.close();
        cout << "Income Statement exported to " << filename << "\n";
    }
}

FinanceManager::~FinanceManager() {
    for (auto& transaction : transactions) {
        delete transaction;
    }
}
