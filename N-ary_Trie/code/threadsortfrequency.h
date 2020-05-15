#ifndef THREADSORTFREQUENCY_H
#define THREADSORTFREQUENCY_H

#include <QThread>
#include "trie.h"
#include <QDir>
#include <QDataStream>
#include <QFile>
#include "completewinnertree.h"
#include "firstplayer.h"
#include "string.h"


class threadSortFrequency : public QThread
{
    Q_OBJECT
public:
    threadSortFrequency();
    void set(Trie*,TrieNode*);
protected:
    void run() Q_DECL_OVERRIDE;
private:
    Trie * trie;
    TrieNode * node;
signals:
    void result(QString);
    void update(int,int);
};

#endif // THREADSORTFREQUENCY_H
