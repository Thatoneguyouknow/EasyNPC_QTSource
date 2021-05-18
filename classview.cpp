#include "classview.h"
#include "ui_classview.h"

classview::classview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::classview)
{
    ui->setupUi(this);

    map<int, Class>::iterator it;
    for( it=availableClasses.begin(); it!=availableClasses.end(); it++)
    {
        ui->ClassList->addItem(QString::fromStdString(it->second.getsetName()));
    }
    connect(ui->ClassList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_class_dc(QListWidgetItem*)));
}

classview::~classview()
{
    delete ui;
}

void classview::refreshClassList()
{
    ui->ClassList->clear();
    map<int, Class>::iterator it;
    for( it=availableClasses.begin(); it!=availableClasses.end(); it++)
    {
        ui->ClassList->addItem(QString::fromStdString(it->second.getsetName()));
    }
}

void classview::newClass()
{
    edit = new NewClass(this);
    connect(edit, &QDialog::accepted, this, &classview::onRefreshSignal);
    connect(edit, &QDialog::rejected, this, &classview::onClassDelete);
    connect(edit, &NewClass::errorCaught, this, &classview::recieveError);
    edit->show();
}

void classview::on_class_dc(QListWidgetItem* clicked)
{
    // Open a new character edit window (possibly from mainwindow for parenthood)
    // Get the index of the generator (based on position in list? Based on name?)
    // Display generator in character edit window
    int toDisplay = -1;
    map<int, Class>::iterator it;
    for ( it=availableClasses.begin(); it != availableClasses.end() ; it++ )
    {
        if( it->second.getsetName().compare(clicked->text().toStdString()) == 0 )
        {
            toDisplay = it->first;
        }
    }
    if( toDisplay < 0 )
    {
        // log error
        QString error = "Class not found: ";
        error.append(clicked->text());
        logError(displayErr, error, getlogDir());

        emit errorCaught(displayErr);
    }
    else
    {
        edit = new NewClass(toDisplay, this);
        connect(edit, &QDialog::accepted, this, &classview::onRefreshSignal);
        connect(edit, &QDialog::rejected, this, &classview::onClassDelete);
        connect(edit, &NewClass::errorCaught, this, &classview::recieveError);
        edit->show();
    }
}

void classview::onRefreshSignal()
{
    refreshClassList();
}

void classview::onClassDelete()
{
    NewClass* toDel = qobject_cast<NewClass*>(sender());
    if( toDel != NULL )
    {
        ui->ClassList->takeItem(toDel->getEdit());
    }
    onRefreshSignal();
}

void classview::recieveError(int err)
{
    emit errorCaught(err);
}
