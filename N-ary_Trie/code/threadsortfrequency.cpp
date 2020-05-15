#include "threadsortfrequency.h"


threadSortFrequency::threadSortFrequency()
{

}

void threadSortFrequency::set(Trie* trie,TrieNode * node)
{
    this->trie = trie;
    this->node = node;
}

//void threadSortFrequency::run()
//{
//    std::vector<SortItem> v;
//    trie->sortPre(node,v);
//    sort(v.begin(),v.end());
//    QString str;
//    for (std::vector<SortItem>::iterator i = v.begin();i != v.end();i++)
//        str += QString(QLatin1String(i->word)) + ":" + QString::number(i->count) + "\t";
//    emit result(str);
//    quit();
//}

void threadSortFrequency::run()
{
    std::vector<SortItem> v;
    trie->sortPre(node,v);

    double numberCount = v.size();
    double now = 0;
    emit update(0,1);

//    QString preFileName = QDir::currentPath() + "/sort/pre.stm";
//    QFile preFile(preFileName);
//    if(!preFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
//        return;
//    QDataStream preStream(&preFile);
//    preStream.setVersion(QDataStream::Qt_5_12);
    std::vector<SortItem>::iterator iter = v.begin();
    int fileCount = 0;
    int storage;
    if(numberCount <= 1000)
        storage = numberCount - 2;
    else
        storage = 1000;

    while(iter != v.end() && ++fileCount)
    {
        QString subFileName = QDir::currentPath() + "/sort/" + QString::number(fileCount) + ".stm";
        QFile subFile(subFileName);
        if(!subFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
            return;
        QDataStream subStream(&subFile);
        subStream.setVersion(QDataStream::Qt_5_12);

        int count = 0;
        SortItem array[storage];
        for(int i = 0;i < storage;i++)
            if(iter != v.end())
            {
                array[i].count = iter->count;
                array[i].word = new char[strlen(iter->word) + 1];
                strcpy(array[i].word,iter->word);
                iter++;
                count++;
            }
            else
                break;

        std::sort(array,array + count);
        for(int i = 0;i < count;i++)
        {
            subStream << array[i].count;
            subStream << QString(QLatin1String(array[i].word));
            now++;
            double f = 0.1;
            if(now / numberCount > f || now == numberCount)
            {
                emit update((int)(now * 100/ numberCount),1);
                f += 0.1;
            }
        }
        subFile.close();
    }


    emit update(0,2);
    now = 0;




//    QString resultFileName = QDir::currentPath() + "/sort/result.stm";
//    QFile resultFile(resultFileName);
//    if(!resultFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
//        return;
//    QDataStream resultStream(&resultFile);
//    resultStream.setVersion(QDataStream::Qt_5_12);

    QString str;

    int flag[fileCount + 1];
    memset(flag,0,sizeof(flag));

    firstPlayer arrayFile[fileCount + 1];
    for(int i = 1;i <= fileCount;i++)
    {
        QString subFileName = QDir::currentPath() + "/sort/" + QString::number(i) + ".stm";
        QFile subFile(subFileName);
        if(!subFile.open(QIODevice::ReadOnly))
            return;
        QDataStream subStream(&subFile);
        subStream.setVersion(QDataStream::Qt_5_12);
        subStream >> arrayFile[i].count;
        subStream >> arrayFile[i].word;
        flag[i]++;
    }

    completeWinnerTree<firstPlayer> fileTree = completeWinnerTree<firstPlayer>(arrayFile,fileCount);
    int count = fileCount;

    str.clear();
    while(count)
    {
        int winner = fileTree.winner();
        firstPlayer old = arrayFile[winner];

        QString subFileName = QDir::currentPath() + "/sort/" + QString::number(winner) + ".stm";
        QFile subFile(subFileName);
        if(!subFile.open(QIODevice::ReadOnly))
            return;
        QDataStream subStream(&subFile);
        subStream.setVersion(QDataStream::Qt_5_12);

        for(int i = 0;i < flag[winner];i++)
        {
            subStream >> arrayFile[winner].count;
            subStream >> arrayFile[winner].word;
        }
        if(!subStream.atEnd())
        {
            subStream >> arrayFile[winner].count;
            subStream >> arrayFile[winner].word;
            flag[winner]++;
        }
        else {
            --count;
            arrayFile[winner].count = 0;
            arrayFile[winner].word = "";
        }

        fileTree.rePlay(winner);

//        resultStream << old.count;
//        resultStream << old.word;
        if(old.word != ".stm")
            str += old.word + ":" + QString::number(old.count) + "\t";
        now++;

        double f = 0.1;
        if(now / numberCount > f || now == numberCount)
        {
            emit update((int)(now * 100/ numberCount),2);
            f += 0.1;
        }
    }

    for(int i = 1;i <= fileCount;i++)
    {
        QFile::remove(QDir::currentPath() + "/sort/" + QString::number(i) + ".stm");
    }

    emit result(str);
    quit();
}
