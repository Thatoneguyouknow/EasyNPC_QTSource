#include "editclass.h"
#include "ui_editclass.h"

editClass::editClass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editClass)
{
    ui->setupUi(this);
}

editClass::~editClass()
{
    delete ui;
}
