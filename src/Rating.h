//
// Created by Denis on 10/2/2020.
//

#ifndef DRAJIC_P2_RATING_H
#define DRAJIC_P2_RATING_H


/**
 * A Rating object holds the ratings for all the books for all the members
 * indexed by memberId and bookId.
 */
class Rating {
public:
    /**
     * Constructor
     */
    Rating(int initialBookCapacity);

    /**
     * Copy Constructor
     * @param other Rating to copy
     */
    Rating(const Rating &other);

    /**
     * Assignment operator
     * @param rhs Book to copy
     * @return Myself
     */
    Rating &operator=(const Rating &rhs);

    /**
     * Destructor
     */
    ~Rating();

    /**
     * Adds a new rating to the list.
     * @param accountId Account that rated the book
     * @param bookId Book that is being rated
     * @param rating Rating number
     */
    void addRating(int accountId, int bookId, int rating);

    /**
     * Gets a rating for a specific book from a user
     * @param accountId Which user's account
     * @param bookId Which book
     * @return Book rating
     */
    int getRating(int accountId, int bookId);

    /**
     * Compares a user's list of book ratings to every other user and returns
     * the user with the most similar ratings to them.
     * @param accountId User that wants to know who has similar ratings
     * @return User with most similar ratings
     */
    int mostSimilar(int accountId);

    /**
     * Adds new member to ratings list
     * @param memberId New member to be added
     */
    void addMember(int memberId);

    /**
     * Adds new book to ratings list
     * @param bookId Book to be added
     */
    void addBook(int bookId);


private:
    const static int INITIAL_MEMBER_CAPACITY = 20;
    const static int RATE_ZERO = 0;
    int **ratingArray;  // 2D array to store ratings
    int memberCapacity; // Current member capacity of ratings array
    int bookCapacity;   // Current book capacity of ratings array

    void resizeCol(int newCount);

    void resizeRow(int newCount);

    void clear();
};


#endif //DRAJIC_P2_RATING_H
