#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <unordered_map>

class User {
public:
    std::string username;
    std::string password;
    std::string recoveryAnswer;

    User(std::string user, std::string pass, std::string recoveryAns);
    bool checkRecoveryAnswer(const std::string& answer);
};

class AccountManager {
private:
    std::unordered_map<std::string, User*> users;
    User* currentUser;

public:
    AccountManager();
    bool registerUser(const std::string& username, const std::string& password, const std::string& recoveryAnswer);
    bool login(const std::string& username, const std::string& password);
    void forgotPassword(const std::string& username);
    void logout();
    bool isLoggedIn() const;
    ~AccountManager();
};

#endif
