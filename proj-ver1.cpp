#include <iostream>
#include <string>

using namespace std;

class Transaction { // base class
protected:
    double amount;
    string category;
    string date;

public:
    Transaction(double amt, string cat, string dt) : amount(amt), category(cat), date(dt) {}

    virtual void displayTransaction() const {
        cout << date << " | " << category << " | $" << amount << endl;
    }

    double getAmount() const {
        return amount;
    }

    string getCategory() const {
        return category;
    }

    virtual ~Transaction() {}
};

class Income : public Transaction { // Income derived class
public:
    Income(double amt, string cat, string dt) : Transaction(amt, cat, dt) {}

    void displayTransaction() const override {
        cout << "[INCOME] " << date << " | " << category << " | +$" << amount << endl;
    }
};

class Expense : public Transaction { // Expense derived class
public:
    Expense(double amt, string cat, string dt) : Transaction(amt, cat, dt) {}

    void displayTransaction() const override {
        cout << "[EXPENSE] " << date << " | " << category << " | -$" << amount << endl;
    }
};

class FinanceManager { // contains all functionalities
private:
    Transaction** transactions;
    int transactionCount;
    int capacity;
    double totalIncome;
    double totalExpenses;
    double monthlyBudget;

public:
    FinanceManager() {
        capacity = 100; // set array capacity
        transactionCount = 0;
        totalIncome = 0;
        totalExpenses = 0;
        transactions = new Transaction*[capacity];
    }

    void addIncome(double amount, string category, string date) {
        if (transactionCount < capacity) {
            transactions[transactionCount++] = new Income(amount, category, date);
            totalIncome += amount;
        } else {
            cout << "Transaction limit reached.\n";
        }
    }

    void addExpense(double amount, string category, string date) {
        if (transactionCount < capacity) {
            transactions[transactionCount++] = new Expense(amount, category, date);
            totalExpenses += amount;
        } else {
            cout << "Transaction limit reached.\n";
        }
    }

    void displayTransactions() const {
        cout << "\n--- Transaction History ---\n";
        for (int i = 0; i < transactionCount; ++i) {
            transactions[i]->displayTransaction();
        }
        cout << "-----------------------------\n";
    }

    void displayByCategory() const {
        string targetCategory;
        cout << "Enter category to search: ";
        cin.ignore(); // to clear input buffer
        getline(cin, targetCategory);

        cout << "\n--- Transactions in Category: " << targetCategory << " ---\n";
        for (int i = 0; i < transactionCount; ++i) {
            if (transactions[i]->getCategory() == targetCategory) {
                transactions[i]->displayTransaction();
            }
        }
        cout << "---------------------------------------------\n";
    }

    void displayCategoryTotals() const {
        struct CategorySummary {
            string category;
            double total;
        } summaries[20];

        int summaryCount = 0;

        for (int i = 0; i < transactionCount; ++i) {
            string cat = transactions[i]->getCategory();
            double amt = transactions[i]->getAmount();
            bool found = false;

            for (int j = 0; j < summaryCount; ++j) {
                if (summaries[j].category == cat) {
                    summaries[j].total += amt;
                    found = true;
                    break;
                }
            }

            if (!found && summaryCount < 20) {
                summaries[summaryCount++] = {cat, amt};
            }
        }

        cout << "\n--- Category Totals ---\n";
        for (int i = 0; i < summaryCount; ++i) {
            cout << summaries[i].category << " : $" << summaries[i].total << endl;
        }
        cout << "------------------------\n";
    }

    void setMonthlyBudget(double budget) {
        monthlyBudget = budget;
    }

    void checkBudgetStatus() const {
        cout << "\n--- Budget Monitoring ---\n";
        cout << "Monthly Budget: $" << monthlyBudget << endl;
        cout << "Total Expenses: $" << totalExpenses << endl;
        if (totalExpenses > monthlyBudget) {
            cout << "Warning: Budget exceeded by $" << (totalExpenses - monthlyBudget) << "!\n";
        }
        else {
            cout << "Budget status: Within limit.\n";
        }
        cout << "--------------------------\n";
    }

    void displaySummary() const {
        cout << "\n--- Financial Summary ---\n";
        cout << "Total Income: $" << totalIncome << endl;
        cout << "Total Expenses: $" << totalExpenses << endl;
        cout << "Net Balance: $" << (totalIncome - totalExpenses) << endl;
        cout << "-----------------------------\n";
    }

    ~FinanceManager() {
        for (int i = 0; i < transactionCount; ++i) {
            delete transactions[i];
        }
        delete[] transactions;
    }
};

int main() {
    FinanceManager myFinance;
    int choice;

    do {
        cout << "\n=== Personal Finance Tracker ===\n";
        cout << "1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. View Transactions\n";
        cout << "4. Search Transactions by Category\n";
        cout << "5. View Totals by Category\n";
        cout << "6. Set Budget\n";
        cout << "7. Check Budget Status\n";
        cout << "8. View Summary\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            double amount;
            string category, date;
            cout << "Enter amount: ";
            cin >> amount;
            cin.ignore(); // flush newline
            cout << "Enter category (e.g., Salary, Bonus): ";
            getline(cin, category);
            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, date);
            myFinance.addIncome(amount, category, date);
        }
        else if (choice == 2) {
            double amount;
            string category, date;
            cout << "Enter amount: ";
            cin >> amount;
            cin.ignore(); // flush newline
            cout << "Enter category (e.g. Rent, Food, Bills): ";
            getline(cin, category);
            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, date);
            myFinance.addExpense(amount, category, date);
        }
        else if (choice == 3) {
            myFinance.displayTransactions();
        }
        else if (choice == 4) {
            myFinance.displayByCategory();
        }
        else if (choice == 5) {
            myFinance.displayCategoryTotals();
        }
        else if (choice == 6) {
            double budget;
            cout << "Enter monthly budget: ";
            cin >> budget;
            myFinance.setMonthlyBudget(budget);
        }
        else if (choice == 7) {
            myFinance.checkBudgetStatus();
        }
        else if (choice == 8) {
            myFinance.displaySummary();
        }
    } while (choice != 9);

    cout << "Exiting...\n";
    return 0;
}
