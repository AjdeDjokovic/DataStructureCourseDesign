#ifndef ADJUSTTHREAD_H
#define ADJUSTTHREAD_H

#include <skiplist.h>
#include <QThread>

class adjustThread : public QThread
{
    Q_OBJECT
public:
    adjustThread();
    void set(skipList<int,QString>*);
protected:
    void run() Q_DECL_OVERRIDE;
private:
    skipList<int,QString>* slist;
signals:
    void result(skipList<int,QString>*);
};

#endif // ADJUSTTHREAD_H
