#ifndef WINDOWSORT_H
#define WINDOWSORT_H

#include <QMainWindow>
#include "trie.h"
#include <QMessageBox>
#include "threadsortfrequency.h"
#include "dialogsearch.h"
#include <QProgressBar>
#include <QLabel>
#include "threadsortinsidefrequency.h"
#include <QFontDialog>

namespace Ui {
class windowSort;
}

class windowSort : public QMainWindow
{
    Q_OBJECT

public:
    explicit windowSort(QWidget *parent = nullptr);
    ~windowSort();
    void set(Trie *);
    void sortFrequency();
    void sortFrequencyFinish(QString);
    void sortTrie();
    void output(QString);
    void searchRow();
    void updateProgressBar(int,int);
    void sortInsideFrequency();
    void sortInsideFrequencyFinish(QString);
    void updateProgressBarInside(int);
    void fontChange();
private:
    Ui::windowSort *ui;
    Trie * trie;
    threadSortFrequency threadA;
    threadSortInsideFrequency threadB;
    void iniSignol();
    QProgressBar * progressBar = NULL;
    QLabel * label = NULL;
};

#endif // WINDOWSORT_H
