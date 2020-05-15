#include "dialogsize.h"
#include "ui_dialogsize.h"

DialogSize::DialogSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSize)
{
    ui->setupUi(this);
}

DialogSize::~DialogSize()
{
    delete ui;
}

int DialogSize::size()
{
    return ui->spinBox->value();
}

int DialogSize::length()
{
    return ui->spinBox_2->value();
}

void DialogSize::setDefault(int value,int length,bool standard)
{
    ui->spinBox->setValue(value);
    ui->spinBox_2->setValue(length);
    if(standard)
    {
        ui->label->setVisible(false);
        ui->spinBox->setVisible(false);
    }
}
