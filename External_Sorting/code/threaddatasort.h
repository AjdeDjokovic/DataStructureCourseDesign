#ifndef THREADDATASORT_H
#define THREADDATASORT_H

#include <QThread>
#include <QString>
#include <QFile>
#include <QDataStream>
#include "completewinnertree.h"
#include "firstplayer.h"
#include <QList>
#include "player.h"
#include <cstring>


class threadDataSort : public QThread
{
    Q_OBJECT
public:
    threadDataSort();
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

#endif // THREADDATASORT_H
