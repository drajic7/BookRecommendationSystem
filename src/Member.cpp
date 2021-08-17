//
// Created by Denis on 10/2/2020.
//

#include "Member.h"

using namespace std;

Member::Member() {
    capacity = INITIAL_CAPACITY;
    memberArray = new MemberInfo[INITIAL_CAPACITY];
    count = 0;
}

Member::Member(const Member &other) {
    capacity = other.capacity;
    memberArray = new MemberInfo[capacity];
    count = other.count;
    for (int i = 0; i < count; i++) {
        memberArray[i] = other.memberArray[i];
    }
}

Member &Member::operator=(const Member &rhs) {
    if (&rhs != this) {
        delete[] memberArray;
        capacity = rhs.capacity;
        count = rhs.count;
        memberArray = new MemberInfo[rhs.capacity];
        for (int i = 0; i < count; i++) {
            memberArray[i] = rhs.memberArray[i];
        }
    }

    return *this;
}

Member::~Member() {
    delete []memberArray;
}

int Member::addMember(std::string memberName) {
    if (count == capacity) {
        resize();
    }
    memberArray[count].name = memberName;
    memberArray[count].account = count + 1;
    memberArray[count].loggedIn = false;

    count++;

    return memberArray[count - 1].account;
}

void Member::resize() {
    // Double capacity of array
    capacity *= 2;

    // Create a new dynamic array with double original capacity
    MemberInfo *newList = new MemberInfo[capacity];

    // Copy contents of original array to new array
    for (int i = 0; i < count; i++) {
        newList[i] = memberArray[i];
    }

    delete[] memberArray;  // Delete contents at address of pointer
    memberArray = newList; // Assigns pointer to newList
}

std::string Member::findName(int memberId) {
    for (int i = 0; i < count; i++) {
        if (memberId == memberArray[i].account) {
            return memberArray[i].name;
        }
    }

    return "MEMBER_NOT_FOUND";
}

int Member::size() {
    return count;
}

bool Member::login(int memberId) {
    for (int i = 0; i < count; i++) {
        if (memberArray[memberId - 1].account == memberId) {
            memberArray[memberId - 1].loggedIn = true;
            return true;
        }
    }
    return false;
}

void Member::logout(int memberId) {
    for (int i = 0; i < count; i++) {
        if (memberArray[memberId - 1].account == memberId) {
            memberArray[memberId - 1].loggedIn = false;
        }
    }
}

void Member::printAccount(int memberId) {
    cout << memberArray[memberId - 1].name << ", Account #: " <<
    memberArray[memberId - 1].account << endl;

}

void Member::print() {
    for (int i = 0; i < count; i++) {
        cout << memberArray[i].name << endl;
    }
}



