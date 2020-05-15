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


QString DialogIni::getContent()
{
    return ui->plainTextEdit->toPlainText();
}
