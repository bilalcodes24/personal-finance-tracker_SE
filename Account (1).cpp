#include "Account.h"
#include <iostream>
#include <limits>

using namespace std;

User::User(string user, string pass, string recoveryAns)
    : username(user), password(pass), recoveryAnswer(recoveryAns) {}

bool User::checkRecoveryAnswer(const string& answer) {
    return recoveryAnswer == answer;
}

AccountManager::AccountManager() : currentUser(nullptr) {}

bool AccountManager::registerUser(const string& username, const string& password, const string& recoveryAnswer) {
    if (users.find(username) != users.end()) {
        cout << "Username already exists.\n";
        return false;
    }
    users[username] = new User(username, password, recoveryAnswer);
    cout << "User registered successfully!\n";
    return true;
}

bool AccountManager::login(const string& username, const string& password) {
    auto user = users.find(username);
    if (user != users.end() && user->second->password == password) {
        currentUser = user->second;
        cout << "Login successful.\n";
        return true;
    }
    cout << "Invalid username or password.\n";
    return false;
}

void AccountManager::forgotPassword(const string& username) {
    auto user = users.find(username);
    if (user != users.end()) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
        string answer;
        cout << "Answer the security question: ";
        getline(cin, answer);
        if (user->second->checkRecoveryAnswer(answer)) {
            string newPassword;
            cout << "Answer is correct! Please enter your new password: ";
            getline(cin, newPassword);
            user->second->password = newPassword;
            cout << "Password reset successfully.\n";
        } else {
            cout << "Incorrect answer to the security question.\n";
        }
    } else {
        cout << "User not found.\n";
    }
}

void AccountManager::logout() {
    currentUser = nullptr;
    cout << "Logged out successfully.\n";
}

bool AccountManager::isLoggedIn() const {
    return currentUser != nullptr;
}

AccountManager::~AccountManager() {
    for (auto& user : users) {
        delete user.second;
    }
}

