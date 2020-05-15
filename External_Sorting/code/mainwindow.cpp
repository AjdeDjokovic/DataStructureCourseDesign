#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    iniSignol();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniSignol()
{
    connect(ui->actDataForm,&QAction::triggered,this,&MainWindow::dataForm);
    connect(&threadA,&threadDataForm::result,this,&MainWindow::dataFormFinish);
    connect(ui->actSort,&QAction::triggered,this,&MainWindow::dataSort);
    connect(&threadB,&threadDataSort::result,this,&MainWindow::dataSortFinish);
    connect(&threadB,&threadDataSort::update,this,&MainWindow::updateProgressBar);
    connect(&threadB,&threadDataSort::test,this,&MainWindow::testShow);
    connect(ui->actOpenFile,&QAction::triggered,this,&MainWindow::openFile);
    connect(ui->actClear,&QAction::triggered,this,&MainWindow::clear);
    connect(ui->actInside,&QAction::triggered,this,&MainWindow::dataInside);
    connect(&threadC,&threadInside::result,this,&MainWindow::dataInsideFinish);
    connect(&threadC,&threadInside::update,this,&MainWindow::updateProgressBar);
    connect(&threadC,&threadInside::test,this,&MainWindow::testShow);
}

void MainWindow::dataForm()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this,"选择生成数据存储文件",curPath,"(*.stm)");
    if(aFileName.isEmpty())
        return;
    DialogSize* dialogSize = new DialogSize(this);
    Qt::WindowFlags flags = dialogSize->windowFlags();
    dialogSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dialogSize->setDefault(10000,"数据规模");
    int ret = dialogSize->exec();
    if(ret != QDialog::Accepted)
        return;
    qint64 size = dialogSize->size();
    threadA.set(aFileName,size);
    threadA.start();
}

void MainWindow::dataFormFinish(QString fileName)
{
    threadA.wait();

    QString dlgTitle = "reslut";
    QString strInfo = "数据文件已生成";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);

    openFileByName(fileName);
}

void MainWindow::dataSort()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this,"选择要进行排序的数据文件",curPath,"(*.stm)");
    if(aFileName.isEmpty())
        return;   
    DialogSize* dialogSize = new DialogSize(this);
    Qt::WindowFlags flags = dialogSize->windowFlags();
    dialogSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dialogSize->setDefault(1000,"内存规模");
    int ret = dialogSize->exec();
    if(ret != QDialog::Accepted)
        return;
    int storage = dialogSize->size();

    threadB.set(aFileName,curPath,storage);
    threadB.start();

}

void MainWindow::dataSortFinish()
{
    threadB.wait();

    QString dlgTitle = "reslut";
    QString strInfo = "排序已生成";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);

    openFileByName(QDir::currentPath() + "/result/result.stm");

}

void MainWindow::openFile()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this,"选择要打开的文件",curPath,"(*.stm)");
    if(aFileName.isEmpty())
        return;

    QFile file(aFileName);
    if(!file.open(QIODevice::ReadOnly))
        return;

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_5_12);
    QString str;
    while(!stream.atEnd())
    {
        qint64 number;
        stream >> number;
        str += QString::number(number) + "\t";
    }
    ui->plainTextEdit->setPlainText(str);
    ui->label->setText("进 度");
    ui->progressBar->setValue(0);
    testShowLabel->clear();
}

void MainWindow::openFileByName(QString aFileName)
{
    QFile file(aFileName);
    if(!file.open(QIODevice::ReadOnly))
        return;

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_5_12);
    QString str;
    while(!stream.atEnd())
    {
        qint64 number;
        stream >> number;
        str += QString::number(number) + "\t";
    }
    ui->plainTextEdit->setPlainText(str);
    ui->label->setText("进 度");
    ui->progressBar->setValue(0);
    testShowLabel->clear();
}

void MainWindow::updateProgressBar(int progress,int type)
{
    if(type == 1)
        ui->label->setText("各归并段生成中");
    else
        ui->label->setText("各归并段归并中");
    ui->progressBar->setValue(progress);
}

void MainWindow::clear()
{
    ui->plainTextEdit->clear();
    ui->label->setText("进 度");
    ui->progressBar->setValue(0);
    testShowLabel->clear();
}

void MainWindow::testShow(qint64 frequency1,qint64 frequency2)
{
    testShowLabel = new QLabel;
    testShowLabel->setMinimumWidth(150);
    testShowLabel->setText("数据文件排序总访问磁盘次数：" + QString::number(frequency1 + frequency2) + "次\t");
    ui->statusBar->addWidget(testShowLabel);
}

void MainWindow::dataInside()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this,"选择要进行排序的数据文件",curPath,"(*.stm)");
    if(aFileName.isEmpty())
        return;
    DialogSize* dialogSize = new DialogSize(this);
    Qt::WindowFlags flags = dialogSize->windowFlags();
    dialogSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dialogSize->setDefault(1000,"内存规模");
    int ret = dialogSize->exec();
    if(ret != QDialog::Accepted)
        return;
    int storage = dialogSize->size();

    threadC.set(aFileName,curPath,storage);
    threadC.start();
}


void MainWindow::dataInsideFinish()
{
    threadC.wait();

    QString dlgTitle = "reslut";
    QString strInfo = "排序已生成";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);

    openFileByName(QDir::currentPath() + "/result/result.stm");
}
