#include "characterview.h"
#include "ui_characterview.h"

CharacterView::CharacterView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterView)
{
    ui->setupUi(this);
    for(int i=0; i < (int)availableGens.size(); i++)
    {
        ui->listWidget->addItem(QString::fromStdString(availableGens[i].getsetName()));
    }

    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_object_dc(QListWidgetItem*)));
}

CharacterView::~CharacterView()
{
    delete ui;
}

void CharacterView::addChar(Generator toAdd)
{
    ui->listWidget->addItem(QString::fromStdString(toAdd.getsetName()));
}

void CharacterView::createChar()
{
    Generator test = Generator();
    availableGens.insert(pair<int, Generator>(test.getGenID(), test));
    // open character window
    //displayCharacter(test.getGenID());
}

void CharacterView::on_object_dc(QListWidgetItem *clicked)
{
    // Open a new character edit window (possibly from mainwindow for parenthood)
    // Get the index of the generator (based on position in list? Based on name?)
    // Display generator in character edit window
    int toDisplay = -1;
    for (int i=0; i<(int)availableGens.size() ; i++ )
    {
        if( availableGens.at(i).getsetName().compare(clicked->text().toStdString()) == 0 )
        {
            toDisplay = i;
        }
    }
    QTextStream out(stdout);
    if( toDisplay < 0 )
    {
        out << "No matching NPC: \n";
        out << clicked->text() << Qt::endl;
    }
    else
    {
        displayCharacter(toDisplay);
    }
}

void CharacterView::displayCharacter(int toDisp)
{
    edit = new editChar(toDisp, this);
    connect(edit, &QDialog::finished, this, &CharacterView::onRefreshSignal);
    edit->show();
}

void CharacterView::onRefreshSignal()
{
    refreshList();
}

void CharacterView::refreshList()
{
    QTextStream out(stdout);
    out << "Refreshing Character List" << Qt::endl;
    ui->listWidget->clear();
    for( int i=0; i < (int)availableGens.size(); i++ )
    {
        ui->listWidget->addItem(QString::fromStdString(availableGens.at(i).getsetName()));
    }
}
