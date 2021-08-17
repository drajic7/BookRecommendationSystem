/*
 * Denis Rajic
 * CPSC 5021, Seattle University
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Book.h"
#include "Member.h"
#include "Rating.h"

using namespace std;

void welcome();

void goodbye();

void loadExternalData(Book &bookList, Rating &ratingList, Member &memberList);

int mainMenu();

int userMenu();

bool login(Member &memberList, int accountNumber);

void addNewMember(Member &memberList, Rating &ratingList);

void addNewBook(Book &bookList, Rating &ratingList);

void addNewRating(int accountNumber, Rating &ratingList, Book &bookList);

void viewRatings(int accountNumber, Rating &ratingList, Book &bookList);

void seeRecommendations(int accountNumber, Rating &ratingList, Book
&bookList, Member &memberList);

void writeToFile(Member &memberList, Book &bookList, Rating &ratingList);

/**
 * This program is a book recommendation program. It reads files that contain
 * information on books and their ratings by different users. It lets you add
 * new users and new book ratings. It lets every user see what their
 * recommendations are based on other users' ratings of the same books they
 * read.
 * @return 0 if no errors
 */
int main() {
    // Constants for user menu
    const int NEW_MEMBER = 1;
    const int NEW_BOOK = 2;
    const int LOGIN = 3;
    const int QUIT = 4;
    const int RATE_BOOK = 3;
    const int VIEW_RATINGS = 4;
    const int SEE_RECOMMENDATIONS = 5;
    const int LOGOUT = 6;

    const int INITIAL_BOOK_SIZE = 10;

    // Create book, member, and rating object
    Book bookList;
    Member memberList;
    Rating ratingList(INITIAL_BOOK_SIZE);

    // Give info about program to user
    welcome();

    // Load data on books and users from files
    loadExternalData(bookList, ratingList, memberList);

    int accountNumber;      // to hold current user
    int mainMenuCommand;    // to hold main menu command
    int userMenuCommand;    // to hold user menu command

    // Main menu repeats until user quits
    do {
        mainMenuCommand = mainMenu();
        // User menu
        if (mainMenuCommand == LOGIN) {
            // Prompt user for login info and continue if successful
            cout << "\nEnter member account: ";
            cin >> accountNumber;
            if (login(memberList, accountNumber)) {
                // Print User Menu until user decides to log out
                do {
                    // Promput user for command
                    userMenuCommand = userMenu();
                    if (userMenuCommand == NEW_MEMBER) {
                        // Adds new member
                        addNewMember(memberList, ratingList);
                    } else if (userMenuCommand == NEW_BOOK) {
                        // Adds new book
                        addNewBook(bookList, ratingList);
                    } else if (userMenuCommand == RATE_BOOK) {
                        // Rates book
                        addNewRating(accountNumber, ratingList, bookList);
                    } else if (userMenuCommand == VIEW_RATINGS) {
                        // View user's ratings
                        cout << endl << memberList.findName(accountNumber) <<
                             "'s ratings... " << endl;
                        viewRatings(accountNumber, ratingList, bookList);
                    } else if (userMenuCommand == SEE_RECOMMENDATIONS) {
                        // Shows recommendations
                        seeRecommendations(accountNumber, ratingList,
                                           bookList, memberList);
                    } else if (userMenuCommand < NEW_MEMBER ||
                               userMenuCommand > LOGOUT) {
                        // Validates that user is entering valid command
                        cout << "Error: Invalid command" << endl;
                    }
                } while (userMenuCommand != LOGOUT);
                // Log user out
                memberList.logout(accountNumber - 1);
            }
        } else if (mainMenuCommand == NEW_MEMBER) {
            // Adds new member
            addNewMember(memberList, ratingList);
        } else if (mainMenuCommand == NEW_BOOK) {
            // Adds new book
            addNewBook(bookList, ratingList);
        } else if (mainMenuCommand < NEW_MEMBER || mainMenuCommand > QUIT) {
            // Validates that user is entering valid command
            cout << "Error: Invalid command" << endl;
        }
    } while (mainMenuCommand != QUIT);

    writeToFile(memberList, bookList, ratingList);

    // Goodbye message
    goodbye();

    return 0;
}

/**
 * Prints welcome message to user
 */
void welcome() {
    cout << "Welcome to the Book Recommendation Program!\n"
            "This program will let you create an account, \n"
            "rate books you've read, and will give you \n"
            "recommendations for other books you may like\n"
            "based on other users' ratings.\n\n";
}

/**
 * Prints goodbye message to user
 */
void goodbye() {
    cout << "\n\nThank you for using the Book Recommendation Program!\n";
}

/**
 * Loads data from files into the rating system Member, Book, and Rating objects
 * @param bookList Book object that will be populated with list of all books
 * @param ratingList Rating object that will be populated with list of all
 * users' ratings of different books
 * @param memberList Member object that will be populated with list of all
 * members
 */
void loadExternalData(Book &bookList, Rating &ratingList, Member &memberList) {
    // To hold name of file with book info
    string bookFileName = "books-updated.txt";
    // To hold name of file with rating info
    string ratingFileName = "ratings-updated.txt";

    // Checks to see if updated books and ratings file exist
    ifstream updatedBookFile(bookFileName);
    ifstream updatedRatingFile(ratingFileName);

    // If the files don't exist, prompt user for file names
    if (!updatedBookFile || !updatedRatingFile) {
        updatedBookFile.close();
        updatedRatingFile.close();

        // Prompt user for books file
        cout << "Enter books file: ";
        cin >> bookFileName;

        // Prompt user for rating file
        cout << "Enter rating file: ";
        cin >> ratingFileName;

        // Read file and fill book array with book info from file
        fstream bookFile(bookFileName);
        fstream ratingFile(ratingFileName);


        if (bookFile) {
            string line;    // To hold line
            string author;  // To hold author name
            string title;   // To hold book title
            string year;    // To hold year
            int bookId = 0; // To hold bookID
            // Get line by line from file
            while (getline(bookFile, line)) {
                // Split line by ',' using stringstream and assign to variables
                stringstream ss(line);

                getline(ss, line, ',');
                author = line;

                getline(ss, line, ',');
                title = line;

                getline(ss, line, ',');
                year = line;

                // Add book info to booklist
                bookList.addBook(to_string(bookId + 1), author, title,
                                 year);
                // Increment bookID
                bookId++;
            }
        } else {
            cout << "ERROR: cannot open file.\n";
        }

        // Close book file
        bookFile.close();

        // Read ratings file
        int totalMembers = 0;       // To hold total members
        int totalBooks = 0;         // To hold total books

        if (ratingFile) {
            string name;            // To hold names of members
            string fileRatings;     // To hold ratings

            // Get line from file until end of file is reached
            while (getline(ratingFile, name)) {

                // Accumulates number of books, resets each loop so that it can
                // be used as an index for the 2d array
                totalBooks = 0;

                // Add Member name to array
                memberList.addMember(name);
                getline(ratingFile, fileRatings);

                // Parse the ratings line into integers
                istringstream ss(fileRatings);
                do {
                    int rating;
                    // Add next integer to array until end of line is reached
                    while (ss >> rating) {
                        // Add rating to 2d array
                        ratingList.addRating(totalMembers, totalBooks, rating);
                        totalBooks++;
                    }
                } while (ss);
                totalMembers++;
            }
            cout << endl;
        } else {
            cout << "ERROR: cannot open file.\n";
        }

        // Close file
        ratingFile.close();

        // Print total books and members in files
        cout << "# of books: " << totalBooks << endl;
        cout << "# of members: " << totalMembers << endl;

    }else {
        // If updated files exist, read updated files
        if (updatedBookFile) {
            string line;    // To hold line
            string author;  // To hold author name
            string title;   // To hold book title
            string year;    // To hold year
            int bookId = 0; // To hold bookID
            // Get line by line from file
            while (getline(updatedBookFile, line)) {
                // Split line by ',' using stringstream and assign to variables
                stringstream ss(line);

                getline(ss, line, ',');
                author = line;

                getline(ss, line, ',');
                title = line;

                getline(ss, line, ',');
                year = line;

                // Add book info to booklist
                bookList.addBook(to_string(bookId + 1), author, title,
                                 year);
                // Increment bookID
                bookId++;
            }
        } else {
            cout << "ERROR: cannot open file.\n";
        }

        // Close book file
        updatedBookFile.close();

        // Read ratings file
        int totalMembers = 0;       // To hold total members
        int totalBooks = 0;         // To hold total books

        if (updatedRatingFile) {
            string name;            // To hold names of members
            string fileRatings;     // To hold ratings

            // Get line from file until end of file is reached
            while (getline(updatedRatingFile, name)) {

                // Accumulates number of books, resets each loop so that it can
                // be used as an index for the 2d array
                totalBooks = 0;

                // Add Member name to array
                memberList.addMember(name);
                getline(updatedRatingFile, fileRatings);

                // Parse the ratings line into integers
                istringstream ss(fileRatings);
                do {
                    int rating;
                    // Add next integer to array until end of line is reached
                    while (ss >> rating) {
                        // Add rating to 2d array
                        ratingList.addRating(totalMembers, totalBooks, rating);
                        totalBooks++;
                    }
                } while (ss);
                totalMembers++;
            }
            cout << endl;
        } else {
            cout << "ERROR: cannot open file.\n";
        }

        // Close file
        updatedRatingFile.close();

        // Print total books and members in files
        cout << "# of books: " << totalBooks << endl;
        cout << "# of members: " << totalMembers << endl;
    }

}

/**
 * Prints main menu and prompts user for menu command
 * @return User's command
 */
int mainMenu() {
    int menuChoice;

    cout << "\n************** MENU **************\n"
            "* 1. Add a new member            *\n"
            "* 2. Add a new book              *\n"
            "* 3. Login                       *\n"
            "* 4. Quit                        *\n"
            "**********************************\n\n"
            "Enter a menu option: ";


    cin >> menuChoice;
    return menuChoice;
}

/**
 * Prints user menu once a user has logged in and prompts for command
 * @return User's command
 */
int userMenu() {
    int menuChoice;

    cout << "\n************** MENU **************\n"
            "* 1. Add a new member            *\n"
            "* 2. Add a new book              *\n"
            "* 3. Rate book                   *\n"
            "* 4. View ratings                *\n"
            "* 5. See recommendations         *\n"
            "* 6. Logout                      *\n"
            "**********************************\n\n"
            "Enter a menu option: ";

    cin >> menuChoice;
    return menuChoice;
}

/**
 * Checks to see if user has account and can login into system
 * @param memberList Member object that we check for user account
 * @param accountNumber User's account number
 * @return User's account number if successful, -1 if not.
 */
bool login(Member &memberList, int accountNumber) {
    // Check to see if user account exists
    if (memberList.login(accountNumber)) {
        cout << memberList.findName(accountNumber) << ", you are logged in."
             << endl;
        return true;
    }
    cout << "Login failed." << endl;
    return false;

}

/**
 * Adds new member to member list
 * @param memberList Member object we will add user to
 * @param ratingList Rating object we will add user to
 */
void addNewMember(Member &memberList, Rating &ratingList) {
    string memberName;  // To hold member name
    int memberID;       // To hold memberId
    cout << "Enter the name of the new member: ";
    cin.ignore();   // Clears input buffer
    getline(cin,memberName);

    // Add Member to member list
    memberID = memberList.addMember(memberName);
    // Add Member to rating list
    ratingList.addMember(memberID);

    cout << memberName << " (account #: " << memberID << ") was added." <<
         endl;
}

/**
 * Adds new book to book list
 * @param bookList Book object we will add book to
 * @param ratingList Rating object we will add book to
 */
void addNewBook(Book &bookList, Rating &ratingList) {
    string title;   // To hold title of book
    string author;  // To hold author of book
    string year;    // To hold year of book
    int bookId;     // To hold bookId

    cin.ignore();           // Clears input buffer
    // Prompt user for details on book to be added
    cout << "Enter the author of the new book: ";
    getline(cin, author);
    cout << "Enter the title of the new book: ";
    getline(cin, title);
    cout << "Enter the year (or range of years) of the new book: ";
    getline(cin, year);

    // Add book to book list
    bookId = bookList.addBook(to_string(bookList.size() + 1), author,
                              title, year);
    // Add book to rating list
    ratingList.addBook(bookId);

    bookList.printBook(bookId);
    cout << " was added.\n";
}

/**
 * Adds new rating to list of ratings
 * @param accountNumber User's account number
 * @param ratingList Rating object we will add rating to
 * @param bookList List of books for printing details of books
 */
void addNewRating(int accountNumber, Rating &ratingList, Book &bookList) {
    string isbn;    // To hold book isbn
    // Validate that it is an existing ISBN
    do {
        cout << "Enter the ISBN for the book you'd like to rate: ";
        cin >> isbn;
    } while (stoi(isbn) < 0 || stoi(isbn) > bookList.size());

    // Gets current user's rating of book
    int bookRating = ratingList.getRating(accountNumber - 1, bookList
            .lookupISBN(isbn));

    string rate = "y";

    // Ask user if they would like to rerate previously rated book
    if (bookRating != 0) {
        cout << "Your current rating for ";
        bookList.printBook(bookList.lookupISBN(isbn));
        cout << " =>rating: " << bookRating << endl;
        cout << "Would you like to re-rate this book (y/n)? ";
        cin >> rate;
    }

    // User enters rating, validates that it is an allowed number
    if (rate == "y") {
        do {
            cout << "Enter your rating: ";
            cin >> bookRating;
        } while (bookRating != -5 && bookRating != -3 && bookRating != 0 &&
                 bookRating != 1 && bookRating != 3 && bookRating != 5);
    }

    // Adds rating to rating list object
    ratingList.addRating(accountNumber - 1, bookList.lookupISBN(isbn),
                         bookRating);

    // Confirms new rating to user
    cout << "Your new rating for ";
    bookList.printBook(bookList.lookupISBN(isbn));
    cout << " => rating: " << ratingList.getRating(accountNumber - 1,
                                                   bookList.lookupISBN(isbn))
         << endl;

}

/**
 * Prints user ratings for each book.
 * @param accountNumber User's account number
 * @param ratingList Rating list containing ratings
 * @param bookList Book list containing details of books
 */
void viewRatings(int accountNumber, Rating &ratingList, Book &bookList) {
    // Prints user rating for every book
    for (int i = 0; i < bookList.size(); i++) {
        bookList.printBook(i);
        cout << " => rating: " << ratingList.getRating(accountNumber - 1, i)
             << endl;
    }
}

/**
 * Prints recommendations for user based on user with most similar ratings
 * @param accountNumber User's account number
 * @param ratingList Rating list containing ratings
 * @param bookList Book list containing details of books
 * @param memberList Member list containing member names
 */
void seeRecommendations(int accountNumber, Rating &ratingList, Book
&bookList, Member &memberList) {
    const int LIKED = 3;            // Constant for liked books
    const int REALLY_LIKED = 5;     // Constant for really liked books

    // Find user who has most similar ratings to current user
    int mostSimilar = ratingList.mostSimilar(accountNumber - 1);

    cout << "\nYou have similar taste as " << memberList.findName
            (mostSimilar + 1) << "!\n" << endl;

    // List books that most similar user has really liked that user has not read
    cout << "Here are the books they really liked: " << endl;
    for (int i = 0; i < bookList.size(); i++) {
        int myRating = ratingList.getRating(accountNumber - 1, i);
        int theirRating = ratingList.getRating(mostSimilar, i);
        if (theirRating == REALLY_LIKED && myRating == 0) {
            bookList.printBook(i);
            cout << endl;
        }
    }
    cout << endl;

    // List books that most similar user has liked that user has not read
    cout << "Here are the books they liked: " << endl;
    for (int i = 0; i < bookList.size(); i++) {
        int myRating = ratingList.getRating(accountNumber - 1, i);
        int theirRating = ratingList.getRating(mostSimilar, i);
        if (theirRating == LIKED && myRating == 0) {
            bookList.printBook(i);
            cout << endl;
        }
    }
}

/**
 * Writes updated data to new files
 * @param memberList Member object with data on members
 * @param bookList Book object with data on books
 * @param ratingList Rating object with data on book ratings
 */
void writeToFile(Member &memberList, Book &bookList, Rating &ratingList) {
    // File to write book info to
    ofstream outBookFile("books-updated.txt");

    // Write book data to file
    for(int i = 0; i < bookList.size(); i++) {
        outBookFile << bookList.writeToFile(i);
    }

    // Close book output file
    outBookFile.close();

    // File to write rating data to
    ofstream outRatingFile("ratings-updated.txt");

    // Write rating data to file
    for(int member = 1; member < memberList.size() + 1; member++) {
        // Write member name
        outRatingFile << memberList.findName(member) << endl;
        string line;    // To hold ratings
        // Add all member ratings to line
        for (int rating = 0; rating < bookList.size(); rating++) {
            line += to_string(ratingList.getRating(member - 1, rating)) + " ";
        }
        // Write member ratings to file
        outRatingFile << line << endl;
    }

    // Close rating output file
    outRatingFile.close();
}