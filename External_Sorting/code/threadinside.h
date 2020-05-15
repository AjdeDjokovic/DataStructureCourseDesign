#ifndef THREADINSIDE_H
#define THREADINSIDE_H

#include <QThread>
#include <algorithm>
#include "completewinnertree.h"
#include <QFile>
#include <QDataStream>
#include "firstplayer.h"
#include "player.h"
#include <cstring>

class threadInside : public QThread
{
    Q_OBJECT
public:
    threadInside();
    void set(QString,QString,int);
protected:
    void run() Q_DECL_OVERRIDE;
private:
    QString fileName;
    QString curPath;
    int storage;
signals:
    void result();
    void update(int,int);
    void test(qint64,qint64);

};

#endif // THREADINSIDE_H
