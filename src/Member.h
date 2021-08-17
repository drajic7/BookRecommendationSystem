//
// Created by Denis on 10/2/2020.
//

#ifndef DRAJIC_P2_MEMBER_H
#define DRAJIC_P2_MEMBER_H

#include <iostream>


/**
 * Member class holds a list of current members.
 * Members are uniquely identified by a member id returned by the add method.
 */
class Member {
public:
    /**
     * Constructor
     */
    Member();

    /**
     * Copy constructor.
     * @param other Member to copy
     */
    Member(const Member &other);

    /**
     * Assignment operator -- make a deep copy.
     * @param rhs Member to copy
     * @return myself
     */
    Member &operator=(const Member &rhs);

    /**
     * Destructor
     */
    ~Member();

    /**
     * Add a new member.
     * @param memberName
     * @return member id (useful for calling findName, for example)
     */
    int addMember(std::string memberName);

    /**
     * Find the name of the given member.
     * @param memberId as returned by the addMember method
     * @return
     */
    std::string findName(int memberId);

    /**
     * Login to account.
     * @param memberId to login
     * @return true if logged in successfully or false if no such member
     */
    bool login(int memberId);

    /**
     * Logout of account.
     * @param memberName
     */
    void logout(int memberID);

    /**
     * Print to std::cout a line about the given member.
     * @param memberId as returned by the addMember method
     */
    void printAccount(int memberId);

    /**
     * Print to std::cout the entire member list contents
     */
    void print();

    /**
     * Get the cardinality of the list.
     * @return number of successful calls to add
     */
    int size();

private:
    static const int INITIAL_CAPACITY = 23;
    struct MemberInfo {
        int account;
        std::string name;
        bool loggedIn;
    };
    MemberInfo *memberArray;
    int count;
    int capacity;

    /**
     * Automatically enlarge if we get more than INITIAL_CAPACITY books in
     * the list.
     */
    void resize();

};

#endif //DRAJIC_P2_MEMBER_H
