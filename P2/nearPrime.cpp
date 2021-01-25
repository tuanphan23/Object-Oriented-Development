/*
-- Developer    : Tuan Phan
-- Project      : P2
-- Instructor   : Dr. Dingle
-- File Name    : nearPrime.cpp
-- File Version : 1.0
-- Course Name  : CPSC 3200
-----------------------------------------------------------------------------
IMPLEMENTATION INVARIANTS:

DATA MEMBERS DICTIONARY:
bool active                     - indicate object active status
bool deactivated                - indicate object permanently active status
int prime                       - hold the prime number
int numOfQueries                - hold the current number of queries
int maxQueries                  - hold the max number of queries allowed
const int MIN_PRIME= 11         - indicate the min two digits prime
const int DEFAULT_PRIME= 71     - indicate default prime value

Private Methods:
IsPrime()
- return true if number is prime otherwise it is false

initializeData()
- initialize all private data members

FindSmallerPrime()
- find next smaller prime number which utilizes the isPrime() function

FindNearPrime()
- a helper function which is utilized in the public Mod() function. It's used to
look for the appropriate nearest neighbor of current prime value

isValid()
- a helper function which is utilized in the public Mod() function. It's used to
increment the query count as well as decrement the current prime value if it
meets all the conditions. This function control the object state and will return
the current object state after the call for query. If pre-conditions are passed,
then it will return true and allow the Mod() function

Mod()
- Check pre-conditions that are passed in private function isValid(). If true
then return the near prime number that is found by the private function
FindSmallerPrime()

getActive()
- return the current state of nearPrime object

Reset()
- reset nearPrime object but only if it is currently active

Revive()
- switch object state
- will permanently deactivate object if it is currently active
- can only be used to bring back an inactive object to active state
-----------------------------------------------------------------------------
-- WHEN		WHO		WHAT
-- 1/13/21	TP  	Design and model NearPrime.cpp
-- 1/14/21  TP      Updated private member & passed in variables
--                      name to be self documenting
--                  Added documentation comments for NearPrime.cs

*/

#include "nearPrime.h"
#include <iostream>
using namespace std;

nearPrime::nearPrime() {
    active = false;
    originalPrime = 0;
    prime = 0;
    deactivated = true;
    lowerPrime = 0;
    numOfQueries = 0;
    maxQueries = 0;
}

nearPrime::nearPrime(int number) {
    if(number >= MIN_PRIME && number <= MAX_PRIME && isPrime(number))
    {
        originalPrime = number;
        active = true;
        deactivated = false;
        prime = originalPrime;
        initializeData();
    }
    else
    {
        active = false;
        deactivated = true;
        originalPrime = 0;
        prime = 0;
        lowerPrime = 0;
        numOfQueries = 0;
        maxQueries = 0;
    }
}

nearPrime::nearPrime(const nearPrime &rhs) {
    active = rhs.active;
    deactivated = rhs.deactivated;
    originalPrime = rhs.originalPrime;
    maxQueries = rhs.maxQueries;
    numOfQueries = rhs.numOfQueries;
    prime = rhs.prime;
    lowerPrime = rhs.prime;
}

nearPrime & nearPrime::operator=(nearPrime& rhs) {
    if(this != &rhs) {
        active = rhs.active;
        deactivated = rhs.deactivated;
        originalPrime = rhs.originalPrime;
        maxQueries = rhs.maxQueries;
        numOfQueries = rhs.numOfQueries;
        prime = rhs.prime;
        lowerPrime = rhs.prime;
    }

    return *this;
}

nearPrime::nearPrime(nearPrime &&rhs) {
    active = rhs.active;
    deactivated = rhs.deactivated;
    originalPrime = rhs.originalPrime;
    maxQueries = rhs.maxQueries;
    numOfQueries = rhs.numOfQueries;
    prime = rhs.prime;
    lowerPrime = rhs.prime;

    active = false;
    deactivated = false;
    originalPrime = 0;
    maxQueries = 0;
    numOfQueries = 0;
    prime = 0;
    lowerPrime = 0;
}

nearPrime & nearPrime::operator=(nearPrime &&rhs) {
    swap(active, rhs.active);
    swap(deactivated, rhs.deactivated);
    swap(originalPrime,rhs.originalPrime);
    swap(maxQueries,rhs.maxQueries);
    swap(numOfQueries,rhs.numOfQueries);
    swap(prime,rhs.prime);
    swap(lowerPrime,rhs.prime);
    return *this;
}

nearPrime::~nearPrime() {

}

void nearPrime::initializeData() {
    if(prime >= MIN_PRIME)
    {
        lowerPrime = findSmallerPrime(prime);
        numOfQueries = 0;
        maxQueries = prime - lowerPrime;
    }
    else
    {
        active = false;
    }
}

bool nearPrime::isPrime(int number) {
    for (int i = 2; i < number/2; i++)
        if (number % i == 0)
            return false;

    return true;
}

bool nearPrime::getActive() {
    return active;
}

int nearPrime::findSmallerPrime(int number) {
    number--;
    while (!isPrime(number))
        number--;
    return number;
}

int nearPrime::mod(int number) {
    int value = -1;
    if(isValid(number))
    {
        value = findNearPrime(number);
    }
    if(numOfQueries == maxQueries) {
        prime = lowerPrime;
        active = false;
        initializeData();
    }
    return value;
}

int nearPrime::findNearPrime(int number) {
    int nearPrime = -1;
    int upperNumber = prime;
    int lowerNumber = prime;
    bool found = false;
    while(!found)
    {
        if (++upperNumber % number == 0)
        {
            found = true;
            nearPrime = upperNumber;
        }
        else if(--lowerNumber >= number && lowerNumber % number == 0)
        {
            found = true;
            nearPrime = lowerNumber;
        }

    }
    return nearPrime;
}

bool nearPrime::isValid(int number) {
    if(number < 2)
    {
        active = false;
    }
    if(active)
    {
        numOfQueries++;
    }
    return active;
}

void nearPrime::reset() {
    if (active)
    {
        prime = originalPrime;
        initializeData();
    }
}

void nearPrime::revive() {
    if (deactivated)
        return;

    active = !active;

    if (active)
        initializeData();
    else
        deactivated = true;
}



