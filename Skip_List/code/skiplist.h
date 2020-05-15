#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "skipnode.h"
#include <stdlib.h>
#include <cmath>
#include <QString>
#include <QStringList>
#include <QtWidgets/QMessageBox>
#include <qinputdialog.h>
#include <QTime>

template<class K,class E>
class skipList
{
    int maxPairs;    //最大元素个数
    float prob;      //随机级数的浮点数
    float cutOff;    //用来确定层数
    int levels;      //当前最大非空链表
    int dSize;       //当前节点个数
    int maxLevel;    //级数上限
    skipNode<K,E>* tailNode;    //尾节点指针
    skipNode<K,E>** last;       //查找时所用i层最后节点
public:
    skipNode<K,E>* headerNode;
    K tailKey;
    skipList(K largeKey,int maxPairs,float prob);
    ~skipList();
    std::pair<const K,E>* find(const K& thekey) const;
    int level() const;
    skipNode<K,E>* search(const K& theKey) const;
    bool insert(const std::pair<const K,E>& thePair);
    bool erase(const K& theKey);
    QString* out() const;
    bool earseMin();
    bool earseMax();
    void randomInsert();
    void randomErase();
    void randomSearch();
    QString getRandomString();
    int generateRandomInteger(int min, int max);
    skipList<K,E>* adjust();
    int size();
};

template<class K,class E>
QString skipList<K,E>::getRandomString()
{
    int max = generateRandomInteger(1,10);
    QString tmp = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    QString str = "";
    static bool seedStatus;
    if (!seedStatus)
    {
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        seedStatus = true;
    }
    for(int i = 0;i < max;i++)
    {
        int ir = qrand() % tmp.length();
        str[i] = tmp.at(ir);
    }
    return str;
}

template<class K,class E>
int skipList<K,E>::generateRandomInteger(int min, int max)
{
    Q_ASSERT(min < max);
    // 加入随机种子。种子是当前时间距离0点0分0秒的秒数。
    // 每次启动程序，只添加一次种子，以做到数字真正随机。
    static bool seedStatus;
    if (!seedStatus)
    {
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        seedStatus = true;
    }
    int nRandom = qrand() % (max - min);
    nRandom = min + nRandom;

    return nRandom;
}

template<class K,class E>
void skipList<K,E>::randomInsert()
{
    std::pair<const K,E>* thePair = new std::pair<const K,E>(generateRandomInteger(1,tailKey - 1),getRandomString());
    insert(*thePair);
    delete thePair;
}

template<class K,class E>
void skipList<K,E>::randomErase()
{
    erase(generateRandomInteger(1,tailKey - 1));
}

template<class K,class E>
void skipList<K,E>::randomSearch()
{
    search(generateRandomInteger(1,tailKey - 1));
}

template<class K,class E>
skipList<K,E>::skipList(K largeKey,int maxPairs,float prob)
{
    this->maxPairs =maxPairs;
    this->prob = prob;
    cutOff = prob * RAND_MAX;
    maxLevel = (int)ceil(logf((float) maxPairs)/logf(1/prob)) - 1;
    levels = 0;
    dSize = 0;
    tailKey = largeKey;

    std::pair<K,E> tailPair;
    tailPair.first = tailKey;
    headerNode = new skipNode<K,E> (tailPair,maxLevel + 1);
    tailNode = new skipNode<K,E> (tailPair,0);
    last = new skipNode<K,E>* [maxLevel + 1];

    for(int i = 0;i <= maxLevel;i++)
        headerNode->next[i] = tailNode;
}

template<class K,class E>
std::pair<const K,E>* skipList<K,E>::find(const K& thekey) const
{
    if(thekey >= tailKey)
        return NULL;
    skipNode<K,E>* beforeNode = headerNode;
    for(int i = levels;i >= 0;i--)
        while(beforeNode->next[i]->element.first < thekey)
            beforeNode = beforeNode->next[i];

    if(beforeNode->next[0]->element.first == thekey)
        return &beforeNode->next[0]->element;

    return NULL;
}

template<class K,class E>
int skipList<K,E>::level() const
{
    int lev = 0;
    while(rand() <= cutOff)
        lev++;
    return (lev <= maxLevel) ? lev : maxLevel;
}

template<class K,class E>
skipNode<K,E>* skipList<K,E>::search(const K& theKey) const
{
    skipNode<K,E>* beforeNode = headerNode;
    for (int i = levels;i >= 0;i--)
    {
        while(beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];
        last[i] =beforeNode;
    }
    return beforeNode->next[0];
}

template<class K,class E>
bool skipList<K,E>::insert(const std::pair<const K,E>& thePair)
{
    if(thePair.first >= tailKey)
    {
        return false;
    }

    skipNode<K,E>* theNode = search(thePair.first);
    if(theNode->element.first == thePair.first)
    {
        theNode->element.second = thePair.second;
        return true;
    }

    int theLevel = level();

//    if(theLevel > levels)
//    {
//        theLevel = ++levels;
//        last[theLevel] = headerNode;
//    }

    if(theLevel > levels)
    {
        for(int i = theLevel;i > levels;i--)
            last[i] = headerNode;
        levels = theLevel;
    }

    skipNode<K,E>* newNode = new skipNode<K,E>(thePair,theLevel + 1);
    for(int i = 0;i <= theLevel;i++)
    {
        newNode->next[i] = last[i]->next[i];
        last[i]->next[i] = newNode;
    }

    dSize++;
    return true;
}

template<class K,class E>
bool skipList<K,E>::erase(const K& theKey)
{
//    if(theKey >= tailKey)
//        return;
    skipNode<K,E>* theNode = search(theKey);
    if(theNode->element.first != theKey)
        return false;

    for(int i = 0;i <= levels && last[i]->next[i] == theNode;i++)
        last[i]->next[i] = theNode->next[i];

    while(levels > 0 && headerNode->next[levels] == tailNode)
        levels--;

    delete theNode;
    dSize--;
    return true;
}

template<class K,class E>
QString* skipList<K,E>::out() const
{
    QString* str = new QString();
    for(int i = levels;i >= 0;i--)
    {
        skipNode<K,E>* theNode = headerNode;
        *str += "headerNode-->";
        while (theNode->next[i] != tailNode)
        {
            std::pair<K,E> thePair = theNode->next[i]->element;
            theNode = theNode->next[i];
            *str += "(" + QString::number(thePair.first) + "," + thePair.second + ")-->";
        }
        *str += "tailNode\n\n";
    }
    return str;
}

//template<class K,class E>
//void skipList<K,E>::clear()
//{
//    dSize += 2;
//    skipNode<K,E>* nextNode;
//    while(headerNode != tailNode)
//    {
//        nextNode = headerNode->next[0];
//        delete headerNode;
//        headerNode = nextNode;
//        dSize--;
//    }
//    delete tailNode;
//    dSize--;
//}

template<class K,class E>
skipList<K,E>::~skipList()
{
    skipNode<K,E>* nextNode = headerNode->next[0];
    delete headerNode;
    headerNode = nextNode;
    while(headerNode != tailNode)
    {
        nextNode = headerNode->next[0];
        delete headerNode;
        headerNode = nextNode;
        dSize--;
    }
    delete tailNode;
    delete []last;
}

template<class K,class E>
bool skipList<K,E>::earseMin()
{
    skipNode<K,E>* nextNode = headerNode->next[0];
    if(nextNode == tailNode)
        return false;
    erase(nextNode->element.first);
    return true;
}

template<class K,class E>
bool skipList<K,E>::earseMax()
{
    skipNode<K,E>* nextNode = headerNode->next[0];
    if(nextNode == tailNode)
        return false;
    while(nextNode->next[0] != tailNode)
        nextNode = nextNode->next[0];
    erase(nextNode->element.first);
    return true;
}

template<class K,class E>
skipList<K,E>* skipList<K,E>::adjust()
{
    skipList<K,E>* newList = new skipList<K,E>(tailKey,maxPairs,prob);
    skipNode<K,E>* nextNode = headerNode->next[0];
    while(nextNode != tailNode)
    {
        newList->insert(nextNode->element);
        nextNode = nextNode->next[0];
    }
    return newList;
}

template<class K,class E>
int skipList<K,E>::size()
{
    return dSize;
}
#endif // SKIPLIST_H


//213:asdzxc 5675:asas 1:asdsa 3:xzcxzc 5:zxcxza
