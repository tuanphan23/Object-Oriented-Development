/*
-- Developer    : Tuan Phan
-- Project      : P2
-- Instructor   : Dr. Dingle
-- File Name    : clusterP.h
-- File Version : 1.0
-- Course Name  : CPSC 3200
-----------------------------------------------------------------------------
Design Decisions and Assumptions:
- A range for the number of encapsulated nearPrime objects is given when the
 class constructor fired.
- if the constructor is passed with an invalid range for two digits number. The
 object will be constructed with default MIN_TWO_DIGITS and MAX_TWO_DIGITS range
- encapsulated nearPrime objects will be initialized during constructor based on
 input range. The distinct two digits prime numbers that each nearPrime objects
 encapsulate will be determined from input range and in ascending order.
- clusterP object will be inactive if all encapsulated nearPrime objects are
 inactive.

-----------------------------------------------------------------------------
INTERFACE INVARIANTS:
- Deep Copying is supported.

query()
- iterate all encapsulated nearPrime objects.

getMinValue()
- return min near prime value of encapsulated nearPrime objects.
- return -1 if clusterP object is inactive

getMaxValue()
- return max near prime value of encapsulated nearPrime objects.
- return -1 if clusterP object is inactive

getNumberOfMatches()
- return the numbers of encapsulated nearPrime objects that have the same near prime
 value.
- return -1 if clusterP object is inactive

getActive()
- return the current state of clusterP object

checkActive()
- check the state of all encapsulated nearPrime objects. Toggle the state of clusterP
 object if all encapsulated nearPrime objects are inactive

getPrimeArray()
- assigns new[] memory at primeArray's location and must be freed after use. Return the
 number of distinct nearPrime objects;

-----------------------------------------------------------------------------
CLASS INVARIANTS:
- client must define the range of prime number for encapsulated nearPrime objects

- Deep copying is supported.

- query() will iterate all encapsulated nearPrime objects.

- getMinValue() will return the min near prime numbers closest to the encapsulated
 prime number of nearPrime objects.

- getMaxValue() will return the max near prime numbers closest to the encapsulated
 prime number of nearPrime objects.

- getNumberOfMatches() will return the numbers of nearPrimes object that return
 the same values.

-----------------------------------------------------------------------------
-- WHEN		WHO		WHAT
-- 1/24/21	TP  	Design and model clusterP.h
-- 1/25/21  TP      Updated private member & passed in variables
--                      name to be self documenting
--                  Added documentation comments for clusterP.h

*/

#ifndef P2_CLUSTERP_H
#define P2_CLUSTERP_H

#include "nearPrime.h"

class clusterP{
    public:

        // Pre: Client must provide the range for nearPrime objects.
        // Post: clusterP object is constructed and fields are initialized.
        clusterP(int end) : clusterP(10, end) {};

        // Pre: Client must provide the range for nearPrime objects.
        // Post: clusterP object is constructed and fields are initialized.
        clusterP(int start, int end);

        // Pre: None
        // Post: Object is copied
        clusterP(const clusterP& rhs);

        // Pre: None
        // Post: Object is assigned.
        clusterP&  operator=(const clusterP& src);

        // Pre: None
        // Post: Object is copied. Heap memory is stolen.
        clusterP(clusterP&& src);

        // Pre: None
        // Post: Object is assigned. Heap memory is stolen.
        clusterP& operator=(clusterP&& src);

        // Pre: None
        // Post: Memory is deallocated.
        ~clusterP();

        // Pre: A specific iteration of nearPrime objects is needed.
        // Post: Some nearPrime objects might be inactive
        //        clusterP object might be inactive
        void query(int number);

        // Pre: None
        // Post: None
        int getMinValue();

        // Pre: None
        // Post: None
        int getMaxValue();

        // Pre: None
        // Post: None
        int getNumberOfMatches();

        // Pre: None
        // Post: None
        bool getActive();

    private:
        const int MIN_TWO_DIGITS = 10;
        const int MAX_TWO_DIGITS = 99;
        bool active;
        int numberOfObjects;

        struct nearPrimeInfo {
            int nearPrimeValue;
            int encapsulatedNumber;
            nearPrime np;
        };
        nearPrimeInfo* infoArray;

        // Pre: None
        // Post: clusterP object might be inactive
        void checkActive();

        // Pre: primeArray is initialize
        // Post: numberOfObjects is defined
        unsigned getPrimeArray(int start, int end, unsigned** primeArray);
};

#endif //P2_CLUSTERP_H
