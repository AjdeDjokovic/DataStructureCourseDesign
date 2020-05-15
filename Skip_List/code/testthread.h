#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QThread>
#include "skiplist.h"
#include <QDebug>
#include <sys/time.h>
#include <QTime>

class testThread : public QThread
{
    Q_OBJECT
public:
    testThread();
    void stopThread();
    void set(skipList<int,QString>*,int);
private:
    int count;
    skipList<int,QString>* slist;
    bool m_stop = false;
protected:
    void run() Q_DECL_OVERRIDE;
signals:
    void result(QString*);
};

#endif // TESTTHREAD_H
