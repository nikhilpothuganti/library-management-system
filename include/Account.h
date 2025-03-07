#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include <string>
#include <ctime>
#include "Book.h"

// Forward declaration
class Library;

struct BorrowingRecord {
    std::string ISBN;
    time_t borrowDate;
    time_t dueDate;
    time_t returnDate;
    bool returned;
};

class Account {
private:
    std::vector<Book*> borrowedBooks;
    std::vector<BorrowingRecord> borrowHistory;
    double fines;
    std::string userId;

public:
    Account();

    void setUserId(const std::string& id);
    std::vector<Book*>& getBorrowedBooks();
    std::vector<BorrowingRecord>& getBorrowHistory();
    double getFines() const;
    void addFine(double amount);
    void clearFines();

    void removeBorrowedBook(Book* book);
    void updateFines(int maxDays, bool isFaculty, const std::string& userId);
    void addBorrowedBook(Book* book, int maxDays);
    void displayBorrowingHistory(const Library& lib) const;
};

#endif // ACCOUNT_H 