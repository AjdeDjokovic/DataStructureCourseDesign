#include "threaddataform.h"
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
    int nRandom1 = qrand();
    int nRandom2 = qrand();

    int nRandom = (nRandom1 << 16) | nRandom2;
    nRandom %= (max - min);

    nRandom += min;

    return nRandom;
}

QString getRandomString(int length)
{
    int level = 1;
    int max = generateRandomInteger(1,pow(26,length));
    while(max / 26 > 1)
    {
        max /= 26;
        level++;
    }
    QString tmp = "abcdefghijklmnopqrstuvwxyz";
    QString str = "";
    static bool seedStatus;
    if (!seedStatus)
    {
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        seedStatus = true;
    }
    for(int i = 0;i < level;i++)
    {
        int ir = qrand() % tmp.length();
        str[i] = tmp.at(ir);
    }
    return str;
}


threadDataForm::threadDataForm()
{

}

void threadDataForm::set(QString fileName,int size,int length,bool standard)
{
    this->fileName = fileName;
    this->size = size;
    this->length = length;
    this->standard = standard;
}

void threadDataForm::run()
{
    QFile aFile(fileName);
    if(!aFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    QTextStream aStream(&aFile);

    if(!standard)
    {
        for(int i = 1;i <= size;i++)
        {
            aStream << getRandomString(length) << QString::fromStdString("\t");
            if(i % 20 == 0)
                aStream << QString::fromStdString("\n");
        }
    }
    else
    {
        for(int i = 1;i <= pow(26,length) * 5;i++)
        {
            aStream << getRandomString(length) << QString::fromStdString("\t");
            if(i % 20 == 0)
                aStream << QString::fromStdString("\n");
        }
    }
    aFile.close();
    emit result(fileName);
    quit();
}

