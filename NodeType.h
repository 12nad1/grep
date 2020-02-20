// Maxwell Kaye
// May 1, 2018
// NodeType.h


#ifndef NODE_TYPE_H_
#define NODE_TYPE_H_

template<class E>
struct NodeType
{
    E info;
    NodeType<E> *next;
};

#endif
