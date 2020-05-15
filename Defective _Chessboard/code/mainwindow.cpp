#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    iniSignol();

    this->setCentralWidget(ui->graphicsView);
    this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniSignol()
{
    connect(ui->actIni,&QAction::triggered,this,&MainWindow::iniChessboard);
    connect(&threadA,&threadColorMap::result,this,&MainWindow::iniChessboardFinish);
    connect(ui->actRestart,&QAction::triggered,this,&MainWindow::restart);
    connect(ui->actClear,&QAction::triggered,this,&MainWindow::clear);
}

void MainWindow::iniChessboard()
{
    DialogIni* dialogIni = new DialogIni(this);
    Qt::WindowFlags flags = dialogIni->windowFlags();
    dialogIni->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dialogIni->exec();
    if(ret != QDialog::Accepted)
        return;
    if(chessboard != NULL)
    {
        delete chessboard;
        chessboard = NULL;
    }
    if(scene != NULL)
    {
        scene->clear();
        delete scene;
        scene = NULL;
    }
    int k = dialogIni->getK();
    int row = dialogIni->getRow();
    int col = dialogIni->getCol();
    delete dialogIni;
    if(row < 0 || row >= pow(2,k) || col < 0 || col >= pow(2,k))
    {
        QString dlgTitle = "warning";
        QString strInfo = "残缺不在棋盘中";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    chessboard = new Chessboard(k,row,col);
    threadA.set(chessboard,k,row,col);
    threadA.start();
}

void MainWindow::drawGrafic()
{
    if(scene != NULL)
    {
        scene->clear();
        delete scene;
        scene = NULL;
    }

    QColor carray[5] = {QColor(255,255,255),QColor(0,0,0),QColor(255,0,0),QColor(30,144,255),QColor(0,255,0)};
//    QColor carray[4] = {QColor(255,255,255),QColor(0,0,255),QColor(255,0,0),QColor(0,255,0)};

    double r = 50;
    double sceneWigth = chessboard->size * r * 2;
    QRectF rect(- sceneWigth * 0.5,- sceneWigth * 0.5,sceneWigth,sceneWigth);
    scene = new QGraphicsScene(rect);
    ui->graphicsView->setScene(scene);
    for(int i = 0;i < chessboard->size;i++)
        for(int j = 0;j < chessboard->size;j++)
        {
            QGraphicsRectItem * item = new QGraphicsRectItem(-r,-r,2 * r , 2 * r);
            item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
            QPen pen;
            pen.setWidth(2);
            item->setPen(pen);
            item->setPos(- sceneWigth * 0.5 + r + j * 2 * r,- sceneWigth * 0.5 + r + i * 2 * r);
            item->setBrush(carray[chessboard->colorLess[chessboard->board[i][j]]]);
            scene->addItem(item);
        }
    ui->graphicsView->centerOn(0,0);
}

void MainWindow::iniChessboardFinish()
{

    threadA.wait();

    QString dlgTitle = "warning";
    QString strInfo = "最少颜色：" + QString::number(chessboard->colorMax) + "种";
    QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);

    drawGrafic();
}

void MainWindow::restart()
{
    if(scene != NULL)
    {
        scene->clear();
        delete scene;
        scene = NULL;
    }
    if(chessboard != NULL)
    {
        delete chessboard;
        chessboard = NULL;
    }
    qApp->quit();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}

void MainWindow::clear()
{
    if(scene != NULL)
    {
        scene->clear();
        delete scene;
        scene = NULL;
    }
    if(chessboard != NULL)
    {
        delete chessboard;
        chessboard = NULL;
    }
}


