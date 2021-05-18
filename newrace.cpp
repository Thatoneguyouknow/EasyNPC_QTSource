#include "newrace.h"
#include "ui_newrace.h"

newrace::newrace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newrace)
{
    ui->setupUi(this);
    // create asi stat combo boxes
    map<int, string>::const_iterator cit;
    for( cit=abbvStat.begin(); cit!=abbvStat.end(); cit++)
    {
        ui->primASIStat->addItem(QString::fromStdString(cit->second));
        ui->SecASIStat->addItem(QString::fromStdString(cit->second));
    }
    // create name style combo box
    map<int, Race>::iterator it;
    for( it=availableRaces.begin(); it!=availableRaces.end(); it++ )
    {
        ui->NamingStyle->addItem(QString::fromStdString(it->second.getsetName()));
    }
    connect(ui->Buttons, SIGNAL(accepted()), this, SLOT(save_clicked()));
}

newrace::newrace(int toEdit, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newrace)
{
    ui->setupUi(this);

    edit = true;
    raceToEdit = toEdit;

    // make any races created by users deleteable

    ui->raceName->setText(QString::fromStdString(availableRaces.at(toEdit).getsetName()));

    // create asi stat combo boxes
    map<int, string>::const_iterator cit;
    for( cit=abbvStat.begin(); cit!=abbvStat.end(); cit++)
    {
        ui->primASIStat->addItem(QString::fromStdString(cit->second));
        ui->SecASIStat->addItem(QString::fromStdString(cit->second));
    }
    // Set ASI stats
    ui->primASIStat->setCurrentIndex(availableRaces.at(toEdit).getsetPrimStat());
    ui->SecASIStat->setCurrentIndex(availableRaces.at(toEdit).getsetSecStat());
    // Set ASI Vals
    ui->PrimASIVal->setValue(availableRaces.at(toEdit).getsetPrimVal());
    ui->SecASIVal->setValue(availableRaces.at(toEdit).getsetSecVal());

    // Set min/max age
    ui->ageMax->setValue(availableRaces.at(toEdit).getsetMaxAge());
    ui->ageMin->setValue(availableRaces.at(toEdit).getsetMinAge());

    // create name style combo box
    map<int, Race>::iterator it;
    for( it=availableRaces.begin(); it!=availableRaces.end(); it++ )
    {
        ui->NamingStyle->addItem(QString::fromStdString(it->second.getsetName()));
    }
    //Set name type
    ui->NamingStyle->setCurrentIndex(availableRaces.at(toEdit).getsetNameType());

    connect(ui->Buttons, SIGNAL(accepted()), this, SLOT(save_clicked()));
}
newrace::~newrace()
{
    delete ui;
}

void newrace::save_clicked()
{
    if(edit)
    {
        availableRaces.at(raceToEdit).getsetName(true, ui->raceName->text().toStdString());
        availableRaces.at(raceToEdit).getsetPrimStat(true, ui->primASIStat->currentIndex());
        availableRaces.at(raceToEdit).getsetPrimVal(true, ui->PrimASIVal->value());
        availableRaces.at(raceToEdit).getsetSecStat(true, ui->SecASIStat->currentIndex());
        availableRaces.at(raceToEdit).getsetSecVal(true, ui->SecASIVal->value());
        availableRaces.at(raceToEdit).getsetMaxAge(true, ui->ageMax->value());
        availableRaces.at(raceToEdit).getsetMinAge(true, ui->ageMin->value());
        availableRaces.at(raceToEdit).getsetNameType(true, ui->NamingStyle->currentIndex());
    }
    else //Read values into a new race
    {
        string name = ui->raceName->text().toStdString();
        Race newRace = Race(name, ui->primASIStat->currentIndex(), ui->SecASIStat->currentIndex(),
                            ui->PrimASIVal->value(), ui->SecASIVal->value(),
                            ui->ageMax->value(), ui->ageMin->value(), ui->NamingStyle->currentIndex());
        availableRaces.insert(pair<int, Race>(newRace.getIdentifier(), newRace));
    }

    // signal event back to mainwindow to refresh the race list
    QDialog::done(0);
}
