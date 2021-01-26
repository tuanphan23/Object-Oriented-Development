/*
-- Developer    : Tuan Phan
-- Project      : P1
-- Instructor   : Dr. Dingle
-- File Name    : UnitTest1.cs
-- File Version : 1.0
-- Course Name  : CPSC 3200
*/

using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using P1;

namespace P1Test
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void Test_Mod()
        {
            //arrange
            int[] PRIME_ARRAY = { 11, 13, 17, 19, 23, 29, 31,
            37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
            Random random = new Random();
            int index = random.Next(0, PRIME_ARRAY.Length);
            int prime = PRIME_ARRAY[index];
            NearPrime obj = new NearPrime(prime);
            int number = random.Next(2, prime);

            //act
            int expectedValue = 0;
            int upperNumber = prime;
            int lowerNumber = prime;
            bool found = false;
            while (!found)
            {
                if (++upperNumber % number == 0)
                {
                    found = true;
                    expectedValue = upperNumber;
                }
                else if (--lowerNumber >= number && lowerNumber % number == 0)
                {
                    found = true;
                    expectedValue = lowerNumber;
                }

            }

            //assert
            Assert.AreEqual(expectedValue, obj.Mod(number));
        }

        [TestMethod]
        public void Test_Mod_Into_Inactive()
        {
            //arrange
            int[] PRIME_ARRAY = { 11, 13, 17, 19, 23, 29, 31,
            37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
            Random random = new Random();
            int index = random.Next(1, PRIME_ARRAY.Length);
            int prime = PRIME_ARRAY[index];
            NearPrime obj = new NearPrime(prime);
            int number = random.Next(2, prime);

            //act
            int maxQueries = PRIME_ARRAY[index] - PRIME_ARRAY[index - 1];
            for (int i = 0; i < maxQueries; i++)
            {
                obj.Mod(number);
            }
            bool expectedState = false;
            int expedtedReturn = 0;

            //assert
            Assert.AreEqual(expedtedReturn, obj.Mod(number));
            Assert.AreEqual(expectedState, obj.getActive());
        }

        [TestMethod]
        public void Test_Mod_Invalid_Number()
        {
            //arrange
            int[] PRIME_ARRAY = { 11, 13, 17, 19, 23, 29, 31,
            37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
            Random random = new Random();
            int index = random.Next(1, PRIME_ARRAY.Length);
            int prime = PRIME_ARRAY[index];
            NearPrime obj = new NearPrime(prime);
            int invalidNumber = random.Next(-10, 2);

            //act
            obj.Mod(invalidNumber);
            bool expectedState = false;

            //assert
            Assert.AreEqual(expectedState, obj.getActive());
        }

        [TestMethod]
        public void Test_Reset()
        {
            //arrange
            int[] PRIME_ARRAY = { 11, 13, 17, 19, 23, 29, 31,
            37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
            Random random = new Random();
            int index = random.Next(1, PRIME_ARRAY.Length);
            int prime = PRIME_ARRAY[index];
            NearPrime obj = new NearPrime(prime);
            int number = random.Next(2, prime);

            //act
            int maxQueries = PRIME_ARRAY[index] - PRIME_ARRAY[index - 1];
            for (int i = 0; i < maxQueries; i++)
            {
                obj.Mod(number);
            }
            obj.Reset();

            bool expectedState = true;
            int expectedValue = 0;
            int upperNumber = prime;
            int lowerNumber = prime;
            bool found = false;
            while (!found)
            {
                if (++upperNumber % number == 0)
                {
                    found = true;
                    expectedValue = upperNumber;
                }
                else if (--lowerNumber >= number && lowerNumber % number == 0)
                {
                    found = true;
                    expectedValue = lowerNumber;
                }
            }

            //assert
            Assert.AreEqual(expectedValue, obj.Mod(number));
            Assert.AreEqual(expectedState, obj.getActive());
        }

        [TestMethod]
        public void Test_Revive()
        {
            //arrange
            int[] PRIME_ARRAY = { 11, 13, 17, 19, 23, 29, 31,
            37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
            Random random = new Random();
            int index = random.Next(1, PRIME_ARRAY.Length);
            int prime = PRIME_ARRAY[index];
            NearPrime obj = new NearPrime(prime);
            int validNumber = random.Next(2, prime);
            int invalidNumber = random.Next(-10, 2);

            //act
            obj.Mod(invalidNumber);
            if (!obj.getActive())
                obj.Revive();
            bool expectedState = true;
            int expectedValue = 0;
            int upperNumber = prime;
            int lowerNumber = prime;
            bool found = false;
            while (!found)
            {
                if (++upperNumber % validNumber == 0)
                {
                    found = true;
                    expectedValue = upperNumber;
                }
                else if (--lowerNumber >= validNumber &&
                    lowerNumber % validNumber == 0)
                {
                    found = true;
                    expectedValue = lowerNumber;
                }
            }
            //assert
            Assert.AreEqual(expectedValue, obj.Mod(validNumber));
            Assert.AreEqual(expectedState, obj.getActive());
        }

        [TestMethod]
        public void Test_Revive_When_Active()
        {
            //arrange
            int[] PRIME_ARRAY = { 11, 13, 17, 19, 23, 29, 31,
            37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
            Random random = new Random();
            int index = random.Next(1, PRIME_ARRAY.Length);
            int prime = PRIME_ARRAY[index];
            NearPrime obj = new NearPrime(prime);

            //act
            if (obj.getActive())
                obj.Revive();
            bool expectedState = false;

            //assert
            Assert.AreEqual(expectedState, obj.getActive());
        }
    }
}
