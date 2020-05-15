#include "threadfileini.h"

threadFileIni::threadFileIni()
{

}

void threadFileIni::set(Trie *trie,QString fileName)
{
    this->trie = trie;
    this->fileName = fileName;
}

void threadFileIni::run()
{
    QFile aFile(fileName);
    if(!aFile.open(QIODevice::ReadOnly))
        return;
    QTextStream aStream(&aFile);
    int row = 1;
    while(!aStream.atEnd())
    {
        QString str = aStream.readLine();
        std::string s = str.toStdString();
        for(int i = 0;i < str.length();i++)
            if(!isalpha(s[i]))
                s[i] = ' ';
        str = QString::fromStdString(s);
        str = str.toLower();
        QStringList list = str.split(QRegExp("\\s"),QString::SkipEmptyParts);
        foreach(QString sub,list)
        {
            char*  ch;
            QByteArray ba = sub.toLatin1(); // must
            ch=ba.data();
            trie->Insert(ch,row);
        }
        row++;
    }
    aFile.close();
    emit result();
    quit();
}
