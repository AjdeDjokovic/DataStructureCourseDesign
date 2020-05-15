#ifndef DIALOGINSERTONLY_H
#define DIALOGINSERTONLY_H

#include <QDialog>

namespace Ui {
class DialogInsertOnly;
}

class DialogInsertOnly : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInsertOnly(QWidget *parent = nullptr);
    ~DialogInsertOnly();
    int key();
    QString str();

private:
    Ui::DialogInsertOnly *ui;
};

#endif // DIALOGINSERTONLY_H
