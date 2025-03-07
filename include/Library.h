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

    void loadBooksFromCSV();
    void loadUsersFromCSV();
    void saveBooks();
    void saveUsers();
    
public:
    Library();
    ~Library();

    bool login(std::string userId, std::string password);
    void logout();
    void saveData();

    // Getters
    const std::vector<Book*>& getBooks() const;
    std::vector<Book*>& getBooks();
    std::vector<User*>& getUsers();
    User* getCurrentUser();

    void mainMenu();
    void displayBorrowingHistory(const Library& lib) const;
};

#endif // LIBRARY_H 