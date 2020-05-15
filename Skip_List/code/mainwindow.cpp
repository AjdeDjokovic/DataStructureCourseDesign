#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    iniTool();
    iniSignol();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniTool()
{
    ui->actInitiate->setEnabled(true);
    ui->actRandomIni->setEnabled(true);
    ui->actClear->setEnabled(false);
    ui->actInsert->setEnabled(false);
    ui->actInsertOnly->setEnabled(false);
    ui->actSearch->setEnabled(false);
    ui->actEarse->setEnabled(false);
    ui->actEarseMin->setEnabled(false);
    ui->actEarseMax->setEnabled(false);
    ui->actTestStart->setEnabled(false);
    ui->actTestStop->setEnabled(false);
    ui->actAdjust->setEnabled(false);
    ui->actDsize->setEnabled(false);
}

void MainWindow::iniSignol()
{
    connect(ui->actInitiate,&QAction::triggered,this,&MainWindow::initialize);
    connect(ui->actRandomIni,&QAction::triggered,this,&MainWindow::randomPair);
    connect(ui->actInsert,&QAction::triggered,this,&MainWindow::insert);
    connect(ui->actInsertOnly,&QAction::triggered,this,&MainWindow::insertOnly);
    connect(ui->actEarse,&QAction::triggered,this,&MainWindow::earse);
    connect(ui->actSearch,&QAction::triggered,this,&MainWindow::search);
    connect(ui->actClear,&QAction::triggered,this,&MainWindow::clear);
    connect(ui->actEarseMin,&QAction::triggered,this,&MainWindow::earseMin);
    connect(ui->actEarseMax,&QAction::triggered,this,&MainWindow::earseMax);
    connect(&threadA,&myThread::result,this,&MainWindow::randomInitialize);
    connect(ui->actTestStart,&QAction::triggered,this,&MainWindow::startTest);
    connect(ui->actTestStop,&QAction::triggered,this,&MainWindow::stopTest);
    connect(&threadB,&testThread::result,this,&MainWindow::outputTest);
    connect(ui->actAdjust,&QAction::triggered,this,&MainWindow::adjustStart);
    connect(&threadC,&adjustThread::result,this,&MainWindow::adjustStop);
    connect(ui->actDsize,&QAction::triggered,this,&MainWindow::size);
}


void MainWindow::output()
{
    ui->plainTextEdit->clear();
    QString* str = slist->out();
    ui->plainTextEdit->setPlainText(*str);
}

void MainWindow::output(QString* str)
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->setPlainText(*str);
}

void MainWindow::initialize()
{
    DialogInitialize* dialogInitialize = new DialogInitialize(this);
    Qt::WindowFlags flags = dialogInitialize->windowFlags();
    dialogInitialize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dialogInitialize->exec();
    if(ret != QDialog::Accepted)
        return;
    int inputValue = dialogInitialize->maxKey();
    QString str = dialogInitialize->str();
    delete dialogInitialize;
    slist = new skipList<int,QString>(inputValue,inputValue,0.5);
    QStringList list = str.split(QRegExp("\\s"),QString::SkipEmptyParts);
    std::pair<int,QString>* thePair = new std::pair<int,QString>();
    foreach(QString num, list)
    {
        QStringList numArray = num.split(":",QString::SkipEmptyParts);
        int first = numArray[0].toInt();
        thePair->first = first;
        thePair->second = numArray[1];
        if(!slist->insert(*thePair))
        {
            QString dlgTitle = "warning";
            QString strInfo = "关键字越界";
            QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        }
//        ui->plainTextEdit->setPlainText(QString::number(slist->headerNode->next[0]->element.first));
    }
    delete thePair;

    output();
    ui->actInitiate->setEnabled(false);
    ui->actRandomIni->setEnabled(false);
    ui->actClear->setEnabled(true);
    ui->actInsert->setEnabled(true);
    ui->actInsertOnly->setEnabled(true);
    ui->actSearch->setEnabled(true);
    ui->actEarse->setEnabled(true);
    ui->actEarseMin->setEnabled(true);
    ui->actEarseMax->setEnabled(true);
    ui->actTestStart->setEnabled(true);
    ui->actTestStop->setEnabled(true);
    ui->actAdjust->setEnabled(true);
    ui->actDsize->setEnabled(true);
}

void MainWindow::randomPair()
{
    DialogSize* dialogSize = new DialogSize(this);
    Qt::WindowFlags flags = dialogSize->windowFlags();
    dialogSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dialogSize->exec();
    if(ret != QDialog::Accepted)
        return;
    int maxKey = dialogSize->maxKey();
    int listSize = dialogSize->listSize();
    if(maxKey <= listSize)
    {
        QString dlgTitle = "warning";
        QString strInfo = "设置的最大关键字太小";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    slist = new skipList<int,QString>(maxKey,maxKey,0.5);
    threadA.set(slist,maxKey,listSize);
    delete dialogSize;
    threadA.start();
}

void MainWindow::randomInitialize(QString* str)
{
    threadA.wait();

    output(str);
    ui->actInitiate->setEnabled(false);
    ui->actRandomIni->setEnabled(false);
    ui->actClear->setEnabled(true);
    ui->actInsert->setEnabled(true);
    ui->actInsertOnly->setEnabled(true);
    ui->actSearch->setEnabled(true);
    ui->actEarse->setEnabled(true);
    ui->actEarseMin->setEnabled(true);
    ui->actEarseMax->setEnabled(true);
    ui->actTestStart->setEnabled(true);
    ui->actTestStop->setEnabled(true);
    ui->actAdjust->setEnabled(true);
    ui->actDsize->setEnabled(true);
}

//void MainWindow::randomInitialize()
//{
//    ui->plainTextEdit->clear();
//    DialogSize* dialogSize = new DialogSize(this);
//    Qt::WindowFlags flags = dialogSize->windowFlags();
//    dialogSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
//    int ret = dialogSize->exec();
//    if(ret != QDialog::Accepted)
//        return;
//    int maxKey = dialogSize->maxKey();
//    int listSize = dialogSize->listSize();
//    if(maxKey <= listSize)
//    {
//        QString dlgTitle = "warning";
//        QString strInfo = "设置的最大关键字太小";
//        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
//        return;
//    }
//    slist = new skipList<int,QString>(maxKey,listSize,0.5);
//    std::pair<int,QString>* thePair = new std::pair<int,QString>();

////    for(int i = 0;i < listSize;i++)
//    while(listSize--)
//    {
//        int key = generateRandomInteger(1,maxKey);
////        QString str = getRandomString();
////        QString str = "abc";
//        QString str = QString::number(generateRandomInteger(1,100000));
//        thePair->first = key;
//        thePair->second = str;
//        slist->insert(*thePair);
//    }

//    delete dialogSize;
//    output();
//    ui->actInitiate->setEnabled(false);
//    ui->actRandomIni->setEnabled(false);
//    ui->actClear->setEnabled(true);
//    ui->actInsert->setEnabled(true);
//    ui->actInsertOnly->setEnabled(true);
//    ui->actSearch->setEnabled(true);
//    ui->actEarse->setEnabled(true);
//    ui->actEarseMin->setEnabled(true);
//    ui->actEarseMax->setEnabled(true);
//}

void MainWindow::insert()
{
    DialogInsertMore* dialogInsertMore = new DialogInsertMore(this);
    Qt::WindowFlags flags = dialogInsertMore->windowFlags();
    dialogInsertMore->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dialogInsertMore->exec();
    if(ret != QDialog::Accepted)
        return;
    QString str = dialogInsertMore->str();
    delete dialogInsertMore;
    QStringList list = str.split(QRegExp("\\s"),QString::SkipEmptyParts);
    std::pair<int,QString>* thePair = new std::pair<int,QString>();
    foreach(QString num, list)
    {
        QStringList numArray = num.split(":",QString::SkipEmptyParts);
        int first = numArray[0].toInt();
        thePair->first = first;
        thePair->second = numArray[1];
        if(!slist->insert(*thePair))
        {
            QString dlgTitle = "warning";
            QString strInfo = "关键字越界";
            QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        }
    }
    delete thePair;
    output();
}

void MainWindow::insertOnly()
{
    DialogInsertOnly* dialogInsertOnly = new DialogInsertOnly(this);
    Qt::WindowFlags flags = dialogInsertOnly->windowFlags();
    dialogInsertOnly->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dialogInsertOnly->exec();
    if(ret != QDialog::Accepted)
        return;
    int key = dialogInsertOnly->key();
    QString str = dialogInsertOnly->str();
    std::pair<int,QString>* thePair = new std::pair<int,QString>(key,str);
    if(!slist->insert(*thePair))
    {
        QString dlgTitle = "warning";
        QString strInfo = "关键字越界";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    }
    delete thePair;
    output();
}

void MainWindow::earse()
{
    QString dlgTitle1 = "请输入整数";
    QString strInfo1 = "输入要删除的关键字";
    int defaultValue = 1;
    bool ok = false;
    int inputValue = QInputDialog::getInt(this,dlgTitle1,strInfo1,defaultValue,1,slist->tailKey-1,1,&ok);
    if(!slist->erase(inputValue))
    {
        QString dlgTitle = "warning";
        QString strInfo = "跳表中没有该关键字的节点";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    }

    output();
}

void MainWindow::earseMin()
{
    if(!slist->earseMin())
    {
        QString dlgTitle = "warning";
        QString strInfo = "跳表中没有节点,无法删除";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    }

    output();
}

void MainWindow::earseMax()
{
    if(!slist->earseMax())
    {
        QString dlgTitle = "warning";
        QString strInfo = "跳表中没有节点,无法删除";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    }

    output();
}

void MainWindow::search()
{
    QString dlgTitle1 = "请输入整数";
    QString strInfo1 = "输入要查找节点的关键字";
    int defaultValue = 1;
    bool ok = false;
    int inputValue = QInputDialog::getInt(this,dlgTitle1,strInfo1,defaultValue,1,slist->tailKey-1,1,&ok);
    skipNode<int,QString>* theNode = slist->search(inputValue);
    if(theNode->element.first == inputValue)
    {
        QString dlgTitle = "reslut";
        QString strInfo = "结果:" + theNode->element.second;
        QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    }
    else
    {
        QString dlgTitle = "warning";
        QString strInfo = "跳表中没有该关键字的节点";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    }
}

void MainWindow::clear()
{
    delete slist;
    ui->plainTextEdit->clear();
    ui->actInitiate->setEnabled(true);
    ui->actRandomIni->setEnabled(true);
    ui->actClear->setEnabled(false);
    ui->actInsert->setEnabled(false);
    ui->actInsertOnly->setEnabled(false);
    ui->actSearch->setEnabled(false);
    ui->actEarse->setEnabled(false);
    ui->actEarseMin->setEnabled(false);
    ui->actEarseMax->setEnabled(false);
    ui->actTestStart->setEnabled(false);
    ui->actTestStop->setEnabled(false);
    ui->actAdjust->setEnabled(false);
    ui->actDsize->setEnabled(false);
}

void MainWindow::startTest()
{
    ui->textEdit->clear();
    QString dlgTitle1 = "请输入整数";
    QString strInfo1 = "请输入操作序列的规模";
    int defaultValue = 5000;
    bool ok = false;
    int inputValue = QInputDialog::getInt(this,dlgTitle1,strInfo1,defaultValue,1,slist->tailKey - 1,1,&ok);
    threadB.set(slist,inputValue);
    threadB.start();

    ui->actInitiate->setEnabled(false);
    ui->actRandomIni->setEnabled(false);
    ui->actClear->setEnabled(false);
    ui->actInsert->setEnabled(false);
    ui->actInsertOnly->setEnabled(false);
    ui->actSearch->setEnabled(false);
    ui->actEarse->setEnabled(false);
    ui->actEarseMin->setEnabled(false);
    ui->actEarseMax->setEnabled(false);
    ui->actTestStart->setEnabled(false);
    ui->actTestStop->setEnabled(true);
    ui->actAdjust->setEnabled(false);
    ui->actDsize->setEnabled(false);
}

void MainWindow::outputTest(QString* str)
{
    ui->textEdit->appendPlainText(*str);
}

void MainWindow::stopTest()
{
    threadB.stopThread();
    threadB.wait();

    output();
    ui->actInitiate->setEnabled(false);
    ui->actRandomIni->setEnabled(false);
    ui->actClear->setEnabled(true);
    ui->actInsert->setEnabled(true);
    ui->actInsertOnly->setEnabled(true);
    ui->actSearch->setEnabled(true);
    ui->actEarse->setEnabled(true);
    ui->actEarseMin->setEnabled(true);
    ui->actEarseMax->setEnabled(true);
    ui->actTestStart->setEnabled(true);
    ui->actTestStop->setEnabled(false);
    ui->actAdjust->setEnabled(true);
    ui->actDsize->setEnabled(true);
}

void MainWindow::adjustStart()
{
    threadC.set(slist);
    threadC.start();
}

void MainWindow::adjustStop(skipList<int,QString>* list)
{
    threadB.wait();
    slist = list;

    output();
}

void MainWindow::size()
{
    QString dlgTitle = "reslut";
    QString strInfo = "节点数量:" + QString::number(slist->size());
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
}
