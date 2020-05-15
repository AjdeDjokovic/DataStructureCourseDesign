#ifndef DIALOGINSERTMORE_H
#define DIALOGINSERTMORE_H

#include <QDialog>

namespace Ui {
class DialogInsertMore;
}

class DialogInsertMore : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInsertMore(QWidget *parent = nullptr);
    ~DialogInsertMore();
    QString str();
private:
    Ui::DialogInsertMore *ui;
};

#endif // DIALOGINSERTMORE_H
