#include "raceview.h"
#include "ui_raceview.h"

raceview::raceview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::raceview)
{
    ui->setupUi(this);

    map<int, Race>::iterator it;
    for( it=availableRaces.begin(); it != availableRaces.end(); it++)
    {
        ui->raceList->addItem(QString::fromStdString(it->second.getsetName()));
    }
    connect(ui->raceList, &QListWidget::itemDoubleClicked, this, &raceview::on_race_dc);
}

raceview::~raceview()
{
    delete ui;
}

void raceview::refreshRace()
{
    ui->raceList->clear();
    map<int, Race>::iterator it;
    for( it=availableRaces.begin(); it != availableRaces.end(); it++)
    {
        ui->raceList->addItem(QString::fromStdString(it->second.getsetName()));
    }
}

void raceview::newRace()
{
    edit = new newrace(this);
    connect(edit, &QDialog::finished, this, &raceview::onRefreshSignal);
    edit->show();
}

void raceview::on_race_dc(QListWidgetItem* clicked)
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
        logError(raceErr, error, getlogDir());
        emit errorCaught(raceErr);
    }
    else
    {
        edit = new newrace(toDisplay, this);
        connect(edit, &QDialog::finished, this, &raceview::onRefreshSignal);
        edit->show();
    }
}

void raceview::onRefreshSignal()
{
    refreshRace();
}
