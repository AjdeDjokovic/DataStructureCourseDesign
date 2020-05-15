#ifndef THREADDATAFORM_H
#define THREADDATAFORM_H

#include <QThread>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <math.h>

class threadDataForm : public QThread
{
    Q_OBJECT
public:
    threadDataForm();
    void set(QString,int,int,bool);
protected:
    void run() Q_DECL_OVERRIDE;
private:
    QString fileName;
    int size;
    int length;
    bool standard;
signals:
    void result(QString);
};

#endif // THREADDATAFORM_H
