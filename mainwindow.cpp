#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    os = QSysInfo::productType();

    //ErrorLog test = ErrorLog("errors.log", "/Library/Application Support/EasyNPC");

    // NEW button dropdown menu
    QMenu *menu = new QMenu(this);
    newButtonActions(menu);
    QFont actionFont = QFont(menu->font());
    actionFont.setPointSize(20);
    menu->setFont(actionFont);
    ui.NEW->setMenu(menu);

    // Menu Bar setup
    menuActions();
    createMenu();

    QWidget *recent = new QWidget(this);
    Recents = new QGridLayout(recent);
    Recents->setVerticalSpacing(50);
    ui.scrollArea->setWidget(recent);


    cUi = new classview(this);
    rUi = new raceview(this);
    map<int, Generator>::iterator it;
    int position = 3;
    for( it = availableGens.begin(); it != availableGens.end(); it++ )
    {
        try {
            CharCard* newCard = new CharCard(it->first, this);
            Recents->addWidget(newCard, (position/3)-1, position%3);
            cards.insert(pair<int, CharCard*>(it->first, newCard));
            position++;
            connect(newCard, SIGNAL(widgetClicked()), this, SLOT(on_EditChar()));
            connect(newCard, &CharCard::errorCaught, this, &MainWindow::onCodedError);
        }  catch (...) {
            QString error = "Card cannot be created for NPC: ";
            error.append(QString::number(it->first));
            logError(CardErr, error, getlogDir());
            onCodedError(CardErr);
        }
    }

    connect(cUi, &classview::errorCaught, this, &MainWindow::onCodedError);
    Recents->addWidget(cUi);
    cUi->hide();

    connect(rUi, &raceview::errorCaught, this, &MainWindow::onCodedError);
    Recents->addWidget(rUi);
    rUi->hide();
}

void MainWindow::menuActions()
{
    // new actions set up by newButtonActions
    aboutAct = new QAction("About", this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(onAbout()));

    report = new QAction("Report Bug", this);
    connect(report, &QAction::triggered, this, &MainWindow::onUncodedError);
}

void MainWindow::createMenu()
{
    newMenu = new QMenu("New");
    newMenu->addAction(newGen);
    newMenu->addAction(newClass);
    newMenu->addAction(newRace);

    fileMenu = new QMenu("File");
    fileMenu->addMenu(newMenu);
    fileMenu->addAction(aboutAct);

    ui.menubar->addMenu(fileMenu);

    helpMenu = new QMenu("Help");
    helpMenu->addAction(report);
    ui.menubar->addMenu(helpMenu);
}

void MainWindow::newButtonActions(QMenu *menu)
{
    newGen = new QAction("Character", this);
    menu->addAction(newGen);
    connect(newGen, SIGNAL(triggered()), this, SLOT(on_NewChar()));

    newClass = new QAction("Class", this);
    menu->addAction(newClass);
    connect(newClass, SIGNAL(triggered()), this, SLOT(on_NewClass()));

    newRace = new QAction("Race", this);
    menu->addAction(newRace);
    connect(newRace, SIGNAL(triggered()), this, SLOT(on_NewRace()));
}

///////////////
/// SLOTS
///////////////

// This slot does nothing, since clicks to NEW overwrite to the dropdown menu
void MainWindow::on_NEW_clicked()
{

}

void MainWindow::on_Characters_clicked()
{
    // Take us to the Characters page
    if(!cUi->isHidden() || !rUi->isHidden())
    {
        cUi->hide();
        rUi->hide();
        map<int, CharCard*>::iterator it;
        for( it = cards.begin(); it != cards.end(); it++ )
        {
            it->second->show();
            it->second->refreshCard();
        }
    }
}

void MainWindow::on_Classes_clicked()
{
    // Take us to the classes page
    if(cUi->isHidden())
    {
        map<int, CharCard*>::iterator it;
        for( it = cards.begin(); it != cards.end(); it++ )
        {
            it->second->hide();
        }
        rUi->hide();
        cUi->show();
    }
    cUi->refreshClassList();
}

void MainWindow::on_Races_clicked()
{
    if(rUi->isHidden())
    {
        map<int, CharCard*>::iterator it;
        for( it = cards.begin(); it != cards.end(); it++ )
        {
            it->second->hide();
        }
        cUi->hide();
        rUi->show();
    }
    rUi->refreshRace();
}

void MainWindow::on_EditChar()
{
    CharCard* card = qobject_cast<CharCard*>(sender());
    if( card != NULL )
    {
        edit = new editChar(card->getId(), this);
        connect(edit, &QDialog::accepted, this, &MainWindow::onCharRefresh);
        connect(edit, &QDialog::rejected, this, &MainWindow::onCharDel);
        connect(edit, &editChar::errorCaught, this, &MainWindow::onCodedError);
        edit->show();
    }
}

void MainWindow::on_NewChar()
{
    Generator test = Generator();
    availableGens.insert(pair<int, Generator>(test.getGenID(), test));
    edit = new editChar(test.getGenID(), this);
    connect(edit, &QDialog::accepted, this, &MainWindow::onCharRefresh);
    connect(edit, &QDialog::rejected, this, &MainWindow::onCharDel);
    connect(edit, &editChar::errorCaught, this, &MainWindow::onCodedError);
    edit->show();
}

void MainWindow::on_NewClass()
{
    // Create a new Class using newclass.ui
    cUi->newClass();
}

void MainWindow::on_NewRace()
{
    // Create a new Race using newrace.ui
    rUi->newRace();
}

void MainWindow::onCharRefresh()
{
    // delete all cards
    map<int, CharCard*>::iterator card;
    for( card = cards.begin(); card != cards.end(); card++ )
    {
        Recents->removeWidget(card->second);
        delete card->second;
    }
    cards.clear();

    // recreate all cards
    map<int, Generator>::iterator it;
    int position = 3;
    for( it = availableGens.begin(); it != availableGens.end(); it++ )
    {
        CharCard* newCard = new CharCard(it->first, this);
        try {
            Recents->addWidget(newCard, (position/3)-1, position%3);
            cards.insert(pair<int, CharCard*>(it->first, newCard));
            position++;
            connect(newCard, SIGNAL(widgetClicked()), this, SLOT(on_EditChar()));
            connect(newCard, &CharCard::errorCaught, this, &MainWindow::onCodedError);
        }  catch (...) {
            QString error = "Card cannot be created for NPC: ";
            error.append(QString::number(it->first));
            logError(CardErr, error, getlogDir());
            onCodedError(CardErr);
        }

    }
}

void MainWindow::onCharDel()
{
    // Remove character card
    CharCard* card = qobject_cast<CharCard*>(sender());
    if( card != NULL )
    {
        Recents->removeWidget(card);
    }
    onCharRefresh();
}

void MainWindow::onCodedError(int code)
{
    errorDial = new CodedError(code, true, this);
    errorDial->show();
    //QDesktopServices::openUrl(QUrl::fromEncoded("mailto:someguy@acompany.com?subject=Sending%20File&attachment=path/to/local/file.dat"));
    // Use QDesktop Services to get data.db file
}

void MainWindow::onUncodedError()
{
    logError(0, "User called error", getlogDir());
    errorDial = new CodedError(0, false, this);
    errorDial->show();
}

void MainWindow::onQuit()
{
    // Save Classes, Races, and Generators
    if( saveClasses() == -1 )
    {
        // throw save error
        onCodedError(-2);
    }
    saveRaces();
    saveGens();
}

void MainWindow::onAbout()
{
    // At some point replace this with something better looking
    QMessageBox::about(this, "About EasyNPC", "Created by Benngy\n2021\nBuilt using:\nQTCreator,  SQLite3");
}
