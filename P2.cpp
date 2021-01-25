/*
-- Developer    : Tuan Phan
-- Project      : P2
-- Instructor   : Dr. Dingle
-- File Name    : p2.cpp
-- File Version : 1.0
-- Course Name  : CPSC 3200
----------------------------------------------------------------------------
Design Decisions and Assumptions:
-- Driver Design:
MIN_TWO_DIGITS is the smallest two digits number
MAX_TWO_DIGITS is the biggest two digits number
Each clusterP objects will be declared and initialized with a random range
from MIN_TWO_DIGITS to MAX_TWO_DIGITS
Firstly, test querying min value, max value and number of matches of a random
clusterP object
Secondly, test assignment operator, copy operator and move semantics of clusterP
objects
Thirdly, using vector container, add and remove heap-allocated clusterP objects
Finally, test copying of clusterP objects via call by value.

-- Assumptions:
Deep copying is supported
The range for clusterP objects will be choose randomly from 10 to 99 which will
sufficient enough to yield objects in different state.

----------------------------------------------------------------------------
WHEN     WHO    WHAT
1/24/21	  TP  	Created p2.cpp
1/24/21   TP    Test test_key_functionalities()
                Test test_assignment_operator()
1/24/21   TP    Test test_copy_operator()
                Test test_move_semantics();
                Test test_heap_allocated_using_uniquePtr()
                Test test_copying_via_call_by_value()
                Added comments
*/

#include "clusterP.h"
#include <iostream>
#include <random>
#include <vector>
#include <memory>
#include <utility>

using namespace std;
const int MIN_TWO_DIGITS = 10;
const int MAX_TWO_DIGITS = 99;

int generate_random_number(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

unique_ptr<clusterP> unique_clusterP_object(unsigned int start, unsigned int end) {
    unique_ptr<clusterP> uniquePtr(new clusterP(start, end));
    return uniquePtr;
}

shared_ptr<clusterP> shareable_clusterP_object(unsigned int start, unsigned int end) {
    shared_ptr<clusterP> shareablePtr(new clusterP(start, end));
    return shareablePtr;
}

void test_key_functionalities() {
    int start = generate_random_number(MIN_TWO_DIGITS, MAX_TWO_DIGITS);
    int end = generate_random_number(MIN_TWO_DIGITS, MAX_TWO_DIGITS);
    int randomNumber = generate_random_number(2, 10);

    cout << "Create and Test object #1: " << endl;
    clusterP object1(start, end);
    object1.query(randomNumber);
    cout << "Mod(" << randomNumber << ")";
    cout << "     Min" << "    Max" << "    Matches" << endl;
    cout << "object #1  " << object1.getMinValue();
    cout << "     " << object1.getMaxValue();
    cout << "     " << object1.getNumberOfMatches() << endl;
}

void test_assignment_operator() {
    int start = generate_random_number(MIN_TWO_DIGITS, MAX_TWO_DIGITS);
    int end = generate_random_number(MIN_TWO_DIGITS, MAX_TWO_DIGITS);
    int randomNumber = generate_random_number(2, 10);

    cout << "Create object #1" << endl;
    clusterP object1(start, end);
    cout << "Create object #2 and assign object #1 to object #2" << endl;
    clusterP object2 = object1;
    cout << "Testing object #1 and object #2 - Expect return the same values" << endl;
    object1.query(randomNumber);
    object2.query(randomNumber);
    cout << "Mod(" << randomNumber << ")";
    cout << "     Min" << "    Max" << "    Matches" << endl;
    cout << "object #1  " << object1.getMinValue();
    cout << "     " << object1.getMaxValue();
    cout << "     " << object1.getNumberOfMatches() << endl;
    cout << "object #2  " << object2.getMinValue();
    cout << "     " << object2.getMaxValue();
    cout << "     " << object2.getNumberOfMatches() << endl;
}

void test_copy_operator() {
    int start = generate_random_number(MIN_TWO_DIGITS, MAX_TWO_DIGITS);
    int end = generate_random_number(MIN_TWO_DIGITS, MAX_TWO_DIGITS);
    int randomNumber = generate_random_number(2, 10);

    cout << "Create object #1" << endl;
    clusterP object1(start, end);
    cout << "Create object #2 and assign object #1 to object #2" << endl;
    clusterP object2(object1);
    cout << "Testing object #1 and object #2 - Expect return the same values" << endl;
    object1.query(randomNumber);
    object2.query(randomNumber);
    cout << "Mod(" << randomNumber << ")";
    cout << "     Min" << "    Max" << "    Matches" << endl;
    cout << "object #1  " << object1.getMinValue();
    cout << "     " << object1.getMaxValue();
    cout << "     " << object1.getNumberOfMatches() << endl;
    cout << "object #2  " << object2.getMinValue();
    cout << "     " << object2.getMaxValue();
    cout << "     " << object2.getNumberOfMatches() << endl;
}

void test_move_semantics() {
    int start = generate_random_number(MIN_TWO_DIGITS, MAX_TWO_DIGITS);
    int end = generate_random_number(MIN_TWO_DIGITS, MAX_TWO_DIGITS);
    int randomNumber = generate_random_number(2, 10);

    cout << "Create object #1" << endl;
    clusterP object1(start, end);
    cout << "Querying object #1" << endl;
    object1.query(randomNumber);
    cout << "Mod(" << randomNumber << ")";
    cout << "     Min" << "    Max" << "    Matches" << endl;
    cout << "object #1  " << object1.getMinValue();
    cout << "     " << object1.getMaxValue();
    cout << "     " << object1.getNumberOfMatches() << endl;

    cout << "Create object #2 and move object #1 to object #2" << endl;
    clusterP object2 = move(object1);
    if(!object1.getActive())
        cout << "Object #1 is inactive now!!!" << endl;
    cout << "Querying object #2" << endl;
    cout << "Mod(" << randomNumber << ")";
    cout << "     Min" << "    Max" << "    Matches" << endl;
    cout << "object #2  " << object2.getMinValue();
    cout << "     " << object2.getMaxValue();
    cout << "     " << object2.getNumberOfMatches() << endl;
}

void test_heap_allocated_using_uniquePtr() {
    int start = generate_random_number(MIN_TWO_DIGITS, MAX_TWO_DIGITS);
    int end = generate_random_number(MIN_TWO_DIGITS, MAX_TWO_DIGITS);
    cout << "Create a unique pointer of clusterP object" << endl;
    unique_ptr<clusterP> uniquePtr1(new clusterP(end));
    vector<unique_ptr<clusterP>> clusterPVector;
    cout << "Add that unique pointer to a vector" << endl;
    clusterPVector.push_back(move(uniquePtr1));
    cout << "Add another unique pointer to a vector" << endl;
    clusterPVector.push_back(unique_clusterP_object(start,end));
    cout << "Remove a heap-allocated object from vector" << endl;
    clusterPVector.pop_back();
    cout << "Expecting vector size to be 1, got: " << clusterPVector.size() << endl;
}

void test_copying_via_call_by_value(shared_ptr<clusterP> input) {
    int randomNumber = generate_random_number(2, 10);
    cout << "Querying until sharable clusterP object inactive" << endl;
    cout << "Mod(" << randomNumber << ")";
    cout << "     Min" << "    Max" << "    Matches" << endl;
    while(input->getActive()) {
        input->query(randomNumber);
        cout << "           " << input->getMinValue();
        cout << "     " << input->getMaxValue();
        cout << "     " << input->getNumberOfMatches() << endl;
    }
    cout << "sharable clusterP object is inactive now!!!" << endl;
}

int main() {
    cout << "--------------- Program Start ---------------" << endl;
    cout << "-- Testing Key Functionalities of clusterP object --" << endl;
    test_key_functionalities();

    cout << "-- Testing assignment operator --" << endl;
    test_assignment_operator();

    cout << "-- Testing copy operator --" << endl;
    test_copy_operator();

    cout << "-- Testing move semantics --" << endl;
    test_move_semantics();

    cout << "-- Using unique_ptr to reference heap-allocated clusterP objects --" << endl;
    test_heap_allocated_using_uniquePtr();

    cout << "-- Demonstrating copying of clusterP objects via call by value --" << endl;
    cout << "create sharable clusterP object" << endl;
    shared_ptr<clusterP> shareClusterP = shareable_clusterP_object(MIN_TWO_DIGITS,MAX_TWO_DIGITS);
    cout << "create a reference of sharable clusterP object" << endl;
    shared_ptr<clusterP> shared_reference(shareClusterP);
    test_copying_via_call_by_value(shareClusterP);

    cout << "Checking the state of reference object" << endl;
    if(!shared_reference->getActive()) {
        cout << "reference of sharable clusterP object is inactive!!!" << endl;
    }
    cout << "--------------- Program Stop ---------------" << endl;
    return 0;
}