#include "testthread.h"

testThread::testThread()
{

}

void testThread::stopThread()
{
    m_stop = true;
}

void testThread::set(skipList<int,QString>* slist,int count)
{
    this->slist = slist;
    this->count = count;
}

void testThread::run()
{
    int rank = 0;
    m_stop = false;
    struct timeval tpstart,tpend;
    float timeuse1,timeuse2,timeuse3;
    QString str;
    QTime timedebuge;
    while(!m_stop)
    {
        rank++;
        gettimeofday(&tpstart,NULL);
        for(int i = 0;i < count;i++)
                slist->randomInsert();
        gettimeofday(&tpend,NULL);
        timeuse1=(1000000*(tpend.tv_sec-tpstart.tv_sec) + tpend.tv_usec-tpstart.tv_usec)/1000.0;

        gettimeofday(&tpstart,NULL);
        for(int i = 0;i < count;i++)
                slist->randomSearch();
        gettimeofday(&tpend,NULL);
        timeuse2=(1000000*(tpend.tv_sec-tpstart.tv_sec) + tpend.tv_usec-tpstart.tv_usec)/1000.0;

        gettimeofday(&tpstart,NULL);
        for(int i = 0;i < count;i++)
                slist->randomErase();
        gettimeofday(&tpend,NULL);
        timeuse3=(1000000*(tpend.tv_sec-tpstart.tv_sec) + tpend.tv_usec-tpstart.tv_usec)/1000.0;

//         str = "第" + QString::number(rank) + "次测试总用时" + QString::number(timeuse1+timeuse2+timeuse3)+ "ms\t" + "插入用时:"+QString::number(timeuse1) +"ms\t" + "查找用时:" + QString::number(timeuse2) +"ms\t" + "删除用时:" + QString::number(timeuse3) +"ms";
        if(timeuse1!=0 && timeuse2 != 0 && timeuse3 != 0)
        {
            str = "此时节点总数："+ QString::number(slist->size()) + "\t\t" +"第" + QString::number(rank) + "次测试总用时" + QString::number(timeuse1+timeuse2+timeuse3)+ "ms\t" + "插入用时:"+QString::number(timeuse1) +"ms\t" + "查找用时:" + QString::number(timeuse2) +"ms\t" + "删除用时:" + QString::number(timeuse3) +"ms";
            emit result(&str);
        }

//        timedebuge.start();
//        for(int i = 0;i < count;i++)
//                slist->randomInsert();
//        float time1 = timedebuge.elapsed();

//        timedebuge.start();
//        for(int i = 0;i < count;i++)
//                slist->randomErase();
//        float time2 = timedebuge.elapsed();

//        timedebuge.start();
//        for(int i = 0;i < count;i++)
//                slist->randomSearch();
//        float time3 = timedebuge.elapsed();

//        str = "第" + QString::number(rank) + "次测试总用时" + QString::number(time1+time2+time3)+ "ms\t" + "插入用时:"+QString::number(time1) +"ms\t" + "查找用时:" + QString::number(time2) +"ms\t" + "删除用时:" + QString::number(time3) +"ms";


        msleep(100);
    }
    quit();
}
