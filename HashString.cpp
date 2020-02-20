/*
 * HashString.cpp
 *
 * Implementation for s string that's stored
 * in a hash table.
 *
 * COMP15
 * Spring 2018
 * Project 2
 * Maxwell Kaye
 *
 */

#include <unordered_set>
#include <functional>   // c++ hash function
#include <string>
#include "HashString.h"
#include "LinkedList.h"

// Default constructor
HashString::HashString()
{
  word = "";
  line = "";
  path = "";
  line_num = 0;

}

// Parameterized constructor: the string itself
HashString::HashString(string s, string l, string p, int ln)
{
  word = s;
  line = l;
  line_num = ln;
  path = p;
}

// Return the word
string HashString::get_word() const
{
  return word;
}

// Set the word to the given value
void HashString::set_word(string s)
{
  word = s;
}

// Return the line
string HashString::get_line() const
{
  return line;
}

// Set the line to the given value
void HashString::set_line(string l)
{
  line = l;
}

// Return the line number
int HashString::get_line_num() const
{
  return line_num;
}

// Set the line to the given value
void HashString::set_line_num(int ln)
{
  line_num = ln;
}

// Return the path
string HashString::get_path() const
{
  return path;
}

// Set the path to the given value
void HashString::set_path(string p)
{
  path = p;
}

// gets length of the list
int HashString::list_length() const
{
  return others.get_length();
}

// Return the next path
HashString HashString::get_next()
{
  int size = others.get_length();
  HashString hs = others.get_value_at(size - 1);
  others.delete_value_at(0);
  return hs;
}

// Function insert_path
// Does: inserts another path into the list of paths
// Inputs: string, the path
// Outputs: none
void HashString::insert_hash_string(HashString hs)
{
  others.insert(hs);
}

// is_empty, used to determine an unset value
// in the hash table
bool HashString::is_empty() const
{
  return (word == "");
}


// Overloaded operators
bool operator == (const HashString &h1, const HashString &h2)
{
  return (h1.word == h2.word);
}

bool operator !=  (const HashString &h1, const HashString &h2)
{
  return (h1.word != h2.word);
}

// Hash Functions

// Function hash_value
// Does: returns the hash value of this HashString object
// Uses the built in c++ hash function
// Inputs: None
// Outputs: size_t
size_t HashString::hash_value() const
{
  hash<string> str_hash;
  return str_hash(word);
}

// Function print
// Does: Prints word, line, and line number, then recursively
// calls itself on the list
// Inputs: none
// Returns: none
void HashString::print() const
{
  cout << "WORD: " << word << endl;
  cout << "LINE: " << line << endl;
  cout << "LINE NUM: " << line_num << endl;

  for (int i = 0; i < others.get_length(); i++)
  {
    others.get_value_at(i).print();
  }

}
