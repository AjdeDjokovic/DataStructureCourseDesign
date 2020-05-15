#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogini.h"
#include "aoe.h"
#include <QMessageBox>
#include <QException>
#include <set>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ini();
    void output(QString);
    void clear();
    bool IsNumber(QString qstrSrc);
    void restart();
    void data();

private:
    Ui::MainWindow *ui;
    aoe * map = NULL;
    QString textData;
    void iniSignol();
};

#endif // MAINWINDOW_H
