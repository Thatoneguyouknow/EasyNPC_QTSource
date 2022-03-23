#include "classview.h"
#include "ui_classview.h"

ClassView::ClassView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClassView)
{
    ui->setupUi(this);

    map<int, Class>::iterator it;
    for( it=availableClasses.begin(); it!=availableClasses.end(); it++ )
    {
        ui->ClassList->addItem(QString::fromStdString(it->second.getsetName()));
    }
    connect(ui->ClassList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_class_dc(QListWidgetItem*)));
}

ClassView::~ClassView()
{
    delete ui;
}

void ClassView::refreshClassList()
{
    ui->ClassList->clear();
    map<int, Class>::iterator it;
    for( it=availableClasses.begin(); it!=availableClasses.end(); it++ )
    {
        ui->ClassList->addItem(QString::fromStdString(it->second.getsetName()));
    }
}

void ClassView::newClass()
{
    edit = new NewClass(this);
    connect(edit, &QDialog::accepted, this, &ClassView::onRefreshSignal);
    connect(edit, &QDialog::rejected, this, &ClassView::onClassDelete);
    connect(edit, &NewClass::errorCaught, this, &ClassView::recieveError);
    edit->show();
}

void ClassView::on_class_dc(QListWidgetItem* clicked)
{
    int toDisplay = -1;
    map<int, Class>::iterator it;
    for ( it=availableClasses.begin(); it != availableClasses.end() ; it++ )
    {
        if( it->second.getsetName().compare(clicked->text().toStdString()) == 0 )
        {
            toDisplay = it->first;
        }
    }

    if(toDisplay < 0)
    {
        QString error = "Cannot find class: ";
        error.append(clicked->text());
        logError(displayErr, error);
        emit errorCaught(displayErr);
    }
    else
    {
        edit = new NewClass(toDisplay, this);
        connect(edit, &QDialog::accepted, this, &ClassView::onRefreshSignal);
        connect(edit, &QDialog::rejected, this, &ClassView::onClassDelete);
        connect(edit, &NewClass::errorCaught, this, &ClassView::recieveError);
        edit->show();
    }
}

void ClassView::onRefreshSignal()
{
    refreshClassList();
}

void ClassView::onClassDelete()
{
    // delete class
}

void ClassView::recieveError(int err)
{
    emit errorCaught(err);
}
