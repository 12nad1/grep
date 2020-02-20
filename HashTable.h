/*
 * HashTable.h
 *
 * Interface for a Hash Table class.
 *
 * COMP15 
 * Spring 2018
 * Project 2
 * Maxwell Kaye
 * 
 */

#include <iostream>

using namespace std;

#ifndef HASH_H_
#define HASH_H_

const int MAX_ITEMS = 20000;

template <class E> class Hash
{
public:
    Hash();

    bool is_full() const;
    bool is_empty() const;

    void retrieve(E&, bool&) const;
    void insert(E);

    int open_slots() const;

    void print() const;
    
private:
    int length;
    E info[MAX_ITEMS];
};

#endif