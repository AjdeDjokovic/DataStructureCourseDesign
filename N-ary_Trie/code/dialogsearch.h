#ifndef DIALOGSEARCH_H
#define DIALOGSEARCH_H

#include <QDialog>

namespace Ui {
class DialogSearch;
}

class DialogSearch : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSearch(QWidget *parent = nullptr);
    ~DialogSearch();
    QString str();
    void setDefault(QString);

private:
    Ui::DialogSearch *ui;
};

#endif // DIALOGSEARCH_H
