//
// Created by Denis on 10/2/2020.
//

#include "Book.h"

using namespace std;

Book::Book() {
    capacity = INITIAL_CAPACITY;
    bookArray = new BookInfo[capacity];
    count = 0;
}

Book::Book(const Book &other) {
    capacity = other.capacity;
    bookArray = new BookInfo[capacity];
    count = other.count;
    for (int i = 0; i < count; i++) {
        bookArray[i] = other.bookArray[i];
    }
}

Book &Book::operator=(const Book &rhs) {
    if (&rhs != this) { //check to see if pointing to same object
        delete[] bookArray;
        capacity = rhs.capacity;
        bookArray = new BookInfo[capacity];
        count = rhs.count;
        for (int i = 0; i < count; i++) {
            bookArray[i] = rhs.bookArray[i];
        }
    }

    return *this;
}

Book::~Book() {
    delete[] bookArray; //delete all elements in array
}

int Book::addBook(std::string isbn, std::string author, std::string title,
                  std::string year) {

    // Check to see if array is full and resize if so
    if (count == capacity) {
        resize();
    }

    bookArray[count].isbn = isbn;
    bookArray[count].author = author;
    bookArray[count].title = title;
    bookArray[count].year = year;

    count++;

    return lookupISBN(isbn);
}

int Book::lookupISBN(std::string isbn) const {
    for (int i = 0; i < count; i++) {
        if (bookArray[i].isbn == isbn) {
            return i;
        }
    }
    return NOT_FOUND;
}

void Book::printBook(int bookId) const {
    cout << bookId + 1 << ", " << bookArray[bookId].author << ", " <<
         bookArray[bookId].title << ", " << bookArray[bookId].year;
}

int Book::size() const {
    return count;
}

void Book::resize() {
    // Double capacity of array
    capacity *= 2;

    // Create a new dynamic array with double original capacity
    BookInfo *newList = new BookInfo[capacity];

    // Copy contents of original array to new array
    for (int i = 0; i < count; i++) {
        newList[i] = bookArray[i];
    }

    delete[] bookArray;  // Delete contents at address of pointer
    bookArray = newList; // Assigns pointer to newList
}

std::string Book::writeToFile(int bookId) {
    return bookArray[bookId].author + "," + bookArray[bookId].title + "," +
    bookArray[bookId].year + "\n";
}
