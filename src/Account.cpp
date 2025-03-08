#include "../include/Account.h"
#include "../include/Library.h"
#include <algorithm>

using namespace std;

Account::Account() : fines(0) {}

void Account::setUserId(const string& id) { 
    userId = id; 
}

vector<Book*>& Account::getBorrowedBooks() { 
    return borrowedBooks; 
}

vector<BorrowingRecord>& Account::getBorrowHistory() { 
    return borrowHistory; 
}

double Account::getFines() const { 
    return fines; 
}

void Account::addFine(double amount) { 
    fines += amount; 
}

void Account::clearFines() { 
    fines = 0; 
}

void Account::removeBorrowedBook(Book* book) {
    // Remove from borrowed books list
    borrowedBooks.erase(
        remove(borrowedBooks.begin(), borrowedBooks.end(), book),
        borrowedBooks.end()
    );

    // Update the corresponding history record and calculate fines
    time_t now = time(nullptr);
    for(auto& record : borrowHistory) {
        if(record.ISBN == book->getISBN() && !record.returned) {
            record.returnDate = now;
            record.returned = true;
            
            // Calculate fines if returned after due date
            if(now > record.dueDate) {
                int daysOverdue = (now - record.dueDate) / (60*60*24);
                fines += daysOverdue * 10; // 10 rupees per day
            }
            break;
        }
    }
}

void Account::addBorrowedBook(Book* book, int maxDays) {
    borrowedBooks.push_back(book);
    time_t now = time(nullptr);
    BorrowingRecord record;
    record.ISBN = book->getISBN();
    record.borrowDate = now;
    record.dueDate = now + (maxDays * 24 * 60 * 60); // Convert days to seconds
    record.returnDate = 0;  // Initialize returnDate to 0 for unreturned books
    record.returned = false;
    borrowHistory.push_back(record);
}

void Account::displayBorrowingHistory(const Library& lib) const {
    vector<string> headers = {"Title", "ISBN", "Borrow Date", "Due Date", "Return Date", "Status"};
    vector<int> widths = {40, 15, 25, 25, 25, 15};
    
    printTableSeparator(widths);
    printTableRow(headers, widths);
    printTableSeparator(widths);
    
    for(const auto& record : borrowHistory) {
        // Find the book to display its title
        string title = "Unknown Title";
        for(Book* b : lib.getBooks()) {
            if(b->getISBN() == record.ISBN) {
                title = b->getTitle();
                break;
            }
        }
        
        // Format dates
        char borrowDate[26], dueDate[26], returnDate[26];
        strftime(borrowDate, 26, "%Y-%m-%d %H:%M:%S", localtime(&record.borrowDate));
        strftime(dueDate, 26, "%Y-%m-%d %H:%M:%S", localtime(&record.dueDate));
        
        string returnStatus;
        string returnDateStr;
        if(record.returned) {
            strftime(returnDate, 26, "%Y-%m-%d %H:%M:%S", localtime(&record.returnDate));
            returnStatus = "Returned";
            returnDateStr = returnDate;
        } else {
            returnStatus = "Not returned";
            returnDateStr = "Not returned";
        }
        
        vector<string> row = {
            title,
            record.ISBN,
            borrowDate,
            dueDate,
            returnDateStr,
            returnStatus
        };
        
        printTableRow(row, widths);
    }
    printTableSeparator(widths);
    cout << "\n";
} 