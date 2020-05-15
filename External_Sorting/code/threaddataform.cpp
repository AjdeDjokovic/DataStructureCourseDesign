#include "threaddataform.h"


qint64 generateRandomInteger()
{
    // 加入随机种子。种子是当前时间距离0点0分0秒的秒数。
    // 每次启动程序，只添加一次种子，以做到数字真正随机。
    static bool seedStatus;
    if (!seedStatus)
    {
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        seedStatus = true;
    }
    int nRandom1 = qrand() ;
    int nRandom2 = qrand() ;

    qint64 nRandom = ((qint64)nRandom1 << 32) | nRandom2;
    nRandom = nRandom;

    return nRandom;
}


threadDataForm::threadDataForm()
{

}

void threadDataForm::set(QString fileName,qint64 size)
{
    this->fileName = fileName;
    this->size = size;
}

void threadDataForm::run()
{
    QFile aFile(fileName);
    if(!aFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    QDataStream aStream(&aFile);
    aStream.setVersion(QDataStream::Qt_5_12);
    for(qint64 i = 0;i < size;i++)
    {
        aStream << generateRandomInteger();
    }
    emit result(fileName);
    quit();
}
