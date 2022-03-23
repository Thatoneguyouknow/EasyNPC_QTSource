#include "classcard.h"
#include "ui_classcard.h"

ClassCard::ClassCard(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClassCard)
{
    ui->setupUi(this);
    Id = id;
    setUpWidget();
}

ClassCard::~ClassCard()
{
    delete ui;
}

void ClassCard::setUpWidget()
{
    array<int, 6> priority = availableClasses.at(Id).getsetPriority();
    try {
        ui->Name->setText(QString::fromStdString(availableClasses.at(Id).getsetName()));
        ui->HitDie->setText(QString::number(availableClasses.at(Id).getsetHitDie()));
        ui->Stat1->setText(QString::fromStdString(abbvStat.at(priority[0])));
        ui->Stat2->setText(QString::fromStdString(abbvStat.at(priority[1])));
        ui->Stat3->setText(QString::fromStdString(abbvStat.at(priority[2])));
        ui->Stat4->setText(QString::fromStdString(abbvStat.at(priority[3])));
        ui->Stat5->setText(QString::fromStdString(abbvStat.at(priority[4])));
        ui->Stat6->setText(QString::fromStdString(abbvStat.at(priority[5])));
    }  catch (...) {
        QString error = "Card cannot be read: ";
        error.append(QString::number(Id));
        logError(cReadErr, error);
        emit errorCaught(cReadErr);

        // Set defaults "Jeff"
        ui->Name->setText("Jeff");
    }
}

void ClassCard::paintEvent(QPaintEvent *p2)
{
    try {
        QPixmap bkgnd(":/Images/Card.png");
        QPainter paint(this);
        paint.drawPixmap(-10, 0, 170, 170, bkgnd);
        QWidget::paintEvent(p2);
    }  catch (...) {
        QString error = "Image paint error";
        logError(paintErr, error);
        emit errorCaught(paintErr);
    }
}
