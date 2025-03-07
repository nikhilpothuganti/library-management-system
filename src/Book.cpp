#include "../include/Book.h"

using namespace std;

Book::Book(const string& t, const string& a, const string& p, int y, const string& isbn)
    : title(t), author(a), publisher(p), year(y), ISBN(isbn), status(BookStatus::AVAILABLE) {}

const string& Book::getISBN() const { return ISBN; }
const string& Book::getAuthor() const { return author; }
const string& Book::getPublisher() const { return publisher; }
int Book::getYear() const { return year; }
const string& Book::getTitle() const { return title; }
BookStatus Book::getStatus() const { return status; }

void Book::setStatus(BookStatus s) { status = s; }
void Book::setTitle(const string& t) { title = t; }
void Book::setAuthor(const string& a) { author = a; }
void Book::setPublisher(const string& p) { publisher = p; }
void Book::setYear(int y) { year = y; }
void Book::setISBN(const string& i) { ISBN = i; }

void Book::display() const {
    vector<string> headers = {"Field", "Value"};
    vector<int> widths = {10, 40};
    
    printTableSeparator(widths);
    printTableRow(headers, widths);
    printTableSeparator(widths);
    
    printTableRow({"Title", title}, widths);
    printTableRow({"Author", author}, widths);
    printTableRow({"Publisher", publisher}, widths);
    printTableRow({"Year", to_string(year)}, widths);
    printTableRow({"ISBN", ISBN}, widths);
    string statusStr = (status == BookStatus::AVAILABLE ? "Available" : 
                     (status == BookStatus::BORROWED ? "Borrowed" : "Reserved"));
    printTableRow({"Status", statusStr}, widths);
    
    printTableSeparator(widths);
    cout << "\n";
} 