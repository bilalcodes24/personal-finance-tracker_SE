#include "Transaction.h"
#include <iostream>
#include <ctime>  // For time functions
using namespace std;

Transaction::Transaction(double amt, string cat, string dt)
    : amount(amt), category(cat), date(dt) {}

void Transaction::displayTransaction() const {
    cout << date << " | " << category << " | $" << amount << endl;
}

double Transaction::getAmount() const {
    return amount;
}

string Transaction::getCategory() const {
    return category;
}

string getDate() {
    time_t now = time(0);
    tm* localtm = localtime(&now);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtm);

    return string(buffer);
}

Transaction::~Transaction() {}

Income::Income(double amt, string cat, string dt)
    : Transaction(amt, cat, dt) {}

void Income::displayTransaction() const {
    cout << "[INCOME] " << date << " | " << category << " | +$" << amount << endl;
}

Expense::Expense(double amt, string cat, string dt)
    : Transaction(amt, cat, dt) {}

void Expense::displayTransaction() const {
    cout << "[EXPENSE] " << date << " | " << category << " | -$" << amount << endl;
}
