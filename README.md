# Library Management System

A command-line library management system that handles user authentication, book management, and borrowing operations.

## Features

- User Management
  - Multiple user roles (Admin, Librarian, Member)
  - User authentication and authorization
  - Fine tracking for overdue books
  - User history tracking

- Book Management
  - Add, remove, and update books
  - Search books by title, author, or ISBN
  - Track book status (Available, Borrowed, Reserved)
  - Book details including title, author, publisher, year, and ISBN

- Borrowing System
  - Borrow and return books
  - Automatic due date calculation
  - Fine calculation for overdue books
  - Book reservation system

- Data Persistence
  - CSV-based storage for books and users
  - Automatic data saving
  - Data validation and error handling

## Prerequisites

- C++17 compatible compiler (g++ recommended)
- Standard C++ Library

## Project Structure

```
library-management-system/
├── include/             # Header files
├── src/                # Source files
├── bin/                # Data files
│   ├── books.csv      # Pre-populated with 10+ books
│   └── users.csv      # Pre-populated with initial users
└── README.md          # This file
```

## Initial Data

The system comes pre-populated with:

### Users
- 1 Administrator
- 1 Librarian
- 5 Students
- 3 Faculty members

### Books
- 10+ books across various genres
- Each book includes complete details (title, author, publisher, year, ISBN)

## Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/library-management-system.git
   cd library-management-system
   ```

2. Compile the program:
   ```bash
   g++ -std=c++17 -Wall -I./include src/*.cpp -o bin/library_system
   ```

3. Run the program:
   ```bash
   ./bin/library_system
   ```

## Usage

### Sample Login Credentials

1. Admin:
   - Username: admin
   - Password: admin123

2. Librarian:
   - Username: librarian
   - Password: lib123

3. Member:
   - Username: member
   - Password: member123

### User Interface

The system provides different menus based on user roles:

1. Admin Menu:
   - Manage users (add, remove, update)
   - View all users
   - Manage books
   - View all books
   - View borrowing history
   - Logout

2. Librarian Menu:
   - Manage books (add, remove, update)
   - View all books
   - View available books
   - View borrowed books
   - View borrowing history
   - Logout

3. Member Menu:
   - View all books
   - View available books
   - View borrowed books
   - Borrow a book
   - Return a book
   - View borrowing history
   - Logout

## Data Storage

The system uses CSV files for data storage in the bin directory:

1. `bin/books.csv`:
   ```
   Title,Author,Publisher,Year,ISBN,Status
   ```
   - Status: 0 (Available), 1 (Borrowed), 2 (Reserved)
   - Pre-populated with 10+ books

2. `bin/users.csv`:
   ```
   UserID,Role,Name,Password,Fines,BORROWED:ISBN1;ISBN2...,HISTORY:ISBN;BorrowDate;DueDate;ReturnDate;Returned;...
   ```
   - Pre-populated with initial users (1 Librarian, 5 Students, 3 Faculty)

## Error Handling

The system includes comprehensive error handling for:
- Invalid user credentials
- Book availability issues
- Fine calculation
- Data validation
- File operations

## Author

Nikhil Pothuganti