# Library Management System

A robust command-line library management system implemented in C++ that handles user authentication, book management, and borrowing operations with role-based access control.

## Features

### User Management
- **Multiple User Roles**
  - Students (can borrow up to 3 books for 15 days)
  - Faculty (can borrow up to 5 books for 30 days)
  - Librarian (manages books and users)
- **Authentication & Authorization**
  - Secure password-based login
  - Role-specific access control
  - Session management
- **Account Management**
  - Fine tracking for overdue books (₹10 per day)
  - Borrowing history
  - Current borrowed books tracking

### Book Management
- **Comprehensive Book Information**
  - Title, Author, Publisher
  - Publication Year
  - ISBN (13-digit validation)
  - Status tracking (Available/Borrowed)
- **Book Operations**
  - Add new books (Librarian)
  - Remove books (Librarian)
  - View all books
  - View available books
  - View borrowed books

### Borrowing System
- **Smart Borrowing Rules**
  - Student: 3 books, 15 days
  - Faculty: 5 books, 30 days
  - Automatic fine calculation
  - Due date tracking
- **Return Processing**
  - Status updates
  - Fine calculation
  - History recording

### Data Persistence
- **CSV-Based Storage**
  - books.csv: Book inventory
  - users.csv: User accounts and history
- **Data Format**
  - Books: Title,Author,Publisher,Year,ISBN,Status
  - Users: UserID,Role,Name,Password,Fines,BORROWED:books,HISTORY:records

## Installation

### Prerequisites
- C++17 compatible compiler
- Terminal/Command Prompt

### Building from Source
1. Compile the program:
   ```bash
   g++ -std=c++17 -I./include src/*.cpp -o bin/library_system
   ```

2. Run the program:
   ```bash
   ./bin/library_system
   ```

## Usage Guide

### Login Credentials

1. **Student Accounts**
   - Format: S### (e.g., S001)
   - Default password: pass123
   - Example: S001/pass123

2. **Faculty Accounts**
   - Format: F### (e.g., F001)
   - Default password: pass123
   - Example: F001/pass123

3. **Librarian Account**
   - ID: L001
   - Password: admin123

### Menu System

#### Student Menu
1. View All Books
2. View Available Books
3. View My Borrowed Books
4. Borrow Book
5. Return Book
6. View Fines
7. Pay Fines
8. View Borrowing History
9. Logout

#### Faculty Menu
1. View All Books
2. View Available Books
3. View My Borrowed Books
4. Borrow Book
5. Return Book
6. View Borrowing History
7. Logout

#### Librarian Menu
1. Add Book
2. Remove Book
3. View All Books
4. View All Users
5. Add User
6. Remove User
7. Logout

### Sample Books
The system comes pre-populated with classic literature:
- Jane Eyre
- The Lord of the Rings
- Wuthering Heights
- The Odyssey
- Don Quixote
- Moby Dick
- The Divine Comedy
- War and Peace
- Les Miserables
- The Count of Monte Cristo

### Project Structure
```
library-management-system/
├── include/
│   ├── Account.h
│   ├── Book.h
│   ├── Library.h
│   ├── User.h
│   └── Utils.h
├── src/
│   ├── Account.cpp
│   ├── Book.cpp
│   ├── Library.cpp
│   ├── User.cpp
│   ├── Utils.cpp
│   └── main.cpp
├── bin/
│   ├── books.csv
│   └── users.csv
└── README.md
```

### Class Hierarchy
- **Library**: Main system controller
- **User**: Base class for all users
  - Student: Limited borrowing privileges
  - Faculty: Extended borrowing privileges
  - Librarian: Administrative privileges
- **Book**: Book information and status
- **Account**: Borrowing records and fines
- **Utils**: Helper functions for UI

### Error Handling
- File I/O error handling
- Invalid input handling
- Data validation errors
- Runtime error handling

## Author
Nikhil Pothuganti