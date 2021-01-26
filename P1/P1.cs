/*
-- Developer    : Tuan Phan
-- Project      : P1
-- Instructor   : Dr. Dingle
-- File Name    : p1.cs
-- File Version : 1.0
-- Course Name  : CPSC 3200
----------------------------------------------------------------------------
Design Decisions and Assumptions:
-- Methods:
Private
    N/A
Public
    InitializeRandomTwoDigitsPrime(int[] randomPrime)
    InitializeNearPrimeObject(NearPrime[] obj, int[] randomPrime)
    SimulateObjects(NearPrime obj, int name)
    TestModFunctionWithValidInput(NearPrime obj, int queries)
    TestModFunctionWithInValidInput(NearPrime obj, int queries)
    TestReviveWithActiveObject(NearPrime obj, int name)

-- Driver Design:
PRIME_ARRAY contains all two digits prime number
Random two digits prime number will be picked in PRIME_ARRAY;
Five different nearPrime objects will be declared and initialized with a random
two digits prime number aboved
Firstly querying for a valid input value and revive object if it reach maximum
number of queries. Reset obj after reviving it. 
Secondly querying for an invalid input value and revive when the object is inactive
Reset obj after reviving it.
Finally, attemp to revie the nearPrime object when it is currently active. Object
will become deactivated and return 0 whenever it is being queried again

-- Assumptions:
For two digits prime the difference between two adjacent number will range from
2 to 8. The number of queries will range from 1 to 10 which will sufficient
enough to yield objects in different state.
----------------------------------------------------------------------------
WHEN     WHO    WHAT
1/13/21	   TP  	Created p1.cs
1/14/21    TP   Test InitializeNearPrimeObject()
                Test SimulateObjects()
                Test TestReviveWithActiveObject()
                Added comments

*/

using System;

namespace P1
{
    class P1
    {
        const int NUMBER_OF_OBJECTS = 7;
        const int NUMBER_OF_VALID_PRIMES = 5;
        const int minNumberValidInput = 2;
        const int minQueries = 1;
        const int maxQueries = 10;
        static void Main(string[] args)
        {
            Console.WriteLine("------------- Program start -----------");
            int[] randomPrime = new int[NUMBER_OF_OBJECTS];           
            NearPrime[] obj = new NearPrime[NUMBER_OF_OBJECTS];
            InitializeRandomTwoDigitsPrime(randomPrime);
            InitializeNearPrimeObject(obj, randomPrime);
            for(int i = 0; i < NUMBER_OF_VALID_PRIMES; i++)
            {
                Console.WriteLine("======== Test Object {0} =========", i + 1);
                Console.WriteLine("Obj{0} is encapsulated a valid two digits" +
                    "prime number", i + 1);
                SimulateObjects(obj[i], i);
                Console.WriteLine();

            }
            for(int i = NUMBER_OF_VALID_PRIMES; i < NUMBER_OF_OBJECTS; i++)
            {
                Console.WriteLine("======== Test Object {0} =========", i + 1);
                Console.WriteLine("Obj{0} is encapsulated an invalid two digits" +
                    " prime number", i + 1);
                SimulateObjects(obj[i], i);
                Console.WriteLine();
            }
            Console.WriteLine("------------- Program stop -----------");
        }

        public static void InitializeRandomTwoDigitsPrime(int[] randomPrime)
        {
            Console.WriteLine("Initialize random two digits prime number");
            int[] PRIME_ARRAY = { 11, 13, 17, 19, 23, 29, 31,
            37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
            Random random = new Random();
            for (int i = 0; i < NUMBER_OF_OBJECTS; i++)
            {
                int randomIndex = random.Next(PRIME_ARRAY.Length);
                randomPrime[i] = PRIME_ARRAY[randomIndex];
            }
        }

        public static void InitializeNearPrimeObject(NearPrime[] obj,
            int[] randomPrime)
        {
            Console.WriteLine("Initialize nearPrime objects");
            for (int i = 0; i < NUMBER_OF_VALID_PRIMES; i++)
            {
                obj[i] = new NearPrime(randomPrime[i]);
            }
            Random random = new Random();
            for (int i = NUMBER_OF_VALID_PRIMES; i < NUMBER_OF_OBJECTS; i++)
            {
                int randomNumber = random.Next(-10, 110);
                while (randomNumber >= 11 && randomNumber <= 97)
                {
                    randomNumber = random.Next(-10, 110);
                }
                obj[i] = new NearPrime(randomNumber);
            }
        }

        public static void SimulateObjects(NearPrime obj, int name)
        {
            Random random = new Random();

            Console.WriteLine("Testing object with valid input");
            Console.WriteLine("x     obj{0}.mod(x)", name + 1);
            int queries = random.Next(minQueries, maxQueries);
            TestModFunctionWithValidInput(obj, queries);

            Console.WriteLine();
            Console.WriteLine("Object is reset...");
            obj.Reset();
            Console.WriteLine();

            Console.WriteLine("Testing object with invalid input");
            Console.WriteLine("x     obj{0}.mod(x)", name + 1);
            TestModFunctionWithInValidInput(obj, queries);

            Console.WriteLine();
            Console.WriteLine("Object is reset...");
            obj.Reset();
            Console.WriteLine();
            Console.WriteLine("Testing revive active object");
            TestReviveWithActiveObject(obj, name, queries);

        }

        public static void TestModFunctionWithValidInput(NearPrime obj,
            int queries)
        {
            int value = 0;
            for (int i = minNumberValidInput; i <= minNumberValidInput +
                queries; i++)
            {
                if(obj.getActive())
                {
                    value = obj.Mod(i);
                }
                if (value != 0)
                    Console.WriteLine(i + "        " + value);
                else
                {
                    Console.WriteLine("Exceeded the query limit -- Reviving");
                    obj.Revive();
                    break;
                }
            }
        }

        public static void TestModFunctionWithInValidInput(NearPrime obj,
            int queries)
        {
            for (int i = minNumberValidInput - queries; i < minNumberValidInput;
                i++)
            {
                if (obj.getActive())
                    Console.WriteLine(i + "         " + obj.Mod(i) + "  ");
                else
                {
                    Console.WriteLine("Input value is not valid -- Reviving");
                    obj.Revive();
                    break;
                }
            }
        }

        public static void TestReviveWithActiveObject(NearPrime obj, int name,
            int queries)
        {
            while(obj.getActive())
            {
                Console.WriteLine("obj{0} is currently active -- " +
                    "Trying to revive", name + 1);
                obj.Revive();
            }
            Console.WriteLine("x     obj{0}.mod(x)", name + 1);
            for (int i = minNumberValidInput; i <= minNumberValidInput + queries;
                i++)
            {
                if (obj.getActive())
                    Console.WriteLine(i + "         " + obj.Mod(i) + "  ");
                else
                {
                    Console.WriteLine("Obj{0} is permanently deactivated",
                        name + 1);
                    break;
                }
            }
        }
    }
}