#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "Book.h"

// Forward declarations
class User;

class Library {
private:
    std::vector<Book*> books;
    std::vector<User*> users;
    User* currentUser;

    // File operations
    void loadBooksFromCSV();
    void loadUsersFromCSV();
    void saveBooks();
    void saveUsers();
    
public:
    // Constructors & Destructor
    Library();
    ~Library();

    // Authentication
    bool login(const std::string& userId, const std::string& password);
    void logout();

    // Data persistence
    void saveData();

    // Getters
    const std::vector<Book*>& getBooks() const;    // For read-only access
    std::vector<Book*>& getBooks();                // For modification access
    const std::vector<User*>& getUsers() const;    // For read-only access
    std::vector<User*>& getUsers();                // For modification access
    User* getCurrentUser() const;

    // Menu
    void mainMenu();

    void displayBorrowingHistory(const Library& lib) const;
};

#endif // LIBRARY_H 