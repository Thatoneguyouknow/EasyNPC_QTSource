#include "racecard.h"
#include "ui_racecard.h"

RaceCard::RaceCard(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RaceCard)
{
    ui->setupUi(this);
    Id = id;
    setUpWidget();
}

RaceCard::~RaceCard()
{
    delete ui;
}

void RaceCard::setUpWidget()
{
    string asi_p = "";
    string asi_s = "";
    string age = "";

    string stat = statNames.at(availableRaces.at(Id).getsetPrimStat());
    asi_p = asi_p.append(stat);
    asi_p = asi_p.append(" - ");
    asi_p = asi_p.append(to_string(availableRaces.at(Id).getsetPrimVal()));

    stat = statNames.at(availableRaces.at(Id).getsetSecStat());
    asi_s = asi_s.append(stat);
    asi_s = asi_s.append(" - ");
    asi_s = asi_s.append(to_string(availableRaces.at(Id).getsetSecVal()));

    age = age.append(to_string(availableRaces.at(Id).getsetMinAge()));
    age = age.append(" - ");
    age = age.append(to_string(availableRaces.at(Id).getsetMaxAge()));

    try {
        ui->Name->setText(QString::fromStdString(availableRaces.at(Id).getsetName()));
        ui->PrimASI->setText(QString::fromStdString(asi_p));
        ui->SecASI->setText(QString::fromStdString(asi_s));
        ui->Age->setText(QString::fromStdString(age));
    }  catch (...) {
        QString error = "Card cannot be read: ";
        error.append(QString::number(Id));
        logError(rReadErr, error);
        emit errorCaught(rReadErr);

        // Set defaults "Jeff"
        ui->Name->setText("Jeff");
    }
}

void RaceCard::paintEvent(QPaintEvent *p2)
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
