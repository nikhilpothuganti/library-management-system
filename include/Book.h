#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Utils.h"

enum class BookStatus { AVAILABLE, BORROWED, RESERVED };

class Book {
private:
    std::string title;
    std::string author;
    std::string publisher;
    int year;
    std::string ISBN;
    BookStatus status;

public:
    Book(const std::string& t = "", const std::string& a = "", const std::string& p = "", 
         int y = 0, const std::string& isbn = "");
    
    // Getters
    const std::string& getISBN() const;
    const std::string& getAuthor() const;
    const std::string& getPublisher() const;
    int getYear() const;
    const std::string& getTitle() const;
    BookStatus getStatus() const;

    // Setters
    void setStatus(BookStatus s);
    void setTitle(const std::string& t);
    void setAuthor(const std::string& a);
    void setPublisher(const std::string& p);
    void setYear(int y);
    void setISBN(const std::string& i);

    void display() const;
};

#endif // BOOK_H 