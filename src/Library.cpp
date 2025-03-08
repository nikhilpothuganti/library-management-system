#include "../include/Library.h"
#include "../include/User.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

using namespace std;

Library::Library() : currentUser(nullptr) {
    // Load data from CSV files
    loadBooksFromCSV();
    loadUsersFromCSV();
}

Library::~Library() {
    for(Book* book : books) delete book;
    for(User* user : users) delete user;
}

void Library::loadBooksFromCSV() {
    ifstream file("bin/books.csv");
    if(file.is_open()) {
        string line;
        while(getline(file, line)) {
            stringstream ss(line);
            string title, author, publisher, isbn;
            int year, status;
            
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, publisher, ',');
            ss >> year;
            ss.ignore();
            getline(ss, isbn, ',');
            ss >> status;
            
            Book* book = new Book(title, author, publisher, year, isbn);
            book->setStatus(static_cast<BookStatus>(status));
            books.push_back(book);
        }
    }
}

void Library::loadUsersFromCSV() {
    ifstream file("bin/users.csv");
    if(file.is_open()) {
        string line;
        int lineNumber = 0;
        while(getline(file, line)) {
            lineNumber++;
            try {
                stringstream ss(line);
                string userId, role, name, password, fines;
                
                getline(ss, userId, ',');
                getline(ss, role, ',');
                getline(ss, name, ',');
                getline(ss, password, ',');
                getline(ss, fines, ',');  // Read fines
                
                User* user = nullptr;
                if(role == "S") user = new Student(userId, password, name);
                else if(role == "F") user = new Faculty(userId, password, name);
                else if(role == "L") user = new Librarian(userId, password, name);
                
                if(user) {
                    // Set fines if any
                    if(!fines.empty()) {
                        user->getAccount().addFine(stod(fines));
                    }
                    
                    // Load currently borrowed books
                    string borrowedSection;
                    getline(ss, borrowedSection, ',');
                    if(borrowedSection.substr(0, 9) == "BORROWED:") {
                        stringstream borrowedSS(borrowedSection.substr(9));
                        string isbn;
                        while(getline(borrowedSS, isbn, ';')) {
                            if(isbn.empty()) continue;
                            for(Book* book : books) {
                                if(book->getISBN() == isbn) {
                                    book->setStatus(BookStatus::BORROWED);
                                    user->getAccount().getBorrowedBooks().push_back(book);
                                    break;
                                }
                            }
                        }
                    }
                    
                    // Load borrow history
                    string historySection;
                    getline(ss, historySection);
                    if(historySection.substr(0, 8) == "HISTORY:") {
                        string historyData = historySection.substr(8);
                        stringstream historySS(historyData);
                        string entry;
                        
                        while(historySS.good()) {
                            BorrowingRecord record;
                            
                            // Read ISBN
                            if(!getline(historySS, entry, ';') || entry.empty()) break;
                            record.ISBN = entry;
                            
                            // Read borrow date
                            if(!getline(historySS, entry, ';')) break;
                            record.borrowDate = stoll(entry);
                            
                            // Read due date
                            if(!getline(historySS, entry, ';')) break;
                            record.dueDate = stoll(entry);
                            
                            // Read return date
                            if(!getline(historySS, entry, ';')) break;
                            record.returnDate = stoll(entry);
                            
                            // Read returned status
                            if(!getline(historySS, entry, ';')) break;
                            record.returned = (entry == "1");
                            
                            user->getAccount().getBorrowHistory().push_back(record);
                        }
                    }
                    
                    users.push_back(user);
                }
            } catch (const exception& e) {
                cerr << "Error parsing line " << lineNumber << ": " << e.what() << endl;
                continue;
            }
        }
        file.close();
    }
}

void Library::saveBooks() {
    ofstream file("bin/books.csv");
    for(Book* book : books) {
        file << book->getTitle() << ","
             << book->getAuthor() << ","
             << book->getPublisher() << ","
             << book->getYear() << ","
             << book->getISBN() << ","
             << static_cast<int>(book->getStatus()) << "\n";
    }
}

void Library::saveUsers() {
    ofstream file("bin/users.csv");
    if(!file.is_open()) {
        throw runtime_error("Failed to open users.csv for writing");
    }
    for(User* user : users) {
        // Write user data
        file << user->getUserId() << ","
             << (dynamic_cast<Student*>(user) ? "S" : 
                 dynamic_cast<Faculty*>(user) ? "F" : "L") << ","
             << user->getName() << ","
             << user->getPassword() << ","
             << user->getAccount().getFines() << ",";
        
        // Save currently borrowed books
        file << "BORROWED:";
        for(Book* book : user->getAccount().getBorrowedBooks()) {
            file << book->getISBN() << ";";
        }
        file << ",";
        
        // Save complete borrow history
        file << "HISTORY:";
        for(const auto& record : user->getAccount().getBorrowHistory()) {
            file << record.ISBN << ";" 
                 << to_string(record.borrowDate) << ";"
                 << to_string(record.dueDate) << ";"
                 << (record.returned ? to_string(record.returnDate) : "0") << ";"
                 << (record.returned ? "1" : "0") << ";";
        }
        file << "\n";
    }
    file.close();
}

bool Library::login(const string& userId, const string& password) {
    for(User* user : users) {
        if(user->getUserId() == userId && user->checkPassword(password)) {
            currentUser = user;
            return true;
        }
    }
    return false;
}

void Library::logout() {
    currentUser = nullptr;
}

void Library::saveData() {
    saveBooks();
    saveUsers();
}

const vector<Book*>& Library::getBooks() const { return books; }
vector<Book*>& Library::getBooks() { return books; }
const vector<User*>& Library::getUsers() const { return users; }
vector<User*>& Library::getUsers() { return users; }
User* Library::getCurrentUser() const { return currentUser; }

void Library::displayBorrowingHistory(const Library& lib) const {
    if (currentUser) {
        currentUser->getAccount().displayBorrowingHistory(lib);
    }
}

void Library::mainMenu() {
    while(true) {
        if(!currentUser) {
            cout << "\nLibrary System\n"
                 << "1. Login\n"
                 << "2. Exit\n"
                 << "Choice: ";
                 
            int choice;
            cin >> choice;
            cin.ignore();
            
            if(choice == 1) {
                string userId, password;
                cout << "User ID: "; getline(cin, userId);
                cout << "Password: "; getline(cin, password);
                
                if(!login(userId, password)) {
                    cout << "Login failed\n";
                }
            } else if(choice == 2) {
                saveData();
                cout << "Goodbye!\n";
                return;
            } else {
                cout << "Invalid choice. Please try again.\n";
            }
        } else {
            currentUser->displayMenu(*this);
        }
    }
} 