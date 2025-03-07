#ifndef USER_H
#define USER_H

#include <string>
#include "Account.h"
#include "Library.h"

class User {
protected:
    std::string userId;
    std::string password;
    std::string name;
    Account account;

public:
    User(std::string id, std::string pwd, std::string n);
    virtual ~User();

    // Getters
    std::string getUserId() const;
    std::string getName() const;
    std::string getPassword() const;
    Account& getAccount();
    
    bool checkPassword(std::string pwd) const;
    
    virtual void displayMenu(Library& lib) = 0;
    virtual bool canBorrow() const = 0;
    virtual int getMaxBooks() const = 0;
    virtual int getMaxDays() const = 0;
    virtual bool incursFines() const = 0;
};

class Student : public User {
public:
    Student(std::string id, std::string pwd, std::string n);
    void displayMenu(Library& lib) override;
    bool canBorrow() const override;
    int getMaxBooks() const override;
    int getMaxDays() const override;
    bool incursFines() const override;
};

class Faculty : public User {
public:
    Faculty(std::string id, std::string pwd, std::string n);
    void displayMenu(Library& lib) override;
    bool canBorrow() const override;
    int getMaxBooks() const override;
    int getMaxDays() const override;
    bool incursFines() const override;
};

class Librarian : public User {
public:
    Librarian(std::string id, std::string pwd, std::string n);
    void displayMenu(Library& lib) override;
    bool canBorrow() const override;
    int getMaxBooks() const override;
    int getMaxDays() const override;
    bool incursFines() const override;
};

#endif // USER_H 