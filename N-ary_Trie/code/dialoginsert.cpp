#include "dialoginsert.h"
#include "ui_dialoginsert.h"

DialogInsert::DialogInsert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInsert)
{
    ui->setupUi(this);
}

DialogInsert::~DialogInsert()
{
    delete ui;
}

QString DialogInsert::str()
{
    return ui->lineEdit->text();
}

int DialogInsert::row()
{
    return ui->spinBox->value();
}
