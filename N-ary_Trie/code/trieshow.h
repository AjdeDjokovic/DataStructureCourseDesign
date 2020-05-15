#ifndef TRIESHOW_H
#define TRIESHOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "trie.h"
#include <QPoint>
#include <QGraphicsItem>
#include <stack>
#include "stacknode.h"
#include <math.h>
#include "dialogsearch.h"
#include <QMessageBox>

namespace Ui {
class trieShow;
}

class trieShow : public QMainWindow
{
    Q_OBJECT

public:
    explicit trieShow(QWidget *parent = nullptr);
    ~trieShow();
    void set(Trie *);
    void showFunction();
    void centre();
    void search();
    void searchDraw(TrieNode*,char*);

private:
    Ui::trieShow *ui;
    Trie * trie;
    QGraphicsScene * scene = NULL;
    void iniSignol();



};

#endif // TRIESHOW_H
