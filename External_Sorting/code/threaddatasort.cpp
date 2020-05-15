#include "threaddatasort.h"

threadDataSort::threadDataSort()
{

}

void threadDataSort::set(QString fileName,QString curPath,int storage)
{
    this->fileName = fileName;
    this->curPath = curPath;
    this->storage = storage;
}

//void threadDataSort::run()
//{
//    int fileCount = 1;
//    QString subFileName = curPath + "/sub/" + QString::number(fileCount);
//    QFile subFile(subFileName);
//    if(!subFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
//        return;
//    QDataStream subStream(&subFile);
//    subStream.setVersion(QDataStream::Qt_5_12);

//    QFile aFile(fileName);
//    if(!aFile.open(QIODevice::ReadOnly))
//        return;
//    QDataStream aStream(&aFile);
//    aStream.setVersion(QDataStream::Qt_5_12);

//    firstPlayer array[5001];
//    for(int i = 1;i <= 5000;i++)
//    {
//        aStream >> array[i].key;
//        array[i].queue = 1;
//    }
//    completeWinnerTree<firstPlayer> tree = completeWinnerTree<firstPlayer>(array,5000);
//    while(!aStream.atEnd())
//    {
//        int winner = tree.winner();
//        firstPlayer old = array[winner];
//        int oldKey = old.key;
//        int oldQueue = old.queue;
//        int newKey;
//        aStream >> newKey;
//        if(newKey > oldKey)
//            array[winner].key = newKey;
//        else {
//            array[winner].key = newKey;
//            array[winner].queue++;
//        }

//        tree.rePlay(winner);

//        if(oldQueue != fileCount)
//        {
//            fileCount++;
//            subFile.close();
//            subFileName = curPath + "/sub/" + QString::number(oldQueue);
//            QFile subFile(subFileName);
//            if(!subFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
//                return;
//            QDataStream subStream(&subFile);
//            subStream.setVersion(QDataStream::Qt_5_12);

//            subStream << oldKey;
//        }
//        else
//            subStream << oldKey;
//    }

//    for(int i = 0;i < 10000;i++)
//    {
//        int winner = tree.winner();
//        firstPlayer old = array[winner];
//        int oldKey = old.key;
//        int oldQueue = old.queue;
//        array[winner].key = INT_MAX;

//        tree.rePlay(winner);

//        if(oldQueue != fileCount)
//        {
//            subFile.close();
//            fileCount++;
//            subFileName = curPath + "/sub/" + QString::number(fileCount);
//            QFile subFile(subFileName);
//            if(!subFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
//                return;
//            QDataStream subStream(&subFile);
//            subStream.setVersion(QDataStream::Qt_5_12);

//            subStream << oldKey;
//        }
//        else
//            subStream << oldKey;
//    }

//    emit result();
//    quit();
//}


void threadDataSort::run()
{

    int fileCount = 0;
    QFile aFile(fileName);
    if(!aFile.open(QIODevice::ReadOnly))
        return;
    QDataStream aStream(&aFile);
    aStream.setVersion(QDataStream::Qt_5_12);



    qint64 fileSize = aFile.size();
    qint64 numberCount = fileSize / 8;
    qint64 now = 0;
    emit update(0,1);



    firstPlayer array[storage + 1];
    for(int i = 1;i <= storage;i++)
    {
        aStream >> array[i].key;
        array[i].queue = 1;
    }
    completeWinnerTree<firstPlayer> tree = completeWinnerTree<firstPlayer>(array,storage);

    while(!aStream.atEnd())
    {
        int winner = tree.winner();
        firstPlayer old = array[winner];
        qint64 oldKey = old.key;
        int oldQueue = old.queue;
        qint64 newKey;
        aStream >> newKey;
        if(newKey >= oldKey)
            array[winner].key = newKey;
        else {
            array[winner].key = newKey;
            array[winner].queue++;
        }

        tree.rePlay(winner);

        QString subFileName = curPath + "/sub/" + QString::number(oldQueue) + ".stm";
        QFile subFile(subFileName);
        if(!subFile.open(QIODevice::Append))
            return;
        QDataStream subStream(&subFile);
        subStream.setVersion(QDataStream::Qt_5_12);
        subStream << oldKey;
        now++;
        if(now % (numberCount / 100) == 0)
            emit update((int)(now * 100/ numberCount),1);
    }

    for(int i = 0;i < storage;i++)
    {
        int winner = tree.winner();
        firstPlayer old = array[winner];
        qint64 oldKey = old.key;
        int oldQueue = old.queue;
        fileCount = oldQueue;
        array[winner].key = INT64_MAX;
        array[winner].queue = INT_MAX;

        tree.rePlay(winner);

        QString subFileName = curPath + "/sub/" + QString::number(oldQueue) + ".stm";
        QFile subFile(subFileName);
        if(!subFile.open(QIODevice::Append))
            return;
        QDataStream subStream(&subFile);
        subStream.setVersion(QDataStream::Qt_5_12);
        subStream << oldKey;
        now++;
        if(now % (numberCount / 100) == 0)
            emit update((int)(now * 100/ numberCount),1);
    }

    aFile.close();
    emit update(0,2);
    now = 0;



//    int fileCount = 10;
    QString resultFileName = curPath + "/result/result.stm";
    QFile resultFile(resultFileName);
    if(!resultFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    QDataStream resultStream(&resultFile);
    resultStream.setVersion(QDataStream::Qt_5_12);

    int flag[fileCount + 1];
    memset(flag,0,sizeof(flag));

    qint64 arrayFile[fileCount + 1];
    for(int i = 1;i <= fileCount;i++)
    {
        QString subFileName = curPath + "/sub/" + QString::number(i) + ".stm";
        QFile subFile(subFileName);
        if(!subFile.open(QIODevice::ReadOnly))
            return;
        QDataStream subStream(&subFile);
        subStream.setVersion(QDataStream::Qt_5_12);
        subStream >> arrayFile[i];
        flag[i]++;
    }

    completeWinnerTree<qint64> fileTree = completeWinnerTree<qint64>(arrayFile,fileCount);
    int count = fileCount;

    while(count)
    {
        int winner = fileTree.winner();
        qint64 old = arrayFile[winner];

        QString subFileName = curPath + "/sub/" + QString::number(winner) + ".stm";
        QFile subFile(subFileName);
        if(!subFile.open(QIODevice::ReadOnly))
            return;
        QDataStream subStream(&subFile);
        subStream.setVersion(QDataStream::Qt_5_12);

        for(int i = 0;i < flag[winner];i++)
            subStream >> arrayFile[winner];
        if(!subStream.atEnd())
        {
            subStream >> arrayFile[winner];
            flag[winner]++;
        }
        else {
            count--;
            arrayFile[winner] = INT64_MAX;
        }

        fileTree.rePlay(winner);

        resultStream << old;
        now++;
        if(now % (numberCount / 100) == 0)
            emit update((int)(now * 100/ numberCount),2);
    }

    for(int i = 1;i <= fileCount;i++)
    {
        QFile::remove(curPath + "/sub/" + QString::number(i) + ".stm");
    }

    emit test(2 * fileCount,2 * fileCount);
    emit result();
    quit();
}

