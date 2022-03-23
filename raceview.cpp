#include "raceview.h"
#include "ui_raceview.h"

RaceView::RaceView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RaceView)
{
    ui->setupUi(this);

    map<int, Race>::iterator it;
    for( it=availableRaces.begin(); it != availableRaces.end(); it++)
    {
        ui->RaceList->addItem(QString::fromStdString(it->second.getsetName()));
    }
    connect(ui->RaceList, &QListWidget::itemDoubleClicked, this, &RaceView::on_race_dc);
}

RaceView::~RaceView()
{
    delete ui;
}

void RaceView::refreshRace()
{
    ui->RaceList->clear();
    map<int, Race>::iterator it;
    for( it=availableRaces.begin(); it != availableRaces.end(); it++)
    {
        ui->RaceList->addItem(QString::fromStdString(it->second.getsetName()));
    }
}

void RaceView::newRace()
{
    edit = new NewRace(this);
    connect(edit, &QDialog::finished, this, &RaceView::onRefreshSignal);
    edit->show();
}

void RaceView::on_race_dc(QListWidgetItem* clicked)
{
    int toDisplay = -1;
    map<int, Race>::iterator it;
    for( it=availableRaces.begin(); it != availableRaces.end(); it++ )
    {
        if( it->second.getsetName().compare(clicked->text().toStdString()) == 0 )
        {
            toDisplay = it->first;
        }
    }
    if( toDisplay < 0 )
    {
        // log error
        QString error = "Race not found: ";
        error.append(clicked->text());
        logError(raceErr, error);
        emit errorCaught(raceErr);
    }
    else
    {
        edit = new NewRace(toDisplay, this);
        connect(edit, &QDialog::finished, this, &RaceView::onRefreshSignal);
        edit->show();
    }
}

void RaceView::onRefreshSignal()
{
    refreshRace();
}
