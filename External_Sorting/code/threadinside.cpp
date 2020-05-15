#include "threadinside.h"

threadInside::threadInside()
{

}

void threadInside::set(QString fileName,QString curPath,int storage)
{
    this->fileName = fileName;
    this->curPath = curPath;
    this->storage = storage;
}

void threadInside::run()
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
//    emit update(0,1);


    while(!aStream.atEnd() && ++fileCount)
    {
        int count = 0;
        firstPlayer array[storage];
        for(int i = 0;i < storage;i++)
            if(!aStream.atEnd())
            {
                aStream >> array[i].key;
                count++;
            }
            else
                break;

        QString subFileName = curPath + "/sub/" + QString::number(fileCount) + ".stm";
        QFile subFile(subFileName);
        if(!subFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
            return;
        QDataStream subStream(&subFile);
        subStream.setVersion(QDataStream::Qt_5_12);

        std::sort(array,array + count);
        for(int i = 0;i < count;i++)
        {
            subStream << array[i].key;
            now++;
            if(now % (numberCount / 100) == 0)
                emit update((int)(now * 100/ numberCount),1);
        }
        subFile.close();
    }


    aFile.close();
    emit update(0,2);
    now = 0;






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
