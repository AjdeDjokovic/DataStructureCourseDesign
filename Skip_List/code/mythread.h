#ifndef MYTHREAD_H
#define MYTHREAD_H
#include "skiplist.h"
#include <QThread>
#include <QString>
#include <QStringList>
#include <utility>
#include <QList>
#include <QTime>

class myThread : public QThread
{
    Q_OBJECT
public:
    myThread();
    void threadBegin();
    void threadPause();
    void stopThread();
    void set(skipList<int,QString>*,int,int);
private:
    skipList<int,QString>* slist;
    int m_seq = 0;
    int maxKey;
    bool m_Paused = true;
    bool m_stop = false;
protected:
    void run() Q_DECL_OVERRIDE;
signals:
    void result(QString*);
};

#endif // MYTHREAD_H
