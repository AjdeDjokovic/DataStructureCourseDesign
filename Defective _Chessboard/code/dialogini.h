#ifndef DIALOGINI_H
#define DIALOGINI_H

#include <QDialog>

namespace Ui {
class DialogIni;
}

class DialogIni : public QDialog
{
    Q_OBJECT

public:
    explicit DialogIni(QWidget *parent = nullptr);
    ~DialogIni();
    int getK();
    int getRow();
    int getCol();

private:
    Ui::DialogIni *ui;
};

#endif // DIALOGINI_H
