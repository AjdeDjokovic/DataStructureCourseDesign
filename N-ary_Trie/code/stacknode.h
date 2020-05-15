#ifndef STACKNODE_H
#define STACKNODE_H

#include "trienode.h"
#include <QPointF>

class stackNode
{
public:
    TrieNode * node;
    int queue;
    QPointF parentPos;
    int level;
    stackNode(TrieNode * node,QPointF parentPos,int queue,int level)
    {
        this->node = node;
        this->parentPos = parentPos;
        this->queue = queue;
        this->level = level;
    }
};

#endif // STACKNODE_H
