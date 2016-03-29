/************************************************************************************
Title: TestChain.cpp
Author: Emma Kimlin
Created on: February 6th, 2016
Description: Main program with two test functions that test Chain.h.
Purpose: To make sure everything implemeneted in Chain.h runs without errors.
Build with: make all 
Modifications: none
************************************************************************************/

#include "Chain.h"
#include <iostream>
using namespace std;
/**
  * Tests the following functions and constructors: ReadChain(), default constructor, one-paramter constructor, 
  * overloaded << operator, copy constructor, copy assignment operator, move constructor, move assignment operator, 
  * destructor.
 */
void TestPart1();
/**
  * Tests the following functions and constructors: default constructor, ReadChain(), 
  * overloaded + operators, overloaded [] operators.
 */
void TestPart2();


// Sample main for program queryTrees

int main(int argc, char **argv) {
  TestPart1();
  TestPart2();
  return 0;
}

void TestPart1() {
    Chain<int> a, b; // Two empty Chains are created
    cout << a.Size() << " "<< b.Size() << endl; // yields 0 0
    
    Chain<int> d{7}; // A chain containing 7 should be created.
    cout << "d contains " << d << endl; // Should just print [7]
    cout << d.Size() << endl;
    
    a.ReadChain(); // User enters a chain, for example [10 30 -1 2]
    cout << "a contains: " << a; // Output should be what user entered.

    b.ReadChain();
    cout << "b contains: " << b;
    
    Chain<int> c{a}; //Calls copy constructor for c
    cout << "Copy contructor called. c was created and should match a. c contains: " << c << endl;
    cout << " And a should be unchanged. a contains: " << a << endl;
    
    a = b; //Should call the copy assignment operator for a
    cout << "Copy Assignment operator called. a should match b now. a contains: " << a << endl;
    
    
    Chain<int> e = std::move(c); // Move constructor for e.
    cout << "Move constructor for e called. c should have been destroyed. c contains: " << c << endl;
    cout << "e was created. e should hold what c used to hold. e contains: " << e << endl;
    
    a = std::move(e); //Move assignment operator for a
    cout << "Move assignment operator called. e should have been destroyed. e contains: " << e << endl;
    cout << "a should hold what e used to hold. a contains: " << a << endl;
} // Destructors will be called.

void TestPart2() {
    Chain<string> a, b;
    
    a.ReadChain(); // User provides input for Chain a.
    cout << "a contains " << a;
    cout << "a is size " << a.Size() << endl;
    b.ReadChain(); // User provides input for Chain b. cout << b << endl;
    cout << "b contains " << b;
    cout << "b is size "<< b.Size() << endl;
    
    cout << a + b << endl; // Concatenates the two Chains.
    
    Chain<string> d = a + b;
    cout << "d created. d contains: " << d << endl;
    
    cout << d + "hi_there" << endl; // Adds an element to the end of d;
    
    cout << a[2] << endl; // Should print the 3rd element. Throw an exception (or even abort()) if is out of
                            // range.
    b[1] = "b_string"; // Should change the 2nd element to “b_string”
    cout << b;
    b[0] = "a_string";
    cout << b;
} // End of TestPart2