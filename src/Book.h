//
// Created by Denis on 10/2/2020.
//

#ifndef DRAJIC_P2_BOOK_H
#define DRAJIC_P2_BOOK_H

#include <string>
#include <iostream>

/**
 * The Book object holds a list of books.
 * Individual books are referred to by their id which is returned by the add
 * method.
 */
class Book {
public:
    static const int NOT_FOUND = -1;

    /**
     * Constructor
     */
    Book();

    /**
     * Copy constructor
     * @param other  Book to copy
     */
    Book(const Book &other);

    /**
     * Assignment operator
     * @param rhs Book to copy
     * @return myself
     */
    Book &operator=(const Book &rhs);

    /**
     * Destructor
     */
    ~Book();

    /**
     * Add a book to the list.
     * @param isbn   of book
     * @param author of book
     * @param title  of book
     * @param year   of book
     * @return Book Id (useful for calling printBook, for example)
     */
    int addBook(std::string isbn, std::string author, std::string title,
                std::string year);

    /**
     * Lookup up a book by its ISBN.
     * @param isbn of book to lookup
     * @return bookId of given book or NOT_FOUND
     */
    int lookupISBN(std::string isbn) const;

    /**
     * Print to std::cout the details for the given book.
     * @param bookId  as returned by the add method
     */
    void printBook(int bookId) const;

    /**
     * How many books have been added?
     * @return the number of books in the list
     */
    int size() const;

    /**
     * Returns a string for writing book info to file.
     * @return String for writing to file
     */
    std::string writeToFile(int bookId);

private:
    static const int INITIAL_CAPACITY = 113;
    struct BookInfo {
        std::string isbn;
        std::string author;
        std::string title;
        std::string year;
    };
    BookInfo *bookArray;
    int count;
    int capacity;

    /**
     * Automatically enlarge if we get more than INITIAL_CAPACITY books in
     * the list.
     */
    void resize();
};


#endif //DRAJIC_P2_BOOK_H
