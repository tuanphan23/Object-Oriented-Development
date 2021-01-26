/*
-- Developer    : Tuan Phan
-- Project      : P1
-- Instructor   : Dr. Dingle
-- File Name    : NearPrime.cs
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
-- 1/13/21	TP  	Design and model NearPrime.cs
-- 1/14/21  TP      Updated private member & passed in variables 
--                      name to be self documenting
--                  Added documentation comments for NearPrime.cs
 
*/

namespace P1
{
    public class NearPrime
    {
        private bool active;
        private bool deactivated;
        private int numOfQueries;
        private int maxQueries;
        private int originalPrime;
        private int prime;
        private int lowerPrime;
        private const int MIN_PRIME = 11;
        private const int MAX_PRIME = 97;

        public NearPrime(int number)
        {
            if(number >= MIN_PRIME && number <= MAX_PRIME && IsPrime(number))
            {
                this.originalPrime = number;
                active = true;
                deactivated = false;
                this.prime = this.originalPrime;
                initializeData();
            }
            else
            {
                active = false;
                deactivated = true;
            }
            
        }

        // PRE : prime is already defined
        // POST : lowerPrime is defined
        //        numOfQueries is defined
        //        maxQueries is defined
        private void initializeData()
        {
            if(this.prime >= MIN_PRIME)
            {
                lowerPrime = FindSmallerPrime(this.prime);
                numOfQueries = 0;
                maxQueries = this.prime - lowerPrime;
            }
            else
            {
                active = false;
            }
        }

        // PRE : N/A
        // POST : N/A
        private bool IsPrime(int number)
        {
            for (int i = 2; i < number/2; i++)
                if (number % i == 0)
                    return false;

            return true;
        }

        // PRE : N/A
        // POST : N/A
        public bool getActive()
        {
            return active;
        }

        // PRE : N/A
        // POST : N/A
        private int FindSmallerPrime(int number)
        {
            number--;
            while (!IsPrime(number))
                number--;
            return number;
        }

        // PRE : prime is already defined
        // POST : N/A
        private int FindNearPrime(int number)
        {
            int nearPrime = 0;
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

        // PRE : Object state is already assigned
        //        CountQueries is already defined
        // POST : PrimeNumber might be decreased
        //        CountQueries might be set to it's default value
        public int Mod(int number)
        {
            if(IsValid(number))
            {
                return FindNearPrime(number);
            }

            return 0;
        }

        // PRE : Object must be active
        //        numOfQueries is already defined
        //        maxQueries is already defined
        //        input number is valid
        // POST : Object state will be inactive if invalid input number or
        //          prime number is smaller than 11
        //        prime number might be decreased to lower prime number
        //        numOfQueries might incremented or reset
        private bool IsValid(int number)
        {
            if(number < 2)
            {
                active = false;
            }
            if(active)
            {
                if(numOfQueries == maxQueries)
                {
                    this.prime = this.lowerPrime;
                    active = false;
                    initializeData();
                }
                else
                {
                    numOfQueries++;
                }
            }
            return active;
        }

        // PRE : object state should be active
        // POST : numOfQueries will be reset to 0
        //        maxQueries will be reset base on the current value of prime
        public void Reset()
        {
            if (active)
            {
                this.prime = originalPrime;
                initializeData();
            }
        }

        // PRE : Object state must be inactive and cannot be deactivated and
        //          is a mutator function which controls state
        // POST : Toggle object state
        //        If Pre-condition was followed, private data members will
        //          be reset
        //        Object will be permanently deactivated if pre condition
        //          wasn't followed 
        public void Revive()
        {
            if (deactivated)
                return;

            active = !active;

            if (active)
                initializeData();
            else
                deactivated = true;
        }
           
    }
}

/*
-------------------------------------------------------------------------------
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
*/