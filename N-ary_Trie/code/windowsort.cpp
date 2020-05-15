#include "windowsort.h"
#include "ui_windowsort.h"

windowSort::windowSort(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::windowSort)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);
    this->setWindowState(Qt::WindowMaximized);
    iniSignol();
}

windowSort::~windowSort()
{
    delete ui;
}

void windowSort::iniSignol()
{
    connect(ui->actsortFrequency,&QAction::triggered,this,&windowSort::sortFrequency);
    connect(&threadA,&threadSortFrequency::result,this,&windowSort::sortFrequencyFinish);
    connect(ui->actsortTrie,&QAction::triggered,this,&windowSort::sortTrie);
    connect(ui->actSearchRow,&QAction::triggered,this,&windowSort::searchRow);
    connect(&threadA,&threadSortFrequency::update,this,&windowSort::updateProgressBar);
    connect(ui->actsortInsideFrequency,&QAction::triggered,this,&windowSort::sortInsideFrequency);
    connect(&threadB,&threadSortInsideFrequency::result,this,&windowSort::sortInsideFrequencyFinish);
    connect(&threadB,&threadSortInsideFrequency::update,this,&windowSort::updateProgressBarInside);
    connect(ui->actFont,&QAction::triggered,this,&windowSort::fontChange);
}

void windowSort::set(Trie * trie)
{
    this->trie = trie;
}

void  windowSort::sortFrequency()
{
    DialogSearch* dialogSearch = new DialogSearch(this);
    Qt::WindowFlags flags = dialogSearch->windowFlags();
    dialogSearch->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dialogSearch->exec();
    if(ret != QDialog::Accepted)
        return;
    QString str = dialogSearch->str();
    delete dialogSearch;

    char*  ch;
    QByteArray ba = str.toLatin1(); // must
    ch=ba.data();

    TrieNode* result;
    if(str == "")
        result = trie->pRoot;
    else
        result = trie->SearchNode(ch);
    if(result == NULL)
    {
        QString dlgTitle = "reslut";
        QString strInfo = "无该节点";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }

    label = new QLabel();
    label->setMinimumWidth(150);
    progressBar = new QProgressBar();
    progressBar->setMaximumWidth(1000);
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    label->setText("各归并段生成中");
    progressBar->setValue(0);

    ui->statusbar->addWidget(label);
    ui->statusbar->addWidget(progressBar);

    threadA.set(trie,result);
    threadA.start();
}

void windowSort::sortFrequencyFinish(QString str)
{
    threadA.wait();

    output(str);

    QString dlgTitle = "reslut";
    QString strInfo = "排序已完成";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);

    delete label;
    label = NULL;
    delete progressBar;
    progressBar = NULL;
}

void windowSort::output(QString str)
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(str);
}

void windowSort::sortTrie()
{
    DialogSearch* dialogSearch = new DialogSearch(this);
    Qt::WindowFlags flags = dialogSearch->windowFlags();
    dialogSearch->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dialogSearch->exec();
    if(ret != QDialog::Accepted)
        return;
    QString str = dialogSearch->str();
    delete dialogSearch;

    char* ch;
    QByteArray ba = str.toLatin1(); // must
    ch=ba.data();

    TrieNode* result;

    if(str == "")
        result = trie->pRoot;
    else
        result = trie->SearchNode(ch);

    if(result == NULL)
    {
        QString dlgTitle = "warning";
        QString strInfo = "没有所查询的字符串";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }


    std::vector<SortItem> v;
    trie->sortPre(result,v);
    QString str1;
    for (std::vector<SortItem>::iterator i = v.begin();i != v.end();i++)
        str1 += QString(QLatin1String(i->word)) + ":" + QString::number(i->count) + "\t";
    output(str1);
}

void windowSort::searchRow()
{
    DialogSearch* dialogSearch = new DialogSearch(this);
    Qt::WindowFlags flags = dialogSearch->windowFlags();
    dialogSearch->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dialogSearch->exec();
    if(ret != QDialog::Accepted)
        return;
    QString str = dialogSearch->str();
    delete dialogSearch;

    char* ch;
    QByteArray ba = str.toLatin1(); // must
    ch=ba.data();

    TrieNode* result;

    result = trie->Search(ch);

    if(result == NULL)
    {
        QString dlgTitle = "warning";
        QString strInfo = "没有所查询的字符串";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }


    QString strRow;
    for(std::vector<int>::iterator iter = result->v.begin();iter != result->v.end();iter++)
    {
        strRow += QString::number(*iter) + "\n";
    }

    QString dlgTitle = "reslut";
    QString strInfo = "出现行数:\n" + strRow;
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
}

void windowSort::updateProgressBar(int progress,int type)
{
    if(type == 1)
        label->setText("各归并段生成中");
    else
        label->setText("各归并段归并中");
    progressBar->setValue(progress);
}

void windowSort::sortInsideFrequency()
{
    DialogSearch* dialogSearch = new DialogSearch(this);
    Qt::WindowFlags flags = dialogSearch->windowFlags();
    dialogSearch->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dialogSearch->exec();
    if(ret != QDialog::Accepted)
        return;
    QString str = dialogSearch->str();
    delete dialogSearch;

    char*  ch;
    QByteArray ba = str.toLatin1(); // must
    ch=ba.data();

    TrieNode* result;
    if(str == "")
        result = trie->pRoot;
    else
        result = trie->SearchNode(ch);
    if(result == NULL)
    {
        QString dlgTitle = "reslut";
        QString strInfo = "无该节点";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }

    if(label != NULL)
    {
        delete label;
        label = NULL;
    }

    if(progressBar != NULL)
    {
        delete progressBar;
        progressBar = NULL;
    }

    label = new QLabel();
    label->setMinimumWidth(150);
    progressBar = new QProgressBar();
    progressBar->setMaximumWidth(1000);
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    label->setText("排序中");
    progressBar->setValue(0);

    ui->statusbar->addWidget(label);
    ui->statusbar->addWidget(progressBar);

    threadB.set(trie,result);
    threadB.start();
}

void windowSort::sortInsideFrequencyFinish(QString str)
{
    threadB.wait();

    output(str);

    QString dlgTitle = "reslut";
    QString strInfo = "排序已完成";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);

    delete label;
    label = NULL;
    delete progressBar;
    progressBar = NULL;
}

void windowSort::updateProgressBarInside(int progress)
{
    progressBar->setValue(progress);
}

void windowSort::fontChange()
{
    QFont iniFont = ui->plainTextEdit->font();
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok,iniFont);
    if(ok)
        ui->plainTextEdit->setFont(font);
}
