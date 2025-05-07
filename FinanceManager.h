#ifndef FINANCEMANAGER_H
#define FINANCEMANAGER_H

#include "Transaction.h"
#include <vector>

class FinanceManager {
private:
    std::vector<Transaction*> transactions;
    double totalIncome;
    double totalExpenses;
    double monthlyBudget;

public:
    FinanceManager();
    void addIncome(double amount, std::string category, std::string date);
    void addExpense(double amount, std::string category, std::string date);
    void displayTransactions() const;
    void displayCategoryTotals() const;
    void setMonthlyBudget(double budget);
    void checkBudgetStatus() const;
    void displaySummary() const;
    void exportIncomeStatement(const std::string& filename) const;
    ~FinanceManager();
};

#endif // FINANCEMANAGER_H
