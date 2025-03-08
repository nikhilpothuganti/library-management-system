#include "../include/User.h"
#include "../include/Library.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Base User class implementation
User::User(string id, string pwd, string n)
    : userId(id), password(pwd), name(n) {
    account.setUserId(id);
}

User::~User() {}

string User::getUserId() const { return userId; }
string User::getName() const { return name; }
string User::getPassword() const { return password; }
Account& User::getAccount() { return account; }
bool User::checkPassword(string pwd) const { return password == pwd; }

// Student class implementation
Student::Student(string id, string pwd, string n) : User(id, pwd, n) {}

bool Student::canBorrow() const { return true; }
int Student::getMaxBooks() const { return 3; }
int Student::getMaxDays() const { return 15; }
bool Student::incursFines() const { return true; }

// Faculty class implementation
Faculty::Faculty(string id, string pwd, string n) : User(id, pwd, n) {}

bool Faculty::canBorrow() const { return true; }
int Faculty::getMaxBooks() const { return 5; }
int Faculty::getMaxDays() const { return 30; }
bool Faculty::incursFines() const { return false; }

// Librarian class implementation
Librarian::Librarian(string id, string pwd, string n) : User(id, pwd, n) {}

bool Librarian::canBorrow() const { return false; }
int Librarian::getMaxBooks() const { return 0; }
int Librarian::getMaxDays() const { return 0; }
bool Librarian::incursFines() const { return false; }

// Menu implementations for each user type
void Student::displayMenu(Library& lib) {
    while(true) {
        cout << "\nStudent Menu - " << name << "\n"
             << "1. View All Books\n"
             << "2. View Available Books\n"
             << "3. View My Borrowed Books\n"
             << "4. Borrow Book\n"
             << "5. Return Book\n"
             << "6. View Fines\n"
             << "7. Pay Fines\n"
             << "8. View Borrowing History\n"
             << "9. Logout\n"
             << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: {
                cout << "\nAll Books:\n";
                vector<string> headers = {"Title", "Author", "ISBN", "Status"};
                vector<int> widths = {35, 25, 15, 10};
                
                printTableSeparator(widths);
                printTableRow(headers, widths);
                printTableSeparator(widths);
                
                for(Book* book : lib.getBooks()) {
                    string statusStr = (book->getStatus() == BookStatus::AVAILABLE ? "Available" : 
                                    (book->getStatus() == BookStatus::BORROWED ? "Borrowed" : "Reserved"));
                    vector<string> row = {
                        book->getTitle(),
                        book->getAuthor(),
                        book->getISBN(),
                        statusStr
                    };
                    printTableRow(row, widths);
                }
                printTableSeparator(widths);
                cout << "\n";
                break;
            }
            case 2: {
                cout << "\nAvailable Books:\n";
                vector<string> headers = {"Title", "Author", "ISBN", "Publisher"};
                vector<int> widths = {35, 25, 15, 30};
                
                printTableSeparator(widths);
                printTableRow(headers, widths);
                printTableSeparator(widths);
                
                for(Book* book : lib.getBooks()) {
                    if(book->getStatus() == BookStatus::AVAILABLE) {
                        vector<string> row = {
                            book->getTitle(),
                            book->getAuthor(),
                            book->getISBN(),
                            book->getPublisher()
                        };
                        printTableRow(row, widths);
                    }
                }
                printTableSeparator(widths);
                cout << "\n";
                break;
            }
            case 3: {
                cout << "\nBorrowed Books:\n";
                vector<string> headers = {"Title", "Author", "ISBN", "Due Date"};
                vector<int> widths = {35, 25, 15, 25};
                
                printTableSeparator(widths);
                printTableRow(headers, widths);
                printTableSeparator(widths);
                
                for(const auto& record : account.getBorrowHistory()) {
                    if(!record.returned) {
                        for(Book* book : lib.getBooks()) {
                            if(book->getISBN() == record.ISBN) {
                                char dueDate[26];
                                strftime(dueDate, 26, "%Y-%m-%d %H:%M:%S", localtime(&record.dueDate));
                                
                                vector<string> row = {
                                    book->getTitle(),
                                    book->getAuthor(),
                                    book->getISBN(),
                                    dueDate
                                };
                                printTableRow(row, widths);
                                break;
                            }
                        }
                    }
                }
                printTableSeparator(widths);
                cout << "\n";
                break;
            }
            case 4: {
                if(account.getBorrowedBooks().size() >= getMaxBooks()) {
                    cout << "You have reached your borrowing limit.\n";
                    break;
                }
                if(account.getFines() > 0) {
                    cout << "Please clear your fines before borrowing.\n";
                    break;
                }
                cout << "\nAvailable Books:\n";
                for(Book* book : lib.getBooks()) {
                    if(book->getStatus() == BookStatus::AVAILABLE) {
                        book->display();
                    }
                }
                cout << "Enter ISBN of book to borrow: ";
                string isbn;
                getline(cin, isbn);

                bool found = false;
                for(Book* book : lib.getBooks()) {
                    if(book->getISBN() == isbn) {
                        found = true;
                        if(book->getStatus() == BookStatus::AVAILABLE) {
                            book->setStatus(BookStatus::BORROWED);
                            account.addBorrowedBook(book, getMaxDays());
                            lib.saveData();  // Save changes to files
                            cout << "Book borrowed successfully.\n";
                        } else {
                            cout << "This book is currently borrowed by someone else.\n";
                        }
                        break;
                    }
                }
                if(!found) {
                    cout << "Book with ISBN " << isbn << " not found.\n";
                }
                break;
            }
            case 5: {
                cout << "\nYour Borrowed Books:\n";
                for(Book* book : account.getBorrowedBooks()) {
                    book->display();
                }
                
                cout << "Enter ISBN of book to return: ";
                string isbn;
                getline(cin, isbn);

                bool found = false;
                for(Book* book : account.getBorrowedBooks()) {
                    if(book->getISBN() == isbn) {
                        book->setStatus(BookStatus::AVAILABLE);
                        account.removeBorrowedBook(book);
                        lib.saveData();  // Save changes to files
                        cout << "Book returned successfully.\n";
                        if(account.getFines() > 0) {
                            cout << "You have incurred fines of Rs. " << account.getFines() << " due to late return.\n";
                        }
                        found = true;
                        break;
                    }
                }
                if(!found) {
                    cout << "You have not borrowed this book.\n";
                }
                break;
            }
            case 6: {
                cout << "Current fines: Rs. " << account.getFines() << "\n";
                break;
            }
            case 7: {
                cout << "Pay fine amount of Rs. " << account.getFines() << "? (y/n): ";
                char confirm;
                cin >> confirm;
                if(confirm == 'y' || confirm == 'Y') {
                    account.clearFines();
                    lib.saveData();  // Save changes after clearing fines
                    cout << "Fines cleared.\n";
                }
                break;
            }
            case 8: {
                cout << "\nBorrowing History:\n";
                account.displayBorrowingHistory(lib);
                break;
            }
            case 9: {
                lib.logout();
                return;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Faculty::displayMenu(Library& lib) {
    while(true) {
        cout << "\nFaculty Menu - " << name << "\n"
            << "1. View All Books\n"
            << "2. View Available Books\n"
            << "3. View My Borrowed Books\n"
            << "4. Borrow Book\n"
            << "5. Return Book\n"
            << "6. View Borrowing History\n"
            << "7. Logout\n"
            << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: {
                cout << "\nAll Books:\n";
                vector<string> headers = {"Title", "Author", "ISBN", "Status"};
                vector<int> widths = {35, 25, 15, 10};
                
                printTableSeparator(widths);
                printTableRow(headers, widths);
                printTableSeparator(widths);
                
                for(Book* book : lib.getBooks()) {
                    string statusStr = (book->getStatus() == BookStatus::AVAILABLE ? "Available" : 
                                    (book->getStatus() == BookStatus::BORROWED ? "Borrowed" : "Reserved"));
                    vector<string> row = {
                        book->getTitle(),
                        book->getAuthor(),
                        book->getISBN(),
                        statusStr
                    };
                    printTableRow(row, widths);
                }
                printTableSeparator(widths);
                cout << "\n";
                break;
            }
            case 2: {
                cout << "\nAvailable Books:\n";
                vector<string> headers = {"Title", "Author", "ISBN", "Publisher"};
                vector<int> widths = {35, 25, 15, 30};
                
                printTableSeparator(widths);
                printTableRow(headers, widths);
                printTableSeparator(widths);
                
                for(Book* book : lib.getBooks()) {
                    if(book->getStatus() == BookStatus::AVAILABLE) {
                        vector<string> row = {
                            book->getTitle(),
                            book->getAuthor(),
                            book->getISBN(),
                            book->getPublisher()
                        };
                        printTableRow(row, widths);
                    }
                }
                printTableSeparator(widths);
                cout << "\n";
                break;
            }
            case 3: {
                cout << "\nBorrowed Books:\n";
                vector<string> headers = {"Title", "Author", "ISBN", "Due Date"};
                vector<int> widths = {35, 25, 15, 25};
                
                printTableSeparator(widths);
                printTableRow(headers, widths);
                printTableSeparator(widths);
                
                for(const auto& record : account.getBorrowHistory()) {
                    if(!record.returned) {
                        for(Book* book : lib.getBooks()) {
                            if(book->getISBN() == record.ISBN) {
                                char dueDate[26];
                                strftime(dueDate, 26, "%Y-%m-%d %H:%M:%S", localtime(&record.dueDate));
                                
                                vector<string> row = {
                                    book->getTitle(),
                                    book->getAuthor(),
                                    book->getISBN(),
                                    dueDate
                                };
                                printTableRow(row, widths);
                                break;
                            }
                        }
                    }
                }
                printTableSeparator(widths);
                cout << "\n";
                break;
            }
            case 4: {
                if(account.getBorrowedBooks().size() >= getMaxBooks()) {
                    cout << "You have reached your borrowing limit.\n";
                    break;
                }

                cout << "\nAvailable Books:\n";
                for(Book* book : lib.getBooks()) {
                    if(book->getStatus() == BookStatus::AVAILABLE) {
                        book->display();
                    }
                }
                cout << "Enter ISBN of book to borrow: ";
                string isbn;
                getline(cin, isbn);

                bool found = false;
                for(Book* book : lib.getBooks()) {
                    if(book->getISBN() == isbn) {
                        found = true;
                        if(book->getStatus() == BookStatus::AVAILABLE) {
                            book->setStatus(BookStatus::BORROWED);
                            account.addBorrowedBook(book, getMaxDays());
                            lib.saveData();  // Save changes to files
                            cout << "Book borrowed successfully.\n";
                        } else {
                            cout << "This book is currently borrowed by someone else.\n";
                        }
                        break;
                    }
                }
                if(!found) {
                    cout << "Book with ISBN " << isbn << " not found.\n";
                }
                break;
            }
            case 5: {
                cout << "\nYour Borrowed Books:\n";
                for(Book* book : account.getBorrowedBooks()) {
                    book->display();
                }
                
                cout << "Enter ISBN of book to return: ";
                string isbn;
                getline(cin, isbn);

                bool found = false;
                for(Book* book : account.getBorrowedBooks()) {
                    if(book->getISBN() == isbn) {
                        book->setStatus(BookStatus::AVAILABLE);
                        account.removeBorrowedBook(book);
                        lib.saveData();  // Save changes to files
                        cout << "Book returned successfully.\n";
                        found = true;
                        break;
                    }
                }
                if(!found) {
                    cout << "You have not borrowed this book.\n";
                }
                break;
            }
            case 6: {
                cout << "\nBorrowing History:\n";
                account.displayBorrowingHistory(lib);
                break;
            }
            case 7: {
                lib.logout();
                return;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Add these validation functions before the Librarian::displayMenu implementation
bool isValidUserId(const string& id, const vector<User*>& users) {
    // Check format
    if(id[0] != 'S' && id[0] != 'F') return false;
    
    // Check if ID already exists
    for(const User* user : users) {
        if(user->getUserId() == id) return false;
    }
    
    return true;
}

bool isValidISBN13(const string& isbn, const vector<Book*>& books) {
    // Check length
    if(isbn.length() != 13) return false;
    
    // Check if all characters are digits
    for(char c : isbn) {
        if(!isdigit(c)) return false;
    }
    
    // Check if ISBN already exists
    for(const Book* book : books) {
        if(book->getISBN() == isbn) return false;
    }
    
}

void Librarian::displayMenu(Library& lib) {
    while(true) {
        cout << "\nLibrarian Menu - " << name << "\n"
             << "1. Add Book\n"
             << "2. Remove Book\n"
             << "3. View All Books\n"
             << "4. View All Users\n"
             << "5. Add User\n"
             << "6. Remove User\n"
             << "7. Logout\n"
             << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: {
                string title, author, publisher, isbn;
                int year;

                cout << "Enter book details:\n";
                cout << "Title: "; getline(cin, title);
                cout << "Author: "; getline(cin, author);
                cout << "Publisher: "; getline(cin, publisher);
                cout << "Year: "; cin >> year;
                cin.ignore();
                
                do {
                    cout << "ISBN (13 digits): "; getline(cin, isbn);
                    if(!isValidISBN13(isbn, lib.getBooks())) {
                        cout << "Invalid ISBN. Please ensure:\n";
                        cout << "- ISBN is exactly 13 digits\n";
                        cout << "- ISBN is not already in the system\n";
                    }
                } while(!isValidISBN13(isbn, lib.getBooks()));

                lib.getBooks().push_back(new Book(title, author, publisher, year, isbn));
                cout << "Book added successfully.\n";
                break;
            }
            case 2: {
                cout << "Enter ISBN of book to remove: ";
                string isbn;
                getline(cin, isbn);

                auto& books = lib.getBooks();
                for(auto it = books.begin(); it != books.end(); ++it) {
                    if((*it)->getISBN() == isbn) {
                        delete *it;
                        books.erase(it);
                        cout << "Book removed successfully.\n";
                        break;
                    }
                }
                break;
            }
            case 3: {
                cout << "\nAll Books:\n";
                vector<string> headers = {"Title", "Author", "ISBN", "Status"};
                vector<int> widths = {35, 25, 15, 10};
                
                printTableSeparator(widths);
                printTableRow(headers, widths);
                printTableSeparator(widths);
                
                for(Book* book : lib.getBooks()) {
                    string statusStr = (book->getStatus() == BookStatus::AVAILABLE ? "Available" : 
                                    (book->getStatus() == BookStatus::BORROWED ? "Borrowed" : "Reserved"));
                    vector<string> row = {
                        book->getTitle(),
                        book->getAuthor(),
                        book->getISBN(),
                        statusStr
                    };
                    printTableRow(row, widths);
                }
                printTableSeparator(widths);
                cout << "\n";
                break;
            }
            case 4: {
                cout << "\nAll Users:\n";
                vector<string> headers = {"User ID", "Name", "Type"};
                vector<int> widths = {15, 30, 10};
                
                printTableSeparator(widths);
                printTableRow(headers, widths);
                printTableSeparator(widths);
                
                for(User* user : lib.getUsers()) {
                    string userType;
                    if(dynamic_cast<Student*>(user)) userType = "Student";
                    else if(dynamic_cast<Faculty*>(user)) userType = "Faculty";
                    else userType = "Librarian";
                    
                    vector<string> row = {
                        user->getUserId(),
                        user->getName(),
                        userType
                    };
                    printTableRow(row, widths);
                }
                printTableSeparator(widths);
                cout << "\n";
                break;
            }
            case 5: {
                string id, password, name;
                cout << "Enter user details:\n";
                
                do {
                    cout << "ID (S### for Student, F### for Faculty): "; 
                    getline(cin, id);
                    if(!isValidUserId(id, lib.getUsers())) {
                        cout << "Invalid user ID. Please ensure:\n";
                        cout << "- ID starts with 'S' for Student or 'F' for Faculty\n";
                        cout << "- ID is not already in use\n";
                    }
                } while(!isValidUserId(id, lib.getUsers()));
                
                cout << "Password: "; getline(cin, password);
                cout << "Name: "; getline(cin, name);

                if(id[0] == 'S') {
                    lib.getUsers().push_back(new Student(id, password, name));
                } else if(id[0] == 'F') {
                    lib.getUsers().push_back(new Faculty(id, password, name));
                }
                cout << "User added successfully.\n";
                break;
            }
            case 6: {
                cout << "Enter user ID to remove: ";
                string id;
                getline(cin, id);

                auto& users = lib.getUsers();
                for(auto it = users.begin(); it != users.end(); ++it) {
                    if((*it)->getUserId() == id) {
                        delete *it;
                        users.erase(it);
                        cout << "User removed successfully.\n";
                        break;
                    }
                }
                break;
            }
            case 7:
                lib.logout();
                return;
            default:
                cout << "Invalid choice\n";
        }
    }
} 