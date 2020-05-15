#include "dialogini.h"
#include "ui_dialogini.h"

DialogIni::DialogIni(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogIni)
{
    ui->setupUi(this);
}

DialogIni::~DialogIni()
{
    delete ui;
}

int DialogIni::getK()
{
    return ui->spinBox->value();
}

int DialogIni::getRow()
{
    return ui->spinBox_2->value();
}

int DialogIni::getCol()
{
    return ui->spinBox_3->value();
}
