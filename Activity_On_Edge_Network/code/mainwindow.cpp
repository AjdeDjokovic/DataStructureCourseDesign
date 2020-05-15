#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->plainTextEdit);
    this->setWindowState(Qt::WindowMaximized);
    iniSignol();

    textData = ui->plainTextEdit->toPlainText();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ini()
{
    ui->plainTextEdit->clear();
    if(map != NULL)
    {
        delete map;
        map = NULL;
    }

    QString dlgTitle = "information";
    QString strInfo = "输入任意行，每行包含3个数字，分别是起始事件、终止事件、耗费时间";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);

    DialogIni* dialogIni = new DialogIni(this);
    Qt::WindowFlags flags = dialogIni->windowFlags();
    dialogIni->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dialogIni->exec();
    if(ret != QDialog::Accepted)
        return;
    QString str = dialogIni->getContent();
    QStringList list = str.split(QRegExp("\n"),QString::SkipEmptyParts);
    std::set<int> s;
    try {
        map = new aoe();
        int count = 1;
        foreach(QString num, list)
        {
            QException e;
            QStringList subList = num.split(QRegExp("\\s"),QString::SkipEmptyParts);
            if(subList.size() != 3 || !IsNumber(subList[0]) || !IsNumber(subList[0]) || !IsNumber(subList[1]) || !IsNumber(subList[2]))
                throw e;
            map->read_graph(subList[0].toInt(), subList[1].toInt(), subList[2].toInt(), count++);
            s.insert(subList[0].toInt());
            s.insert(subList[1].toInt());
        }
        map->set(list.size(),s);
    } catch (QException) {
        QString dlgTitle = "warning";
        QString strInfo = "输入格式错误";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        delete map;
        map = NULL;
        return;
    }
    if(!map->toposort())
    {
        QString dlgTitle = "warning";
        QString strInfo = "输入aoe图中有环路";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        delete map;
        map = NULL;
        return;
    }
    map->CriticalPath();
    map->dfs();

    QString arg = "your input : \n\n" + str + "\n\n\n";
    arg += "vertax number : " + QString::number(s.size()) + "\t\t" + "activity number : " + QString::number(list.size()) + "\n\n";

    output(arg);

    QString dlgTitle1 = "information";
    QString strInfo1 = "初始化AOE图成功";
    QMessageBox::information(this,dlgTitle1,strInfo1,QMessageBox::Ok,QMessageBox::NoButton);
}

void MainWindow::output(QString arg)
{
    ui->plainTextEdit->appendPlainText(arg);

    ui->plainTextEdit->appendPlainText("\nThe topological sort result are:\n");
    ui->plainTextEdit->appendPlainText(map->outTopo());

    ui->plainTextEdit->appendPlainText("\nThe critical activities are:\n");
    foreach(QString str,map->list1)
    {
        ui->plainTextEdit->appendPlainText(str);
    }

    ui->plainTextEdit->appendPlainText("\nThe critical path are:\n");
    foreach(QString str,map->list2)
    {
        ui->plainTextEdit->appendPlainText(str);
    }

    ui->plainTextEdit->appendPlainText("\nThe critical path  length are : " + QString::number(map->outLength()) + "\n");

    ui->plainTextEdit->appendPlainText("\nThe vertax early time and last time are:\n");
    ui->plainTextEdit->appendPlainText(map->outV());

    ui->plainTextEdit->appendPlainText("\nThe activity early time and last time are:\n");
    ui->plainTextEdit->appendPlainText(map->outE());


}

void MainWindow::iniSignol()
{
    connect(ui->actIni,&QAction::triggered,this,&MainWindow::ini);
    connect(ui->actClear,&QAction::triggered,this,&MainWindow::clear);
    connect(ui->actRestart,&QAction::triggered,this,&MainWindow::restart);
    connect(ui->actData,&QAction::triggered,this,&MainWindow::data);
}

void MainWindow::clear()
{
    ui->plainTextEdit->clear();
    if(map != NULL)
    {
        delete map;
        map = NULL;
        QString dlgTitle = "information";
        QString strInfo = "清除成功";
        QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    }
    else {
        QString dlgTitle = "warning";
        QString strInfo = "没有要清除的AOE图";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    }
}

bool MainWindow::IsNumber(QString qstrSrc)
{
    QByteArray ba = qstrSrc.toLatin1();
    const char *s = ba.data();
    bool bret = true;
    while(*s)
    {
        if(*s>='0' && *s<='9')
        {

        }
        else
        {
            bret = false;
            break;
        }
        s++;
    }
    return bret;
}

void MainWindow::restart()
{
    qApp->quit();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}

void MainWindow::data()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(textData);
}
