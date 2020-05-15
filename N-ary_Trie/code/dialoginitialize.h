#ifndef DIALOGINITIALIZE_H
#define DIALOGINITIALIZE_H

#include <QDialog>

namespace Ui {
class DialogInitialize;
}

class DialogInitialize : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInitialize(QWidget *parent = nullptr);
    ~DialogInitialize();
    QString str();

private:
    Ui::DialogInitialize *ui;
};

#endif // DIALOGINITIALIZE_H
