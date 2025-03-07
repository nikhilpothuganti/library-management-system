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
    Book(std::string t = "", std::string a = "", std::string p = "", int y = 0, std::string isbn = "");
    
    // Getters
    std::string getISBN() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    int getYear() const;
    std::string getTitle() const;
    BookStatus getStatus() const;

    // Setters
    void setStatus(BookStatus s);
    void setTitle(std::string t);
    void setAuthor(std::string a);
    void setPublisher(std::string p);
    void setYear(int y);
    void setISBN(std::string i);

    void display() const;
};

#endif // BOOK_H 