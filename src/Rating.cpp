//
// Created by Denis on 10/2/2020.
//

#include <iostream>
#include "Rating.h"

Rating::Rating(int initialBookCapacity) {
    memberCapacity = INITIAL_MEMBER_CAPACITY;
    bookCapacity = initialBookCapacity;

    //allocate rows
    ratingArray = new int *[memberCapacity];

    //allocate cols
    for (int i = 0; i < memberCapacity; i++) {
        ratingArray[i] = new int[bookCapacity];
    }

    //initialize all values in ratingArray to zero
    for (int row = 0; row < memberCapacity; row++) {
        for (int col = 0; col < bookCapacity; col++) {
            ratingArray[row][col] = RATE_ZERO;
        }
    }
}

Rating::Rating(const Rating &other) {
    memberCapacity = other.memberCapacity;
    bookCapacity = other.memberCapacity;
    ratingArray = new int*[memberCapacity];
    for (int i = 0; i < memberCapacity; i++) {
        ratingArray[i] = new int[bookCapacity];
    }
    for (int i = 0; i < memberCapacity; i++) {
        for (int j = 0; j < bookCapacity; j++) {
            ratingArray[i][j] = other.ratingArray[i][j];
        }
    }
}

Rating &Rating::operator=(const Rating &rhs) {
    if (this != &rhs) {
        clear();
        memberCapacity = rhs.memberCapacity;
        bookCapacity = rhs.memberCapacity;
        ratingArray = new int*[memberCapacity];
        for (int i = 0; i < memberCapacity; i++) {
            ratingArray[i] = new int[bookCapacity];
        }
        for (int i = 0; i < memberCapacity; i++) {
            for (int j = 0; j < bookCapacity; j++) {
                ratingArray[i][j] = rhs.ratingArray[i][j];
            }
        }
    }

    return *this;
}

Rating::~Rating() {
    clear();
}

void Rating::addRating(int accountId, int bookId, int rating) {
    addBook(bookId);
    addMember(accountId);
    ratingArray[accountId][bookId] = rating;
}

int Rating::getRating(int accountId, int bookId) {
    return ratingArray[accountId][bookId];
}

void Rating::addMember(int memberId) {
    if (memberId == memberCapacity) {
        resizeCol(memberCapacity * 2);
    }

}

void Rating::addBook(int bookId) {
    if (bookId == bookCapacity) {
        resizeRow(bookCapacity * 2);
    }
}

//resizes number of books
void Rating::resizeRow(int newCount) {
    // Create a new 2d dynamic array with double original book capacity
    int **newList = new int*[memberCapacity];

    //allocate cols
    for (int i = 0; i < memberCapacity; i++) {
        newList[i] = new int[newCount];
    }

    // initialize all ratings to zero in new ratings array
    for (int row = 0; row < memberCapacity; row++) {
        for (int col = 0; col < newCount; col++) {
            newList[row][col] = RATE_ZERO;
        }
    }

    // copy contents of original array to new array
    for (int i = 0; i < memberCapacity; i++) {
        for (int j = 0; j < bookCapacity; j++) {
            newList[i][j] = ratingArray[i][j];
        }
    }

    // delete contents of old array
    clear();

    bookCapacity = newCount;

    ratingArray = newList; // Assigns pointer to newList
}

void Rating::resizeCol(int newCount) {
    // Create a new 2d dynamic array with double original capacity
    int **newList = new int*[newCount];

    //allocate cols
    for (int i = 0; i < newCount; i++) {
        newList[i] = new int[bookCapacity];
    }

    // initialize all ratings to zero in new ratings array
    for (int row = 0; row < newCount; row++) {
        for (int col = 0; col < bookCapacity; col++) {
            newList[row][col] = RATE_ZERO;
        }
    }

    // copy contents of original array to new array
    for (int i = 0; i < memberCapacity; i++) {
        for (int j = 0; j < bookCapacity; j++) {
            newList[i][j] = ratingArray[i][j];
        }
    }

    // delete contents of old array
    clear();

    memberCapacity = newCount;

    ratingArray = newList; // Assigns pointer to newList
}

void Rating::clear() {
    for (int i = 0; i < memberCapacity; i++) {
        delete[] ratingArray[i];
    }
    delete[] ratingArray;
}

int Rating::mostSimilar(int accountId) {
    int highestSimilarityScore;
    int similarityScore;
    int userWithHighestSimilarity;

    for (int user = 0; user < memberCapacity; user++) {
        similarityScore = 0;
        for (int book = 0; book < bookCapacity; book++) {
            similarityScore += getRating(accountId,book) *
                               getRating(user,book);
        }
        if (similarityScore > highestSimilarityScore && user != accountId) {
            highestSimilarityScore = similarityScore;
            userWithHighestSimilarity = user;
        }

    }

    return userWithHighestSimilarity;
}



