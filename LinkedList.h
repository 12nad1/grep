/*
 * LinkedList.h
 *
 * Interface for a Linked List class.
 *
 * COMP15 
 * Spring 2018
 * Project 2
 * Maxwell Kaye
 *
 */

#include <iostream>
#include <exception>
#include "NodeType.h"
using namespace std;

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

const int FAIL = -1;

class FullList : public exception{
public:
    const char * what() const throw() {return "Oh no, the list is full!\n";}; 
};

class EmptyList : public exception{
public:
    const char * what() const throw() {return "Sad, the list is empty!\n";}
};

template<class E> class LinkedList
{
 public:
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList &);
    LinkedList & operator =(const LinkedList &);

	void delete_value_at(int);

	void insert(E);
	E get_value_at(int) const;
	int get_length() const;
	void make_empty();
    E find(E, bool &) const;

    bool is_empty() const;
    bool is_full() const;

  private:
	NodeType<E> *head;
};

#endif
