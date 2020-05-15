#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QObject>
#include <QPoint>
#include <QGraphicsItem>
#include <trie.h>
#include <stack>
#include "stacknode.h"
#include "dialoginitialize.h"
#include <math.h>
#include "dialogsearch.h"
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include "dialogsize.h"
#include "threaddataform.h"
#include "threadfileini.h"
#include "threadsortfrequency.h"
#include "trieshow.h"
#include "windowsort.h"
#include "windowfile.h"
#include "dialoginsert.h"
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
    void inputIni();
    void fileIni();
    void fileIniFinish();
    void deleteTrie();
    void deleteNode();
    void insert();

    void openGrafic();
    void openSort();
    void openFile();
    void on_tabWidget_tabCloseRequested(int index);
    void on_tabWidget_currentChanged(int index);
    void paintEvent(QPaintEvent *event);
    void restart();

private:
    Ui::MainWindow *ui;
    Trie * trie = NULL;
    threadFileIni threadB;
    void iniSignol();
    void iniTool(bool);
};

#endif // MAINWINDOW_H
