#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "skiplist.h"
#include <QDebug>
#include "dialogsize.h"
#include "dialoginsertonly.h"
#include "dialoginsertmore.h"
#include "dialoginitialize.h"
#include "mythread.h"
#include "testthread.h"
#include "adjustthread.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initialize();
    void insert();
    void earse();
    void earseMin();
    void earseMax();
    void search();
    void output();
    void output(QString*);
    void clear();
    void randomPair();
    void insertOnly();
    void randomInitialize(QString*);
    void startTest();
    void outputTest(QString*);
    void stopTest();
    void adjustStart();
    void adjustStop(skipList<int,QString>* list);
    void size();
private:
    Ui::MainWindow *ui;
    skipList<int,QString>* slist;
    myThread threadA;
    testThread threadB;
    adjustThread threadC;
    void iniTool();
    void iniSignol();
};

#endif // MAINWINDOW_H
