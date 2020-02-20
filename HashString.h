/*
 * HashString.h
 *
 * Interface for a HashString class.
 * We're making a Hash Table of HashString objects.
 *
 * COMP15
 * Spring 2018
 * Project 2
 * Maxwell Kaye
 *
 */

#include <string>
#include "LinkedList.h"
using namespace std;

#ifndef HASH_STRING_H_
#define HASH_STRING_H_

class HashString
{
private:
    string word;
    string line;
    string path;
    int line_num;
    LinkedList<HashString> others;

public:
    HashString();
    HashString(string, string, string, int);

    string get_word() const;
    void set_word(string);  

    string get_line() const;
    void set_line(string);  

    int get_line_num() const;
    void set_line_num(int);    

    string get_path() const;
    void set_path(string);  

    int list_length() const;
    HashString get_next();
    void insert_hash_string(HashString);  

    size_t hash_value() const;
    bool is_empty() const;

    void print() const;

    friend bool operator == (const HashString &, const HashString &);
    friend bool operator != (const HashString &, const HashString &);
};

#endif

