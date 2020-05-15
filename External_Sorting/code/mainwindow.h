#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "dialogsize.h"
#include <QDir>
#include <QFileDialog>
#include <threaddataform.h>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include "threaddatasort.h"
#include "threadinside.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void dataForm();
    void dataFormFinish(QString);
    void dataSort();
    void dataSortFinish();
    void openFile();
    void openFileByName(QString);
    void updateProgressBar(int,int);
    void clear();
    void testShow(qint64,qint64);
    void dataInside();
    void dataInsideFinish();

private:
    Ui::MainWindow *ui;
    threadDataForm threadA;
    threadDataSort threadB;
    threadInside threadC;
    QLabel * testShowLabel;
    void iniTool();
    void iniSignol();
};

#endif // MAINWINDOW_H
