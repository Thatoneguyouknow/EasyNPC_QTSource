#include "newclass.h"
#include "ui_newclass.h"

NewClass::NewClass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewClass)
{
    ui->setupUi(this);
    ui->HitDie->addItems(hitdieStrs);
    for( int i=0; i < (int)statNames.size(); i++ )
    {
        ui->StatList->addItem(QString::fromStdString(statNames.at(i)));
    }
    ui->DelButton->setDisabled(true);
    ui->DelButton->hide();
    connect(ui->Buttons, SIGNAL(accepted()), this, SLOT(on_Save_clicked()));
}

NewClass::NewClass(int toEdit, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewClass)
{
    ui->setupUi(this);

    edit = true;
    classToEdit = toEdit;

    //if(!availableClasses.at(toEdit).getsetUser())
    //{
        ui->DelButton->setDisabled(true);
        ui->DelButton->hide();
    //}

    ui->Name->setText(QString::fromStdString(availableClasses.at(toEdit).getsetName()));
    ui->HitDie->addItems(hitdieStrs);

    // Catch error 1113 from Stats.cpp
    int hitDiePos = getHdPos(availableClasses.at(toEdit).getsetHitDie());
    if(hitDiePos == -1)
    {
        // Error has already been logged, output error dialog to user
        constructErr(hdPosNotFound);
        // set Current Index to 0
        hitDiePos = 0;
    }
    ui->HitDie->setCurrentIndex(hitDiePos);

    int currentPriority;
    for(int i=0; i < (int)availableClasses.at(toEdit).getsetPriority().size(); i++ )
    {
        try {
            currentPriority = availableClasses.at(toEdit).getsetPriority().at(i);
            ui->StatList->addItem(QString::fromStdString(statNames.at(currentPriority)));
        }  catch (...) {
            // ErrorCode 1105
            constructErr(pListReadErr);
            QString error = "Priority List Failed Read";
            logError(pListReadErr, error, getlogDir());
            // clear StatList, and add default
            ui->StatList->clear();
            for( int i=0; i < (int)statNames.size(); i++ )
            {
                ui->StatList->addItem(QString::fromStdString(statNames.at(i)));
            }
            break;
        }
    }
    connect(ui->Buttons, SIGNAL(accepted()), this, SLOT(on_Save_clicked()));
    connect(ui->DelButton, &QPushButton::clicked, this, &NewClass::on_Delete_clicked);
}

int NewClass::getEdit()
{
    return classToEdit;
}


NewClass::~NewClass()
{
    delete ui;
}

void NewClass::constructErr(int err)
{
    emit errorCaught(err);
}

void NewClass::on_Save_clicked()
{
    if(edit)
    {
        availableClasses.at(classToEdit).getsetName(true, ui->Name->text().toStdString());

        // catch error 1112 from Stats.cpp
        int hitDieVal = searchHd(ui->HitDie->currentText().toStdString());
        if( hitDieVal == -1 )
        {
            // output error to user dialog
            emit errorCaught(hdNotFound);
            // Set HitDie to default: 4
            hitDieVal = 4;
        }
        availableClasses.at(classToEdit).getsetHitDie(true, hitDieVal);
        array<int, 6> stats;
        int stat;
        for( int i = 0; i < ui->StatList->count(); i++ )
        {
            // Catch error 1111 from Stats.cpp
            stat = searchStats(ui->StatList->item(i)->text().toStdString());
            if( stat == -1 )
            {
                // output error to user dialog
                emit errorCaught(statNotFound);
                // Set priority to default (STR, DEX, CON, INT, WIS, CHA)
                stats = {STRENGTH, DEXTERITY, CONSTITUTION, INTELLIGENCE, WISDOM, CHARISMA};
                // break out of the loop
                break;
            }
            stats[i] = stat;
        }
        availableClasses.at(classToEdit).getsetPriority(true, &stats);
    }
    else //Read values into a new class
    {
        string name = ui->Name->text().toStdString();
        string hitdie = ui->HitDie->currentText().toStdString();

        // Catch error 1112 from Stats.cpp
        int hd = searchHd(hitdie);
        if( hd == -1 )
        {
            // output error to user dialog
            emit errorCaught(hdNotFound);
            // set hd to default: 4
            hd = 4;
        }
        array<int, 6> stats;
        int stat;
        for( int i = 0; i < ui->StatList->count(); i++ )
        {
            // Catch error 1111 from Stats.cpp
            stat = searchStats(ui->StatList->item(i)->text().toStdString());
            if( stat == -1 )
            {
                // output error to user dialog
                emit errorCaught(statNotFound);
                // Set priority to default (STR, DEX, CON, INT, WIS, CHA)
                stats = {STRENGTH, DEXTERITY, CONSTITUTION, INTELLIGENCE, WISDOM, CHARISMA};
                // break out of the loop
                break;
            }
            stats[i] = stat;
        }
        Class newClass = Class(name, hd, stats, true);
        availableClasses.insert(pair<int, Class>(newClass.getClassID(), newClass));
    }
    // signal event back to mainwindow to refresh the class list

    QDialog::accept();
}

void NewClass::on_Delete_clicked()
{
    map<int, Class>::iterator it;
    it = availableClasses.find(classToEdit);

    // remove class from SQL
    removeClass(it->first);

    // remove race from availableClasses
    availableClasses.erase(it);

    // signal raceview to remove class from list
    QDialog::reject();
}
