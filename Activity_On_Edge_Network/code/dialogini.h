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
    QString getContent();

private:
    Ui::DialogIni *ui;
};

#endif // DIALOGINI_H
