/************************************************************************************
 Title: Chain.h
 Author: Emma Kimlin
 Created on: February 6th, 2016
 Description: This class holds a series of items in a "chain", with each item seperated by a space. The user can output the items in the chain as a whole, and find the size in bytes of the chain.
 Purpose: To become familiar with the "big five" and overloading assignment operators. 
 Modifications:
    February 13th, Emma Kimlin: Implemented constructors and overloaded << operator
    Februrary 17th, Emma Kimlin: Implemented overloaded [] and + operators
 ************************************************************************************/
#ifndef CSCI335_HOMEWORK1_CHAIN_
#define CSCI335_HOMEWORK1_CHAIN_
#include <cstddef>
#include <array>
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

template<typename Object>
class Chain {
public:
    /**
      * DEFAULT CONSTRUCTOR
     */
    explicit Chain() : size_(0), array_(NULL) {}

    /**
      * ONE-PARAMETER CONSTRUCTOR
     */
    explicit Chain(const Object & obj)
    {
        size_ = sizeof(Object);
        array_ = new Object[1] {obj};
    }

    /** 
      * DESTRUCTOR 
     */
    ~Chain()
    {
        if (array_ != nullptr) {
            delete [] array_;
            array_ = nullptr;
        }
    }

    /**
      * Copy Constructor is used when returning or passing obj by value/initializing obj to state of rhs.
      * Pre-Condition: rhs is a lvalue.
      * Post-Condition: A new object has been created that is a mirror image of rhs. rhs is unaltered.
     */
    Chain(const Chain &rhs) {
        size_ = rhs.size_;
        if (size_ != 0) {
            array_ = new Object[size_];
            std::copy(rhs.array_, rhs.array_+size_, array_);
        } else
            array_ = nullptr; //rhs doesn't contain anything; neither will this
    }

    /**
      * Move Constructor is used when returning or passing obj by value/initializing obj to state of rhs.
      * Pre-Condition: rhs is an rvalue.
      * Post-Condition: A new object has been created that is a mirror image of rhs. rhs is set to NULL.
     */
    Chain(Chain &&rhs) {
        std::swap(size_, rhs.size_);
        std::swap(array_, rhs.array_); //now array_ of calling obj points to same place as rhs so it references rhs's values
        //destructor will clean up rhs 
    }

    /** 
      * Copy Assignment Operator is called for statements such as lhs=rhs
      * Pre-Condition: rhs is a lvalue.
      * Post-Condition: lhs is a mirror image of rhs. rhs is unaltered.
     */
    Chain& operator=(const Chain &rhs)
    {
        if (this != &rhs) { 
            if (size_ != rhs.size_) {
                size_ = rhs.size_;
                delete [] array_;
                array_ = new Object[size_];
            }
            std::copy(rhs.array_, rhs.array_ + size_, array_);
        }
        return *this;
    }
    
    /** 
      * The Move Assignment Operator is called for statements such as lhs=rhs
      * Pre-Condition: rhs is an rvalue.
      * Post-Condition: lhs is a mirror image of rhs. rhs is set to NULL
     */
    Chain& operator=(Chain &&rhs) {
        if (this != &rhs) {
            std::swap(size_, rhs.size_);
            std::swap(array_, rhs.array_);
            delete [] rhs.array_;
            rhs.array_ = nullptr;
        }
        return *this;
    }

    /**
      * Overloaded output operator allows user to output the entire contents of a chain to screen.
      * Post Condition: Values in chain are printed to screen with each value separated by a space.
     */
    friend std::ostream& operator<< (std::ostream& os, const Chain& chain) {
        if (chain.array_ != nullptr) {
            size_t obj_size = sizeof(Object);
            size_t num_entries = chain.size_ /obj_size; //found out how many entries are in chain
            for (int i = 0 ; i < num_entries; i++)
                os << chain[i] << " ";
        }
        os << std::endl;
        return os;
    }

    /**
      * Overloaded Additition Operator allows user to concatenating two chains.
      * Pre-Condition: User wishes to add two Chains, chain1 and chain2. The lhs of the addition operator will act as the calling object to this function.
      * Post-Condition: A new chain is returned that stores chain1's values followed by chain2's values.
    */
    Chain operator+(const Chain &rhs) {
        int num_obj_this = size_/sizeof(Object);
        int num_obj_rhs = rhs.size_/sizeof(Object);
        
        int num_obj_total = num_obj_this + num_obj_rhs;
        Object* new_ptr = new Object[num_obj_total]; //make an array that stores both chains
        for (int i = 0; i < num_obj_this; i++)
            new_ptr[i] = array_[i]; //store calling object's chain into new object's chain
        int j = 0;
        for (int i = num_obj_this; i < num_obj_total; i++)
            new_ptr[i] = rhs[j++]; //store rhs object's chain into latter half of                             new object's chain

        size_t total_size = num_obj_total*sizeof(Object);
        return Chain(total_size, new_ptr);
    }

    /**
      * The Overloaded Addition Operator allows user to concatenate an Object to the end of an existing Chain<Object>.
      * Pre-Condition: Object must be the rhs operand of addition operation. Chain must be lhs operand and will act as the calling object.
      * Post-Condition: A new chain is returned that stores chain1's values followed by obj
     */ 
    Chain operator+(const Object &obj) const {
        Chain<Object> temp{obj}; //create a temp chain to contain the obj
        Chain<Object> new_obj = *this + temp; //create new object to concatenate temp and calling obj
        return new_obj;
    }

    /**
      * Overloaded [] operator references values in the array of a Chain. This allows programmer to refer to the array in Chain c by typing "c[index]" instead of "c.array_[i]". This function checks to make sure index provided is in range. If not, will abort the process.
      * Pre-Condition: Chain is not const.
     */
    Object& operator[] (int i) {
        if ((i < 0) || (i >= size_)) {
            std::cout << "Error: Index is out of range." << std::endl;
            std::abort();
        } else
            return array_[i];
    }

    /**
      * Purpose: Overloaded [] operator references values in the array of a Chain. This allows programmer to refer to the array in Chain c by typing "c[index]" instead of "c.array_[i]". This function checks to make sure index provided is in range. If not, will abort the process.
      * Pre-Condition: Chain is const.
     */
    const Object& operator[] (int i) const {
        if ((i < 0) || (i >= size_)) {
            std::cout << "Error: Index is out of range." << std::endl;
            std::abort();
        } else
            return array_[i];
    }
    
    size_t Size() const { return size_; }
    /**
      * Read user input off of the command line and store it as an array within the calling object. It will overwrite previous data in Chain.
      * Pre-Condition: Calling chain contains trivial information that can be overwritten. 
      * Post-Condition: Calling chain is updated to store values provided by user and size_ is updated.
     */
    void ReadChain() {
        delete [] array_; //delete previous contents to avoid memory leak where user inputs less than there was in chain to begin with.
        
        //Read user input into a string and make an array big enough to hold it all:
        std::string user_chain;
        getline(std::cin, user_chain);
        int num_inputs = find_num_inputs(user_chain);
        array_ = new Object[num_inputs];
      
        //Parse for values (separated by spaces) provided by user, and store in array_ using stringstream to convert each string of user input into correct type.
        std::string word;
        Object obj_input;
        int first_space = -1; //index of space before a word.
        int array_index = 0;
        for (int i = 0; i < user_chain.size(); i++) {
            if (user_chain[i] == ' ') {          //iterate through user_chain looking for spaces
                word = user_chain.substr(first_space + 1, i-(first_space +1));
                std::stringstream ss_input(word);
                ss_input >> obj_input; //convert input from string to template type
                array_[array_index++] = obj_input; //finally, store input into dynamic array
                first_space = i;
            } else if (i == user_chain.size()-1) {       //you have reached the end of the chain, but there won't be a space
                word = user_chain.substr(first_space + 1, i-first_space);
                std::stringstream ss_input(word);
                ss_input >> obj_input;
                array_[array_index++] = obj_input;
            }
        }
        size_ = num_inputs*sizeof(Object);
    }
    /**
      * Purpose: Find out how many inputs from a string provided by user, by counting spaces in between inputs. 
      * Pre-Condition: Assumes no space before and after chain and that each value is seperated by a space.
     */
    const int find_num_inputs(const std::string& user_chain) {
        int num_inputs = 1; //start with one, as num words = num spaces + 1
        for (std::string::const_iterator it = user_chain.begin(); it != user_chain.end(); ++it) {
            if (*it == ' ')
                num_inputs++;
        }
        return num_inputs;
    }

 private:
    std::size_t size_; //returns size of chain (array) in terms of bytes.
    Object *array_;
    explicit Chain(const size_t size, Object* obj_ptr) : size_(size), array_(obj_ptr) {} //FOR INTERNAL USE ONLY
};

#endif // CSCI_335_HOMEWORK1_CHAIN_




































