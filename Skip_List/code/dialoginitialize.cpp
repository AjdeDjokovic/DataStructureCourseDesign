#include "dialoginitialize.h"
#include "ui_dialoginitialize.h"

DialogInitialize::DialogInitialize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInitialize)
{
    ui->setupUi(this);
}

DialogInitialize::~DialogInitialize()
{
    delete ui;
}

int DialogInitialize::maxKey()
{
    return ui->spinBox->value();
}

QString DialogInitialize::str()
{
    return ui->textEdit->toPlainText();
}
