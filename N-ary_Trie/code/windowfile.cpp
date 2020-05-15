#include "windowfile.h"
#include "ui_windowfile.h"

windowFile::windowFile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::windowFile)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->plainTextEdit);
    this->setWindowState(Qt::WindowMaximized);
    iniSignol();
}

windowFile::~windowFile()
{
    delete ui;
}

void windowFile::iniSignol()
{
    connect(ui->actOpenFile,&QAction::triggered,this,&windowFile::openFile);
    connect(ui->actCreateFile,&QAction::triggered,this,&windowFile::createFile);
    connect(&threadA,&threadDataForm::result,this,&windowFile::createFileFinish);
    connect(ui->actCreareStandard,&QAction::triggered,this,&windowFile::createFileStandard);
    connect(ui->actSave,&QAction::triggered,this,&windowFile::saveFile);
    connect(ui->actSaveLast,&QAction::triggered,this,&windowFile::saveFileLast);
    connect(ui->actDeleteFile,&QAction::triggered,this,&windowFile::deleteFile);
    connect(ui->actNewFile,&QAction::triggered,this,&windowFile::newFile);
    connect(ui->actFont,&QAction::triggered,this,&windowFile::fontChange);
}



void windowFile::openFile()
{
    QString curPath = QDir::currentPath();
    QString fileName = QFileDialog::getSaveFileName(this,"选择要打开的文本",curPath,"(*.txt)");
    if(fileName.isEmpty())
        return;
    QFile file(fileName);
    if(!file.exists())
    {
        QString dlgTitle = "warning";
        QString strInfo = "没有找到该文件";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString dlgTitle = "warning";
        QString strInfo = "打开文件失败";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    QTextStream stream(&file);
    output(stream.readAll());
    file.close();

    if(label != NULL)
    {
        delete label;
        label = NULL;
    }

    label = new QLabel();
    label->setMinimumWidth(150);
    label->setText(fileName);
    ui->statusbar->addWidget(label);
    return;
}

void windowFile::openFileByName(QString fileName)
{
    QFile file(fileName);
    if(!file.exists())
    {
        QString dlgTitle = "warning";
        QString strInfo = "没有找到该文件";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString dlgTitle = "warning";
        QString strInfo = "打开文件失败";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    QTextStream stream(&file);
    output(stream.readAll());
    file.close();

    if(label != NULL)
    {
        delete label;
        label = NULL;
    }

    label = new QLabel();
    label->setMinimumWidth(150);
    label->setText(fileName);
    ui->statusbar->addWidget(label);
}

void windowFile::output(QString str)
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(str);
}

void windowFile::createFile()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this,"选择生成文本文件",curPath,"(*.txt)");
    if(aFileName.isEmpty())
        return;
    DialogSize* dialogSize = new DialogSize(this);
    Qt::WindowFlags flags = dialogSize->windowFlags();
    dialogSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dialogSize->setDefault(1000,3,false);
    int ret = dialogSize->exec();
    if(ret != QDialog::Accepted)
        return;
    int size = dialogSize->size();
    int length = dialogSize->length();
    threadA.set(aFileName,size,length,false);
    threadA.start();
}

void windowFile::createFileStandard()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this,"选择生成文本文件",curPath,"(*.txt)");
    if(aFileName.isEmpty())
        return;
    DialogSize* dialogSize = new DialogSize(this);
    Qt::WindowFlags flags = dialogSize->windowFlags();
    dialogSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dialogSize->setDefault(1000,3,true);
    int ret = dialogSize->exec();
    if(ret != QDialog::Accepted)
        return;
    int length = dialogSize->length();
    threadA.set(aFileName,0,length,true);
    threadA.start();
}

void windowFile::createFileFinish(QString fileName)
{
    threadA.wait();

    QString dlgTitle = "reslut";
    QString strInfo = "数据文件已生成";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);

    openFileByName(fileName);
}

void windowFile::saveFile()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this,"选择保存位置",curPath,"(*.txt)");
    if(aFileName.isEmpty())
        return;
    QFile aFile(aFileName);
    if(!aFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QString dlgTitle = "warning";
        QString strInfo = "打开文件失败";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    QTextStream aStream(&aFile);
    QString str = ui->plainTextEdit->toPlainText();
    aStream << str;
    aFile.close();

    QString dlgTitle = "reslut";
    QString strInfo = "文件已保存";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
}

void windowFile::saveFileLast()
{
    if(label == NULL)
    {
        QString dlgTitle = "warning";
        QString strInfo = "尚未打开任何文件";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    QFile aFile(label->text());
    if(!aFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QString dlgTitle = "warning";
        QString strInfo = "打开文件失败";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    QTextStream aStream(&aFile);
    QString str = ui->plainTextEdit->toPlainText();
    aStream << str;
    aFile.close();

    QString dlgTitle = "reslut";
    QString strInfo = "文件已保存";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
}

void windowFile::deleteFile()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this,"选择保存位置",curPath,"(*.txt)");
    if(aFileName.isEmpty())
        return;
    QFile::remove(aFileName);

    QString dlgTitle = "reslut";
    QString strInfo = "文件删除";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
}

void windowFile::newFile()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this,"选择保存位置",curPath,"(*.txt)");
    if(aFileName.isEmpty())
        return;
    QFile aFile(aFileName);
    if(!aFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QString dlgTitle = "warning";
        QString strInfo = "新建文件失败";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    aFile.close();

    QString dlgTitle = "reslut";
    QString strInfo = "新建文件成功";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);

    openFileByName(aFileName);
}

void windowFile::fontChange()
{
    QFont iniFont = ui->plainTextEdit->font();
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok,iniFont);
    if(ok)
        ui->plainTextEdit->setFont(font);
}


