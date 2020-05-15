#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chessboard.h"
#include "dialogini.h"
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPoint>
#include <QGraphicsItem>
#include "threadcolormap.h"
#include "QProcess"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void iniChessboard();
    void iniChessboardFinish();
    void drawGrafic();
    void restart();
    void clear();


private:
    Ui::MainWindow *ui;
    Chessboard * chessboard = NULL;
    QGraphicsScene * scene = NULL;
    threadColorMap threadA;
    void iniSignol();
};

#endif // MAINWINDOW_H
