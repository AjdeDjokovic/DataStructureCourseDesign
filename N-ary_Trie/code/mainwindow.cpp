#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();
    ui->tabWidget->tabsClosable();
    this->setCentralWidget(ui->tabWidget);
    this->setWindowState(Qt::WindowMaximized);

    iniSignol();
    iniTool(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniSignol()
{
    connect(ui->actInputIni,&QAction::triggered,this,&MainWindow::inputIni);
    connect(ui->actFileIni,&QAction::triggered,this,&MainWindow::fileIni);
    connect(&threadB,&threadFileIni::result,this,&MainWindow::fileIniFinish);
    connect(ui->actDelete,&QAction::triggered,this,&MainWindow::deleteTrie);
    connect(ui->actDeleteNode,&QAction::triggered,this,&MainWindow::deleteNode);
    connect(ui->actInsert,&QAction::triggered,this,&MainWindow::insert);

    connect(ui->actOpenGrafic,&QAction::triggered,this,&MainWindow::openGrafic);
    connect(ui->actOpenSort,&QAction::triggered,this,&MainWindow::openSort);
    connect(ui->actOpenFile,&QAction::triggered,this,&MainWindow::openFile);
    connect(ui->tabWidget,&QTabWidget::tabCloseRequested,this,&MainWindow::on_tabWidget_tabCloseRequested);
    connect(ui->tabWidget,&QTabWidget::currentChanged,this,&MainWindow::on_tabWidget_currentChanged);
    connect(ui->actRestart,&QAction::triggered,this,&MainWindow::restart);
}

void MainWindow::iniTool(bool flag)
{
    ui->actInputIni->setEnabled(!flag);
    ui->actFileIni->setEnabled(!flag);
    ui->actDelete->setEnabled(flag);
    ui->actDeleteNode->setEnabled(flag);
    ui->actInsert->setEnabled(flag);
    ui->actOpenGrafic->setEnabled(flag);
    ui->actOpenSort->setEnabled(flag);
    ui->actOpenFile->setEnabled(true);
}

void MainWindow::inputIni()
{
    DialogInitialize* dialogInitialize = new DialogInitialize(this);
    Qt::WindowFlags flags = dialogInitialize->windowFlags();
    dialogInitialize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dialogInitialize->exec();
    if(ret != QDialog::Accepted)
        return;
    QString str = dialogInitialize->str();
    std::string s = str.toStdString();
    for(int i = 0;i < str.length();i++)
        if(!isalpha(s[i]))
            s[i] = ' ';
    str = QString::fromStdString(s);
    str = str.toLower();
    delete dialogInitialize;

    trie = new Trie();
    int row = 1;
    QStringList list = str.split(QRegExp("\n"),QString::SkipEmptyParts);
    foreach(QString num, list)
    {
        QStringList subList = num.split(QRegExp("\\s"),QString::SkipEmptyParts);
        foreach(QString subNum,subList)
        {
            char*  ch;
            QByteArray ba = subNum.toLatin1(); // must
            ch=ba.data();
            trie->Insert(ch,row);
        }
        row++;
    }

    QString dlgTitle = "reslut";
    QString strInfo = "初始化已完成";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);

    iniTool(true);
}

//void MainWindow::trieShowFunction()
//{
//    int r = 20;  //节点半径
//    int height = trie->pRoot->height;
//    int h = 50 * pow(10,height);
////    int h = 500;
//    int sceneHeight = height * h + 4 * r;
//    int sceneWigth = (2 * pow(26,height) + 1) * r * 2;
//    QRectF rect(- sceneWigth * 0.5,- sceneHeight * 0.5,sceneWigth,sceneHeight);

//    if(scene != NULL)
//    {
//        delete scene;
//        scene = NULL;
//    }

//    scene = new QGraphicsScene(rect);
//    ui->graphicsView->setScene(scene);


//    QGraphicsEllipseItem * item = new QGraphicsEllipseItem(-r,-r,2 * r , 2* r);
//    item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
//    item->setPos(0,- sceneHeight * 0.5 + 2 * r);
//    QPen pen;
//    pen.setWidth(3);
//    item->setPen(pen);
//    scene->addItem(item);
//    ui->graphicsView->centerOn(0,- sceneHeight * 0.5 + 2 * r);

//    std::stack<stackNode> s;
//    for(int i = 0;i < 26;i++)
//    {
//        if(trie->pRoot->nextBranch[i] != NULL)
//        {
//            stackNode node(trie->pRoot->nextBranch[i],QPointF(0,- sceneHeight * 0.5 + 2 * r),i,trie->pRoot->height);
//            s.push(node);
//        }
//    }

//    while(!s.empty())
//    {
//        stackNode curStackNode = s.top();
//        s.pop();

//        qreal dis = 2 * r * pow(26,curStackNode.level - 1) * 2;

//        qreal start = curStackNode.parentPos.x() - 12.5 * dis;

//        QGraphicsEllipseItem * item1 = new QGraphicsEllipseItem(-r,-r,2 * r , 2* r);
//        item1->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
//        item1->setPos(start + curStackNode.queue * dis,curStackNode.parentPos.y() + h);
//        pen.setWidth(3);
//        item1->setPen(pen);
//        scene->addItem(item1);
//        QGraphicsLineItem * item2 = new QGraphicsLineItem();
//        pen.setWidth(2);
//        item2->setPen(pen);
//        item2->setLine(curStackNode.parentPos.x(),curStackNode.parentPos.y() + r,start + curStackNode.queue * dis,curStackNode.parentPos.y() + h - r);
//        scene->addItem(item2);
//        QGraphicsSimpleTextItem * item3 = new QGraphicsSimpleTextItem();
//        QFont font = item3->font();
//        font.setPointSize(r * 0.75);
//        item3->setFont(font);
//        item3->setText(QString(curStackNode.node->c));
//        item3->setPos(start + curStackNode.queue * dis - r * 0.3,curStackNode.parentPos.y() + h - r * 0.70);
//        scene->addItem(item3);


//        for(int i = 0;i < 26;i++)
//        {
//            if(curStackNode.node->nextBranch[i] != NULL)
//            {
//                stackNode node(curStackNode.node->nextBranch[i],QPointF(start + curStackNode.queue * dis,curStackNode.parentPos.y() + h),i,curStackNode.level - 1);
//                s.push(node);
//            }
//        }
//    }
//}

//void MainWindow::search()
//{
//    DialogSearch* dialogSearch = new DialogSearch(this);
//    Qt::WindowFlags flags = dialogSearch->windowFlags();
//    dialogSearch->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
//    int ret = dialogSearch->exec();
//    if(ret != QDialog::Accepted)
//        return;
//    QString str = dialogSearch->str();
//    delete dialogSearch;

//    char*  ch;
//    QByteArray ba = str.toLatin1(); // must
//    ch=ba.data();

//    if(str == "")
//    {
//        trieShowFunction();
//        trieSort(trie->pRoot);
//        return;
//    }


//    TrieNode* result = trie->Search(ch);
//    if(result == NULL)
//    {
//        QString dlgTitle = "warning";
//        QString strInfo = "没有所查询的字符串";
//        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
//        return;
//    }

//    searchDraw(result,ch);
//    trieSort(result);

//}

//void MainWindow::searchDraw(TrieNode* node,char * str)
//{
//    int r = 20;  //节点半径
//    int height = node->height;
//    int h = 50 * pow(10,height);
////    int h = 500;
//    int sceneHeight = height * h + 4 * r + strlen(str) * h;
//    int sceneWigth = (2 * pow(26,height) + 1) * r * 2;
//    QRectF rect(- sceneWigth * 0.5,- sceneHeight * 0.5,sceneWigth,sceneHeight);

//    if(scene != NULL)
//    {
//        delete scene;
//        scene = NULL;
//    }

//    scene = new QGraphicsScene(rect);
//    ui->graphicsView->setScene(scene);

//    QGraphicsEllipseItem * item = new QGraphicsEllipseItem(-r,-r,2 * r , 2* r);
//    item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
//    item->setPos(0,- sceneHeight * 0.5 + 2 * r);
//    QPen pen;
//    pen.setWidth(3);
//    item->setPen(pen);
//    scene->addItem(item);

//    for(int i = 0;i < strlen(str);i++)
//    {
//        QGraphicsEllipseItem * item1 = new QGraphicsEllipseItem(-r,-r,2 * r , 2* r);
//        item1->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
//        item1->setPos(0,- sceneHeight * 0.5 + 2 * r + (i + 1) * h);
//        pen.setWidth(3);
//        item1->setPen(pen);
//        scene->addItem(item1);
//        QGraphicsLineItem * item2 = new QGraphicsLineItem();
//        pen.setWidth(2);
//        item2->setPen(pen);
//        item2->setLine(0,- sceneHeight * 0.5 + 2 * r + r + i * h,0,- sceneHeight * 0.5 + 2 * r + (i + 1) * h - r);
//        scene->addItem(item2);
//        QGraphicsSimpleTextItem * item3 = new QGraphicsSimpleTextItem();
//        QFont font = item3->font();
//        font.setPointSize(r * 0.75);
//        item3->setFont(font);
//        item3->setText(QString(str[i]));
//        item3->setPos(0 - r * 0.3,- sceneHeight * 0.5 + 2 * r + (i + 1) * h - r * 0.70);
//        scene->addItem(item3);
//    }

//    std::stack<stackNode> s;
//    for(int i = 0;i < 26;i++)
//    {
//        if(node->nextBranch[i] != NULL)
//        {
//            s.push(stackNode(node->nextBranch[i],QPointF(0,- sceneHeight * 0.5 + 2 * r + strlen(str) * h),i,node->height));
//        }
//    }

//    while(!s.empty())
//    {
//        stackNode curStackNode = s.top();
//        s.pop();

//        qreal dis = 2 * r * pow(26,curStackNode.level - 1) * 2;

//        qreal start = curStackNode.parentPos.x() - 12.5 * dis;

//        QGraphicsEllipseItem * item1 = new QGraphicsEllipseItem(-r,-r,2 * r , 2* r);
//        item1->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
//        item1->setPos(start + curStackNode.queue * dis,curStackNode.parentPos.y() + h);
//        pen.setWidth(3);
//        item1->setPen(pen);
//        scene->addItem(item1);
//        QGraphicsLineItem * item2 = new QGraphicsLineItem();
//        pen.setWidth(2);
//        item2->setPen(pen);
//        item2->setLine(curStackNode.parentPos.x(),curStackNode.parentPos.y() + r,start + curStackNode.queue * dis,curStackNode.parentPos.y() + h - r);
//        scene->addItem(item2);
//        QGraphicsSimpleTextItem * item3 = new QGraphicsSimpleTextItem();
//        QFont font = item3->font();
//        font.setPointSize(r * 0.75);
//        item3->setFont(font);
//        item3->setText(QString(curStackNode.node->c));
//        item3->setPos(start + curStackNode.queue * dis - r * 0.3,curStackNode.parentPos.y() + h - r * 0.70);
//        scene->addItem(item3);


//        for(int i = 0;i < 26;i++)
//        {
//            if(curStackNode.node->nextBranch[i] != NULL)
//            {
//                stackNode node(curStackNode.node->nextBranch[i],QPointF(start + curStackNode.queue * dis,curStackNode.parentPos.y() + h),i,curStackNode.level - 1);
//                s.push(node);
//            }
//        }
//    }

//}

//void MainWindow::trieSort(TrieNode* node)
//{
//    std::vector<SortItem> v;
//    trie->sortPre(node,v);
//    QString str;
//    for (std::vector<SortItem>::iterator i = v.begin();i != v.end();i++)
//        str += QString(QLatin1String(i->word)) + ":" + QString::number(i->count) + "\t";
//    output(str);
//}

//void MainWindow::output(QString str)
//{
//    ui->plainTextEdit->clear();
//    ui->plainTextEdit->appendPlainText(str);
//}

//void MainWindow::createFile()
//{
//    QString curPath = QDir::currentPath();
//    QString aFileName = QFileDialog::getSaveFileName(this,"选择生成文本文件",curPath,"(*.txt)");
//    if(aFileName.isEmpty())
//        return;
//    DialogSize* dialogSize = new DialogSize(this);
//    Qt::WindowFlags flags = dialogSize->windowFlags();
//    dialogSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
//    dialogSize->setDefault(1000,3);
//    int ret = dialogSize->exec();
//    if(ret != QDialog::Accepted)
//        return;
//    int size = dialogSize->size();
//    int length = dialogSize->length();
//    threadA.set(aFileName,size,length);
//    threadA.start();
//}

//void MainWindow::createFileFinish(QString)
//{
//    threadA.wait();

//    QString dlgTitle = "reslut";
//    QString strInfo = "数据文件已生成";
//    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
//}

void MainWindow::fileIni()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this,"选择生成文本文件",curPath,"(*.txt)");
    if(aFileName.isEmpty())
        return;

    trie = new Trie();
    threadB.set(trie,aFileName);
    threadB.start();
}

void MainWindow::fileIniFinish()
{
    threadB.wait();

    QString dlgTitle = "reslut";
    QString strInfo = "初始化已完成";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);

    iniTool(true);
}

//void MainWindow::centre()
//{
//    DialogSearch* dialogSearch = new DialogSearch(this);
//    Qt::WindowFlags flags = dialogSearch->windowFlags();
//    dialogSearch->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
//    int ret = dialogSearch->exec();
//    if(ret != QDialog::Accepted)
//        return;
//    QString str = dialogSearch->str();
//    char*  ch;
//    QByteArray ba = str.toLatin1(); // must
//    ch=ba.data();
//    delete dialogSearch;


//    double r = 20;  //节点半径
//    double height = trie->pRoot->height;
//    double h = 50 * pow(10,height);
////    int h = 500;
//    double sceneHeight = height * h + 4 * r;
//    double sceneWigth = (2 * pow(26,height) + 1) * r * 2;

//    double pointWidth = 0;
//    double pointHeight = - sceneHeight * 0.5 + 2 * r;

//    if(str == "")
//    {
//        ui->graphicsView->centerOn(0,- sceneHeight * 0.5 + 2 * r);
//        return;
//    }


//    for(int i = 0;i < strlen(ch);i++)
//    {
//        qreal dis = 2 * r * pow(26,--height) * 2;
//        pointWidth = pointWidth - 12.5 * dis + (ch[i] - 'a') * dis;
//        pointHeight += h;
//    }
//    ui->graphicsView->centerOn(pointWidth,pointHeight);
//}

//void MainWindow::sortFrequency()
//{
//    DialogSearch* dialogSearch = new DialogSearch(this);
//    Qt::WindowFlags flags = dialogSearch->windowFlags();
//    dialogSearch->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
//    int ret = dialogSearch->exec();
//    if(ret != QDialog::Accepted)
//        return;
//    QString str = dialogSearch->str();
//    delete dialogSearch;

//    char*  ch;
//    QByteArray ba = str.toLatin1(); // must
//    ch=ba.data();

//    TrieNode* result;
//    if(str == "")
//        result = trie->pRoot;
//    else
//        result = trie->SearchNode(ch);
//    if(result == NULL)
//    {
//        QString dlgTitle = "reslut";
//        QString strInfo = "无该节点";
//        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
//        return;
//    }

//    threadC.set(trie,result);
//    threadC.start();
//}

//void MainWindow::sortFrequencyFinish(QString str)
//{
//    threadC.wait();

//    output(str);

//    QString dlgTitle = "reslut";
//    QString strInfo = "排序已完成";
//    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
//}

void MainWindow::deleteTrie()
{
    if(trie != NULL)
    {
        delete trie;
        trie = NULL;
    }
    ui->tabWidget->clear();

    iniTool(false);
}

void MainWindow::deleteNode()
{
    DialogSearch* dialogSearch = new DialogSearch(this);
    Qt::WindowFlags flags = dialogSearch->windowFlags();
    dialogSearch->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dialogSearch->setDefault("删除节点");
    int ret = dialogSearch->exec();
    if(ret != QDialog::Accepted)
        return;
    QString str = dialogSearch->str();
    delete dialogSearch;

    char* ch;
    QByteArray ba = str.toLatin1(); // must
    ch=ba.data();

//    TrieNode* result;
//    if(str == "")
//        result = trie->pRoot;
//    else
//        result = trie->SearchNode(ch);

//    if(result == NULL)
//    {
//        QString dlgTitle = "warning";
//        QString strInfo = "删除的节点不存在";
//        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
//        return;
//    }
//        trie->Destory(result);

    if(str == "")
    {
        deleteTrie();
        return;
    }
    if(trie->SearchNode(ch) == NULL)
    {
        QString dlgTitle = "warning";
        QString strInfo = "删除的节点不存在";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    trie->Remove(ch);

    QString dlgTitle = "information";
    QString strInfo = "删除成功";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);

    ui->tabWidget->clear();
}

void MainWindow::insert()
{
    DialogInsert * dialogInsert = new DialogInsert(this);
    Qt::WindowFlags flags = dialogInsert->windowFlags();
    dialogInsert->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dialogInsert->exec();
    if(ret != QDialog::Accepted)
        return;
    QString str = dialogInsert->str();
    int row = dialogInsert->row();
    delete dialogInsert;

    char* ch;
    QByteArray ba = str.toLatin1(); // must
    ch=ba.data();

    if(str == "")
    {
        QString dlgTitle = "warning";
        QString strInfo = "字符串不能为空";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }

    trie->Insert(ch,row);
    QString dlgTitle = "information";
    QString strInfo = "插入成功";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    ui->tabWidget->clear();
}


void MainWindow::openGrafic()
{
    trieShow * show = new trieShow(this);
    show->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(show,QString::asprintf("图形化界面 %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
    show->set(trie);
}

void MainWindow::openSort()
{
    windowSort * windowShow = new windowSort(this);
    windowShow->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(windowShow,QString::asprintf("排序界面 %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
    windowShow->set(trie);
}

void MainWindow::openFile()
{
    windowFile * windowShow = new windowFile(this);
    windowShow->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(windowShow,QString::asprintf("文件界面 %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if(index < 0)
        return;
    QWidget * aForm = ui->tabWidget->widget(index);
    aForm->close();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    bool en = ui->tabWidget->count() > 0;
    ui->tabWidget->setVisible(en);

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0,ui->menuBar->height() + 30,this->width(),this->height() - ui->menuBar->height() - 30,QPixmap(QDir::currentPath() + "/back.jpg"));
}

void MainWindow::restart()
{
    qApp->quit();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}

//a bc def rr e
//b er lc ty f


//a b c d e f g h i j k l m n o p q r s t u v w x y z        aa ab c d e f g h i j k l m n o p q r s t u v w x y z


//a b c d e f g h i j k l m n o p q r s t u v w x y z
//aa ab ac ad ae af ag ah ai aj ak al am an ao ap aq ar as at au av aw ax ay az
//ba bb bc bd be bf bg bh bi bj bk bl bm bn bo bp bq br bs bt bu bv bw bx by bz


//a b c d e f g h i j k l m n o p q r s t u v w x y z
//aa ab ac ad ae af ag ah ai aj ak al am an ao ap aq ar as at au av aw ax ay az
//ba bb bc bd be bf bg bh bi bj bk bl bm bn bo bp bq br bs bt bu bv bw bx by bz
//caa cab cac cad cae caf cag cah cai caj cak cal cam can cao cap caq car cas cat cau cav caw cax cay caz
