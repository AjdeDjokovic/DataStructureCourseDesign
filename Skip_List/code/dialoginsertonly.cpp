#include "dialoginsertonly.h"
#include "ui_dialoginsertonly.h"

DialogInsertOnly::DialogInsertOnly(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInsertOnly)
{
    ui->setupUi(this);
}

DialogInsertOnly::~DialogInsertOnly()
{
    delete ui;
}

int DialogInsertOnly::key()
{
    return ui->spinBox->value();
}

QString DialogInsertOnly::str()
{
    return ui->lineEdit->text();
}
