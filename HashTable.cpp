/*
 * HashTable.cpp
 * 
 * Implementation for Hash Table class
 *
 * COMP15
 * Spring 2018
 * Project 2
 * Maxwell Kaye
 *
 */

#include <string>
#include "HashTable.h"
#include "HashString.h"
#include "LinkedList.h"
using namespace std;

// Default constructor
template<class E>
Hash<E>::Hash()
{
    length = 0;
}

// Function is_full(), const
// Parameters: none
// Returns: bool
// Does: Checks if array (static) is full
template<class E>
bool Hash<E>::is_full() const
{
    return (length == MAX_ITEMS);
}

// Function is_empty(), const
// Parameters: none
// Returns: bool
// Does: Checks if array is emtpy
template<class E>
bool Hash<E>::is_empty() const 
{
    return (length == 0);
}

// Function: retrieve
// Parameters: Item (E) &, bool &
// Returns: int, the number of collisions
// Does: Gets the hash value of the given item.
//       If the item is found at that position, return it.
//       If not, look for it in other positions in the array.
//       Hash table resolves collisions with linear probing.
template<class E>
void Hash<E>::retrieve(E &item, bool &found) const
{
    if (is_empty())
        return;

    size_t location = item.hash_value() % MAX_ITEMS;

    found = (info[location] == item);
    if (found)
        item = info[location];
}

// Function: insert
// Parameters: Item (E)
// Returns: void
// Does: Gets the hash value of the given item.
//       If that position is available, insert the item.
//       If not, insert the item in the next attribute of the
//       string that is there, using chaining.
template<class E>
void Hash<E>::insert(E item)
{
    if (is_full())
        return;

    size_t location = item.hash_value() % MAX_ITEMS;
    
    if (info[location].is_empty())
    {
        info[location] = item;
        length++;
    }
    else
    {
        info[location].insert_hash_string(item);
    }
}

// Function: open_slots
// Parameters: None, const
// Returns: int, the number of empty slots in the array
// Does: Determines how 'full' our hash table is.
//       Iterates through each space and counts the number
//       that are empty. Ideal hash table is full!
template<class E>
int Hash<E>::open_slots() const
{
    int open = 0;
    for (size_t i = 0; i < MAX_ITEMS; i++)
    {
        if (info[i].is_empty())
            open++;
    }
    return open;
}

// Function print
// Inputs: none
// Outputs: none
// Does: prints the hash table
template<class E>
void Hash<E>::print() const
{
    bool done = false;
    int count = 0;
    for (int i = 0; !done; i++)
    {
        if (!info[i].is_empty())
        {
            info[i].print();
            count++;
        }

        if (count == length)
            done = true;
    }
}




template class Hash<HashString>;
