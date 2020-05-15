#ifndef SKIPNODE_H
#define SKIPNODE_H

#include <utility>

template <class K,class E>
struct skipNode
{
    typedef std::pair<const K,E> pairType;

    pairType element;
    skipNode<K,E> **next;

    skipNode(const pairType & thePair,int size):element(thePair)
    {
        next = new skipNode<K,E>* [size];
    }
};

#endif // SKIPNODE_H
