#include "adjustthread.h"

adjustThread::adjustThread()
{

}

void adjustThread::set(skipList<int,QString>* slist)
{
    this->slist = slist;
}

void adjustThread::run()
{
    skipList<int,QString>* list = slist->adjust();
    delete slist;
    emit result(list);
    quit();
}
