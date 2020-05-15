#ifndef DIALOGSIZE_H
#define DIALOGSIZE_H

#include <QDialog>

namespace Ui {
class DialogSize;
}

class DialogSize : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSize(QWidget *parent = nullptr);
    ~DialogSize();
    int size();
    int length();
    void setDefault(int,int,bool);

private:
    Ui::DialogSize *ui;
};

#endif // DIALOGSIZE_H
