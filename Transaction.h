#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
protected:
    double amount;
    std::string category;
    std::string date;

public:
    Transaction(double amt, std::string cat, std::string dt);
    virtual void displayTransaction() const;
    double getAmount() const;
    std::string getCategory() const;
    std::string getDate() const;
    virtual ~Transaction();
};

class Income : public Transaction {
public:
    Income(double amt, std::string cat, std::string dt);
    void displayTransaction() const override;
};

class Expense : public Transaction {
public:
    Expense(double amt, std::string cat, std::string dt);
    void displayTransaction() const override;
};

#endif // TRANSACTION_H
