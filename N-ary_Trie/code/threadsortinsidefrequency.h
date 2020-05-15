#ifndef THREADSORTINSIDEFREQUENCY_H
#define THREADSORTINSIDEFREQUENCY_H

#include <QThread>
#include "trie.h"
#include <QDir>
#include <QDataStream>
#include <QFile>


class threadSortInsideFrequency : public QThread
{
    Q_OBJECT
public:
    threadSortInsideFrequency();
    void set(Trie*,TrieNode*);
protected:
    void run() Q_DECL_OVERRIDE;
private:
    Trie * trie;
    TrieNode * node;
signals:
    void result(QString);
    void update(int);
};

#endif // THREADSORTINSIDEFREQUENCY_H
