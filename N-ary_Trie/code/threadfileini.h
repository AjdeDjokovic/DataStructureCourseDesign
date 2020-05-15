#ifndef THREADFILEINI_H
#define THREADFILEINI_H

#include <QThread>
#include "trie.h"
#include <QFile>
#include <QTextStream>
#include <ctype.h>
#include <cstring>

class threadFileIni : public QThread
{
    Q_OBJECT
public:
    threadFileIni();
    void set(Trie * trie,QString fileName);
protected:
    void run() Q_DECL_OVERRIDE;
private:
    Trie * trie;
    QString fileName;
signals:
    void result();
};

#endif // THREADFILEINI_H
