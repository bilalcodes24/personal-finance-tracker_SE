#include <iostream>
#include "Account.h"
#include "FinanceManager.h"
#include "Transaction.h"
#include "Utility.h"
using namespace std;

int main() {
    AccountManager accountManager;
    FinanceManager financeManager;
    int choice;
    string username, password;

    do {
        cout << "\n=== Personal Finance Tracker ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Forgot Password\n";
        cout << "4. Logout\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();  // clear input buffer

        if (choice == 1) {
            string recoveryAnswer;
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            cout << "Set your security question answer (e.g., What is your pet's name?): ";
            getline(cin, recoveryAnswer);
            accountManager.registerUser(username, password, recoveryAnswer);

        } else if (choice == 2) {
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            if (!accountManager.login(username, password)) {
                cout << "Login failed.\n";
            }

        } else if (choice == 3) {
            cout << "Enter username: ";
            getline(cin, username);
            accountManager.forgotPassword(username);

        } else if (choice == 4) {
            accountManager.logout();
        }

        if (accountManager.isLoggedIn()) {
            int financeChoice;
            cout << "\n=== Finance Manager ===\n";
            cout << "1. Add Income\n";
            cout << "2. Add Expense\n";
            cout << "3. Display Transactions\n";
            cout << "4. Display Category Totals\n";
            cout << "5. Set Monthly Budget\n";
            cout << "6. Check Budget Status\n";
            cout << "7. Display Summary\n";
            cout << "8. Export Income Statement\n";
            cout << "0. Back to Main Menu\n";
            cout << "Enter choice: ";
            cin >> financeChoice;
            cin.ignore();

            if (financeChoice == 1) {
                double amount;
                string category, date;
                cout << "Enter amount: $";
                cin >> amount;
                cin.ignore();
                cout << "Enter category: ";
                getline(cin, category);
                cout << "Enter date (YYYY-MM-DD): ";
                getline(cin, date);
                financeManager.addIncome(amount, category, date);

            } else if (financeChoice == 2) {
                double amount;
                string category, date;
                cout << "Enter amount: $";
                cin >> amount;
                cin.ignore();
                cout << "Enter category: ";
                getline(cin, category);
                cout << "Enter date (YYYY-MM-DD): ";
                getline(cin, date);
                financeManager.addExpense(amount, category, date);

            } else if (financeChoice == 3) {
                financeManager.displayTransactions();

            } else if (financeChoice == 4) {
                financeManager.displayCategoryTotals();

            } else if (financeChoice == 5) {
                double budget;
                cout << "Enter monthly budget: $";
                cin >> budget;
                financeManager.setMonthlyBudget(budget);

            } else if (financeChoice == 6) {
                financeManager.checkBudgetStatus();

            } else if (financeChoice == 7) {
                financeManager.displaySummary();

            } else if (financeChoice == 8) {
                string filename;
                cout << "Enter filename to export: ";
                cin >> filename;
                financeManager.exportIncomeStatement(filename);
            }
        }

    } while (choice != 0);

    return 0;
}
