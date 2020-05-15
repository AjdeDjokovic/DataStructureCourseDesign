#ifndef THREADDATAFORM_H
#define THREADDATAFORM_H
#include <QThread>
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QTime>


class threadDataForm : public QThread
{
    Q_OBJECT
public:
    threadDataForm();
    void set(QString,qint64);
protected:
    void run() Q_DECL_OVERRIDE;
private:
    QString fileName;
    qint64 size;
signals:
    void result(QString);
};

#endif // THREADDATAFORM_H
