#include "mythread.h"

int generateRandomInteger(int min, int max)
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

QString getRandomString()
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


myThread::myThread()
{

}

void myThread::threadBegin()
{
    m_Paused = false;
}

void myThread::threadPause()
{
    m_Paused = true;
}

void myThread::stopThread()
{
    m_stop = true;
}

void myThread::set(skipList<int,QString>* slist,int key,int seq)
{
    this->slist = slist;
    maxKey = key;
    m_seq = seq;
}

void myThread::run()
{
    m_stop = false;
    std::pair<int,QString>* thePair = new std::pair<int,QString>();
    for(int i = 0;i < m_seq;i++)
    {
        int key = generateRandomInteger(1,maxKey - 1);
        QString str = getRandomString();
        thePair->first = key;
        thePair->second = str;
        slist->insert(*thePair);
    }
    QString* str = slist->out();
    delete thePair;
    emit result(str);
    quit();
}
