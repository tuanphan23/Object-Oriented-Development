/*
-- Developer    : Tuan Phan
-- Project      : P2
-- Instructor   : Dr. Dingle
-- File Name    : cluterP.cpp
-- File Version : 1.0
-- Course Name  : CPSC 3200
-----------------------------------------------------------------------------
IMPLEMENTATION INVARIANTS:

DATA MEMBERS DICTIONARY:
bool active                     - indicate object active status
int numberOfObjects             - hold the number of encapsulated nearPrime object
struct nearPrimeInfo            - hold the nearPrime value corresponding with
                                    encapsulated nearPrime object
const int MIN_TWO_DIGITS = 10   - indicate the min two digits number
const int MAX_TWO_DIGITS = 99   - indicate the max two digits number

Private Methods:
getPrimeArray()
- a helper function which assigns new[] memory at primeArray's location and must
 be freed after use. Return the number of distinct nearPrime objects;

checkActive()
- a helper function which is utilized in the public Mod() function. It's used to
increment the query count as well as decrement the current prime value if it
meets all the conditions. This function control the object state and will return
the current object state after the call for query. If pre-conditions are passed,
then it will return true and allow the Mod() function

Public Methods:
getActive()
- return the current state of clusterP object

query()
- if clusterP object state is active, iterate all encapsulated nearPrime objects.
 Otherwise return.

getMinValue()
- if clusterP object state is active, return min near prime value of encapsulated
 nearPrime objects. Otherwise return -1;

getMaxValue()
- if clusterP object state is active, return max near prime value of encapsulated
 nearPrime objects. Otherwise return -1;

getNumberOfMatches()
- if clusterP object state is active, return the numbers of encapsulated nearPrime
 objects that have the same near prime value. Otherwise return -1;
-----------------------------------------------------------------------------
-- WHEN		WHO		WHAT
-- 1/24/21	TP  	Design and model clusterP.cpp
-- 1/25/21  TP      Updated private member & passed in variables
--                      name to be self documenting
--                  Added documentation comments for clusterP.cpp

*/

#include "clusterP.h"
#include <iostream>
#include <unordered_set>
using namespace std;

clusterP::clusterP(int start, int end) {
    if(start < MIN_TWO_DIGITS)
        start = MIN_TWO_DIGITS;
    if(end > MAX_TWO_DIGITS)
        end = MAX_TWO_DIGITS;
    if(start > end)
        swap(start, end);
    active = true;
    unsigned int* primeArray = 0;
    numberOfObjects = getPrimeArray(start, end, &primeArray);

    if(numberOfObjects) {
        infoArray = new nearPrimeInfo[numberOfObjects];
        for(int i = 0; i < numberOfObjects; i++) {
            infoArray[i].nearPrimeValue = 0;
            infoArray[i].encapsulatedNumber = primeArray[i];
            infoArray[i].np = nearPrime(infoArray[i].encapsulatedNumber);
        }
    }
    else {
        active = false;
        numberOfObjects = 0;
        infoArray = nullptr;
    }
    delete[] primeArray;
}

unsigned int clusterP::getPrimeArray(int start, int end, unsigned int **primeArray) {
    unsigned int count = 0;
    unsigned int size = 10;
    unsigned int* primeNumbers = new unsigned int[size];
    bool isPrime;

    if(start % 2 == 0) ++start;
    for(int i = start; i <= end; i += 2) {
        isPrime = true;
        for(int j = 3; j < i/2; j += 2) {
            if(i % j == 0) {
                isPrime = false;
                break;
            }
        }
        if(!isPrime)
            continue;
        if(count == size) {
            size *= 2;
            unsigned int* temp = new unsigned int[size];
            for(int k = 0; k < count; k++) {
                temp[k] = primeNumbers[k];
            }
            delete[] primeNumbers;
            primeNumbers = temp;
        }
        primeNumbers[count] = i;
        ++count;
    }
    *primeArray = primeNumbers;
    return count;
}

clusterP::clusterP(const clusterP &rhs) {
    numberOfObjects = rhs.numberOfObjects;
    active = rhs.active;
    infoArray = new nearPrimeInfo[rhs.numberOfObjects];
    for(int i = 0; i < numberOfObjects; i++) {
        infoArray[i] = rhs.infoArray[i];
    }
}

clusterP &  clusterP::operator=(const clusterP &rhs) {
    if(this != &rhs) {
        delete[] infoArray;
        active = rhs.active;
        numberOfObjects = rhs.numberOfObjects;
        infoArray = new nearPrimeInfo[numberOfObjects];
        for(int i = 0; i < numberOfObjects; i++) {
            infoArray[i] = rhs.infoArray[i];
        }
    }
    return *this;
}

clusterP::clusterP(clusterP &&src) {
    active = src.active;
    numberOfObjects = src.numberOfObjects;
    infoArray = src.infoArray;
    src.active = false;
    src.numberOfObjects = 0;
    src.infoArray = nullptr;
}

clusterP & clusterP::operator=(clusterP &&src) {
    swap(active, src.active);
    swap(numberOfObjects, src.numberOfObjects);
    for(int i = 0; i < numberOfObjects; i++) {
        swap(infoArray[i], src.infoArray[i]);
    }
    return *this;
}

clusterP::~clusterP() {
    delete[] infoArray;
}

bool clusterP::getActive() {
    return active;
}

void clusterP::query(int number) {
    if(!active)
        return;
    for(int i = 0; i < numberOfObjects; i++) {
        infoArray[i].nearPrimeValue = infoArray[i].np.mod(number);
    }
    checkActive();
}

int clusterP::getMinValue() {
    if(!active)
        return -1;
    int min = INT_MAX;
    for(int i = 0; i < numberOfObjects; i++) {
        if(infoArray[i].nearPrimeValue == -1)
            continue;
        if(infoArray[i].nearPrimeValue < min) {
            min = infoArray[i].nearPrimeValue;
        }
    }
    return (min == INT_MAX) ? -1 : min;
}

int clusterP::getMaxValue() {
    if(!active)
        return -1;
    int max = INT_MIN;
    for(int i = 0; i < numberOfObjects; i++) {
        if(infoArray[i].nearPrimeValue == -1)
            continue;
        if(infoArray[i].nearPrimeValue > max) {
            max = infoArray[i].nearPrimeValue;
        }
    }
    return (max == INT_MIN) ? -1 : max;
}

int clusterP::getNumberOfMatches() {
    if(!active)
        return -1;
    unordered_set<int> valueSet;
    int numberOfMatches = 0;
    for(int i = 0; i < numberOfObjects; i++) {
        if(infoArray[i].nearPrimeValue == -1)
            continue;
        if (valueSet.find(infoArray[i].nearPrimeValue) == valueSet.end())
            valueSet.insert(infoArray[i].nearPrimeValue);
        else
            numberOfMatches++;
    }
    return numberOfMatches;
}

void clusterP::checkActive() {
    int count = 0;
    for(int i = 0; i < numberOfObjects; i++) {
        if(!infoArray[i].np.getActive())
            count++;
    }
    if(count == numberOfObjects)
        active = false;
}