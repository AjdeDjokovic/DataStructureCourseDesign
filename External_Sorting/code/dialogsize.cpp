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

void DialogSize::setDefault(qint64 value,QString str)
{
    ui->spinBox->setValue(value);
    ui->label->setText(str);
}
