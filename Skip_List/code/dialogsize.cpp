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

int DialogSize::maxKey()
{
    return ui->spinBox->value();
}

int DialogSize::listSize()
{
    return ui->spinBox_2->value();
}
