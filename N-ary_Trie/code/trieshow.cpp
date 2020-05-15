#include "trieshow.h"
#include "ui_trieshow.h"

trieShow::trieShow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::trieShow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->graphicsView);
    this->setWindowState(Qt::WindowMaximized);

    iniSignol();
}

trieShow::~trieShow()
{
    delete ui;
}

void trieShow::set(Trie * trie)
{
    this->trie = trie;
    showFunction();
}
void trieShow::iniSignol()
{
    connect(ui->actCentre,&QAction::triggered,this,&trieShow::centre);
    connect(ui->actSearch,&QAction::triggered,this,&trieShow::search);
}

void trieShow::showFunction()
{
    double r = 20;  //节点半径
    double height = trie->pRoot->height;
    double h = 50 * pow(10,height);
//    int h = 500;
    double sceneHeight = height * h + 4 * r;
    double sceneWigth = (2 * pow(26,height) + 1) * r * 2;
    QRectF rect(- sceneWigth * 0.5,- sceneHeight * 0.5,sceneWigth,sceneHeight);

    if(scene != NULL)
    {
        scene->clear();
        delete scene;
        scene = NULL;
    }

    scene = new QGraphicsScene(rect);
    ui->graphicsView->setScene(scene);


    QGraphicsEllipseItem * item = new QGraphicsEllipseItem(-r,-r,2 * r , 2* r);
    item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    item->setPos(0,- sceneHeight * 0.5 + 2 * r);
    QPen pen;
    pen.setWidth(3);
    item->setPen(pen);
    scene->addItem(item);
    ui->graphicsView->centerOn(0,- sceneHeight * 0.5 + 2 * r);

    std::stack<stackNode> s;
    for(int i = 0;i < 26;i++)
    {
        if(trie->pRoot->nextBranch[i] != NULL)
        {
            stackNode node(trie->pRoot->nextBranch[i],QPointF(0,- sceneHeight * 0.5 + 2 * r),i,trie->pRoot->height);
            s.push(node);
        }
    }

    while(!s.empty())
    {
        stackNode curStackNode = s.top();
        s.pop();

        qreal dis = 2 * r * pow(26,curStackNode.level - 1) * 2;

        qreal start = curStackNode.parentPos.x() - 12.5 * dis;

        QGraphicsEllipseItem * item1 = new QGraphicsEllipseItem(-r,-r,2 * r , 2* r);
        item1->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        item1->setPos(start + curStackNode.queue * dis,curStackNode.parentPos.y() + h);
        pen.setWidth(3);
        item1->setPen(pen);
        scene->addItem(item1);
        QGraphicsLineItem * item2 = new QGraphicsLineItem();
        pen.setWidth(2);
        item2->setPen(pen);
        item2->setLine(curStackNode.parentPos.x(),curStackNode.parentPos.y() + r,start + curStackNode.queue * dis,curStackNode.parentPos.y() + h - r);
        scene->addItem(item2);
        QGraphicsSimpleTextItem * item3 = new QGraphicsSimpleTextItem();
        QFont font = item3->font();
        font.setPointSize(r * 0.75);
        item3->setFont(font);
        item3->setText(QString(curStackNode.node->c));
        item3->setPos(start + curStackNode.queue * dis - r * 0.3,curStackNode.parentPos.y() + h - r * 0.70);
        scene->addItem(item3);
        for(int i = 0;i < 26;i++)
        {
            if(curStackNode.node->nextBranch[i] != NULL)
            {
                stackNode node(curStackNode.node->nextBranch[i],QPointF(start + curStackNode.queue * dis,curStackNode.parentPos.y() + h),i,curStackNode.level - 1);
                s.push(node);
            }
        }
    }
}

void trieShow::centre()
{
    DialogSearch* dialogSearch = new DialogSearch(this);
    Qt::WindowFlags flags = dialogSearch->windowFlags();
    dialogSearch->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dialogSearch->exec();
    if(ret != QDialog::Accepted)
        return;
    QString str = dialogSearch->str();
    char*  ch;
    QByteArray ba = str.toLatin1(); // must
    ch=ba.data();
    delete dialogSearch;


    double r = 20;  //节点半径
    double height = trie->pRoot->height;
    double h = 50 * pow(10,height);
//    int h = 500;
    double sceneHeight = height * h + 4 * r;
    double sceneWigth = (2 * pow(26,height) + 1) * r * 2;

    double pointWidth = 0;
    double pointHeight = - sceneHeight * 0.5 + 2 * r;

    if(str == "")
    {
        ui->graphicsView->centerOn(0,- sceneHeight * 0.5 + 2 * r);
        return;
    }


    for(int i = 0;i < strlen(ch);i++)
    {
        qreal dis = 2 * r * pow(26,--height) * 2;
        pointWidth = pointWidth - 12.5 * dis + (ch[i] - 'a') * dis;
        pointHeight += h;
    }
    ui->graphicsView->centerOn(pointWidth,pointHeight);
}

void trieShow::search()
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

    if(str == "")
    {
        showFunction();
        return;
    }
    TrieNode* result = trie->SearchNode(ch);
    if(result == NULL)
    {
        QString dlgTitle = "warning";
        QString strInfo = "没有所查询的字符串";
        QMessageBox::warning(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    searchDraw(result,ch);
}

void trieShow::searchDraw(TrieNode* node,char * str)
{
    double r = 20;  //节点半径
    double height = node->height;
    double h = 50 * pow(10,height);
//    int h = 500;
    double sceneHeight = height * h + 4 * r + strlen(str) * h;
    double sceneWigth = (2 * pow(26,height) + 1) * r * 2;
    QRectF rect(- sceneWigth * 0.5,- sceneHeight * 0.5,sceneWigth,sceneHeight);

    if(scene != NULL)
    {
        scene->clear();
        delete scene;
        scene = NULL;
    }

    scene = new QGraphicsScene(rect);
    ui->graphicsView->setScene(scene);

    QGraphicsEllipseItem * item = new QGraphicsEllipseItem(-r,-r,2 * r , 2* r);
    item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    item->setPos(0,- sceneHeight * 0.5 + 2 * r);
    QPen pen;
    pen.setWidth(3);
    item->setPen(pen);
    scene->addItem(item);
    ui->graphicsView->centerOn(0,- sceneHeight * 0.5 + 2 * r);

    for(int i = 0;i < strlen(str);i++)
    {
        QGraphicsEllipseItem * item1 = new QGraphicsEllipseItem(-r,-r,2 * r , 2* r);
        item1->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        item1->setPos(0,- sceneHeight * 0.5 + 2 * r + (i + 1) * h);
        pen.setWidth(3);
        item1->setPen(pen);
        scene->addItem(item1);
        QGraphicsLineItem * item2 = new QGraphicsLineItem();
        pen.setWidth(2);
        item2->setPen(pen);
        item2->setLine(0,- sceneHeight * 0.5 + 2 * r + r + i * h,0,- sceneHeight * 0.5 + 2 * r + (i + 1) * h - r);
        scene->addItem(item2);
        QGraphicsSimpleTextItem * item3 = new QGraphicsSimpleTextItem();
        QFont font = item3->font();
        font.setPointSize(r * 0.75);
        item3->setFont(font);
        item3->setText(QString(str[i]));
        item3->setPos(0 - r * 0.3,- sceneHeight * 0.5 + 2 * r + (i + 1) * h - r * 0.70);
        scene->addItem(item3);
    }

    std::stack<stackNode> s;
    for(int i = 0;i < 26;i++)
    {
        if(node->nextBranch[i] != NULL)
        {
            s.push(stackNode(node->nextBranch[i],QPointF(0,- sceneHeight * 0.5 + 2 * r + strlen(str) * h),i,node->height));
        }
    }

    while(!s.empty())
    {
        stackNode curStackNode = s.top();
        s.pop();

        qreal dis = 2 * r * pow(26,curStackNode.level - 1) * 2;

        qreal start = curStackNode.parentPos.x() - 12.5 * dis;

        QGraphicsEllipseItem * item1 = new QGraphicsEllipseItem(-r,-r,2 * r , 2* r);
        item1->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        item1->setPos(start + curStackNode.queue * dis,curStackNode.parentPos.y() + h);
        pen.setWidth(3);
        item1->setPen(pen);
        scene->addItem(item1);
        QGraphicsLineItem * item2 = new QGraphicsLineItem();
        pen.setWidth(2);
        item2->setPen(pen);
        item2->setLine(curStackNode.parentPos.x(),curStackNode.parentPos.y() + r,start + curStackNode.queue * dis,curStackNode.parentPos.y() + h - r);
        scene->addItem(item2);
        QGraphicsSimpleTextItem * item3 = new QGraphicsSimpleTextItem();
        QFont font = item3->font();
        font.setPointSize(r * 0.75);
        item3->setFont(font);
        item3->setText(QString(curStackNode.node->c));
        item3->setPos(start + curStackNode.queue * dis - r * 0.3,curStackNode.parentPos.y() + h - r * 0.70);
        scene->addItem(item3);


        for(int i = 0;i < 26;i++)
        {
            if(curStackNode.node->nextBranch[i] != NULL)
            {
                stackNode node(curStackNode.node->nextBranch[i],QPointF(start + curStackNode.queue * dis,curStackNode.parentPos.y() + h),i,curStackNode.level - 1);
                s.push(node);
            }
        }
    }

}

