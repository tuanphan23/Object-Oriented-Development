/*
-- Developer    : Tuan Phan
-- Project      : P2
-- Instructor   : Dr. Dingle
-- File Name    : nearPrime.h
-- File Version : 1.0
-- Course Name  : CPSC 3200
-----------------------------------------------------------------------------
Design Decisions and Assumptions:
- A prime number is given when the class constructor fired.
- The prime number must be two digits
- if the constructor is passed with an invalid two digits prime number. The
object will be deactivated
- "maxQueries" will be initialized during constructor based off of "prime" and
"lowerPrime".
- when reaching to maxQueries the nearPrime object state will become inactive
- The prime number will be decreased when reaching the max number of queries
allowed
- The nearPrime object will be active unless the input number for mod function
is invalid, or the value of current prime number is smaller than 11
- Revive an inactive nearPrime object will toggle the object state and reset the
current number of queries. Current prime number is not changed back to original
prime number and "maxQueries" will be defined again base on value of current
"prime" and "lowerPrime". If current "prime" is smaller than 11 object will
become inactive.

-----------------------------------------------------------------------------
INTERFACE INVARIANTS:
IsPrime()
- return true if number is two digits prime
- return false if number is not two digits prime

initializeData()
- initialize all private data members

FindSmallerPrime()
- return next smaller prime

FindNearPrime()
- return the near prime number

Mod()
- return the near prime number of current prime number. If Object is inactive
or input value is < 2 or current prime number is smaller than 11
it will return 0

getActive()
- return the current state of nearPrime object

Reset()
- reset nearPrime object but only if it is currently active

Revive()
- toggle object state
- permanently deactivate object if object is currently active
- can only be used to bring back an inactive object to active state

-----------------------------------------------------------------------------
CLASS INVARIANTS:
Return the near prime number when meets the following requirements:
1. Object state is active
2. must be given a two digits prime number
3. input number is valid

-----------------------------------------------------------------------------
-- WHEN		WHO		WHAT
-- 1/13/21	TP  	Design and model NearPrime.h
-- 1/14/21  TP      Updated private member & passed in variables
--                      name to be self documenting
--                  Added documentation comments for NearPrime.cs

*/

#ifndef P2_NEARPRIME_H
#define P2_NEARPRIME_H

class nearPrime {

    public:

        // Pre: Object Invoked.
        // Post: Fields for Object instantiated.
        nearPrime();

        // Pre: Object Invoked.
        // Post: Fields for Object instantiated.
        nearPrime(int number);

        // Pre: None
        // Post: Object copied to another instance.
        nearPrime(const nearPrime& rhs);

        // Pre: None
        // Post: Object assigned to another instance.
        nearPrime& operator=(nearPrime& rhs);

        // Pre: None
        // Post: Object copied to another instance.
        // allocated memory is stolen.
        nearPrime(nearPrime&& rhs);

        // Pre: None
        // Post: Object assigned to another instance.
        // allocated memory is stolen.
        nearPrime& operator=(nearPrime&& rhs);

        // Pre: None
        // Post: Object Deallocated.
        ~nearPrime();

        // PRE : N/A
        // POST : N/A
        bool getActive();

        // PRE : Object state is already assigned
        //        CountQueries is already defined
        // POST : PrimeNumber might be decreased
        //        CountQueries might be set to it's default value
        int mod(int number);

        // PRE : object state should be active
        // POST : numOfQueries will be reset to 0
        //        maxQueries will be reset base on the current value of prime
        void reset();

        // PRE : Object state must be inactive and cannot be deactivated and
        //          is a mutator function which controls state
        // POST : Toggle object state
        //        If Pre-condition was followed, private data members will
        //          be reset
        //        Object will be permanently deactivated if pre condition
        //          wasn't followed
        void revive();

    private:
        bool active;
        bool deactivated;
        int numOfQueries;
        int maxQueries;
        int originalPrime;
        int prime;
        int lowerPrime;

        const int MIN_PRIME = 11;
        const int MAX_PRIME = 97;

        // PRE : prime is already defined
        // POST : lowerPrime is defined
        //        numOfQueries is defined
        //        maxQueries is defined
        void initializeData();

        // PRE : N/A
        // POST : N/A
        bool isPrime(int number);

        // PRE : N/A
        // POST : N/A
        int findSmallerPrime(int number);

        // PRE : prime is already defined
        // POST : N/A
        int findNearPrime(int number);

        // PRE : Object must be active
        //        numOfQueries is already defined
        //        maxQueries is already defined
        //        input number is valid
        // POST : Object state will be inactive if invalid input number or
        //          prime number is smaller than 11
        //        prime number might be decreased to lower prime number
        //        numOfQueries might incremented or reset
        bool isValid(int number);


};

#endif //P2_NEARPRIME_H
