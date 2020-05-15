#include "dialoginsertmore.h"
#include "ui_dialoginsertmore.h"

DialogInsertMore::DialogInsertMore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInsertMore)
{
    ui->setupUi(this);
}

DialogInsertMore::~DialogInsertMore()
{
    delete ui;
}

QString DialogInsertMore::str()
{
    return ui->textEdit->toPlainText();
}
