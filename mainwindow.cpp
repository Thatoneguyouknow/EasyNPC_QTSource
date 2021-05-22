#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Dropdown menu for NEW button
    QMenu *menu = new QMenu(this);
    newButtonActions(menu);
    QFont actionFont = QFont(menu->font());
    actionFont.setPointSize(20);
    menu->setFont(actionFont);
    ui->NEW->setMenu(menu);

    // MenuBar setup
    menuActions();
    createMenu();

    // Recent view area setup
    QWidget *recent = new QWidget(this);
    Recents = new QGridLayout();
    recent->setLayout(Recents);
    Recents->setVerticalSpacing(50);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(recent);

    cUi = new ClassView(this);
    connect(cUi, &ClassView::errorCaught, this, &MainWindow::onCodedError);
    Recents->addWidget(cUi);
    cUi->hide();

    rUi = new RaceView(this);
    connect(rUi, &RaceView::errorCaught, this, &MainWindow::onCodedError);
    Recents->addWidget(rUi);
    rUi->hide();

    map<int, Generator>::iterator it;
    int position = 3;
    for( it=availableGens.begin(); it!=availableGens.end(); it++ )
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
            logError(CardErr, error);
            onCodedError(CardErr);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;

    delete cUi;
    delete rUi;
    delete Recents;

    delete newMenu;
    delete fileMenu;
    delete helpMenu;

    delete newGen;
    delete newClass;
    delete newRace;
    delete aboutAct;
    delete report;
}

void MainWindow::menuActions()
{
    aboutAct = new QAction("About", this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(onAbout()));

    report = new QAction("Report Bug", this);
    connect(report, SIGNAL(triggered()), this, SLOT(onUncodedError()));
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

    ui->menubar->addMenu(fileMenu);

    helpMenu = new QMenu("Help");
    helpMenu->addAction(report);
    ui->menubar->addMenu(helpMenu);
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

void MainWindow::on_NewChar()
{
    Generator test = Generator();
    availableGens.insert(pair<int, Generator>(test.getGenID(), test));
    edit = new editchar(test.getGenID(), this);
    connect(edit, &QDialog::accepted, this, &MainWindow::onCharRefresh);
    connect(edit, &QDialog::rejected, this, &MainWindow::onCharDel);
    connect(edit, &editchar::errorCaught, this, &MainWindow::onCodedError);
    edit->show();
}

void MainWindow::on_NewClass()
{
    cUi->newClass();
}

void MainWindow::on_NewRace()
{
    rUi->newRace();
}

void MainWindow::on_EditChar()
{
    CharCard* card = qobject_cast<CharCard*>(sender());
    if( card != NULL )
    {
        edit = new editchar(card->getId(), this);
        connect(edit, &QDialog::accepted, this, &MainWindow::onCharRefresh);
        connect(edit, &QDialog::rejected, this, &MainWindow::onCharDel);
        connect(edit, &editchar::errorCaught, this, &MainWindow::onCodedError);
        edit->show();
    }
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
            logError(CardErr, error);
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
    printf("Coded Error\n");
}

void MainWindow::onUncodedError()
{
    logError(0, "User called error");
    errorDial = new CodedError(0, false, this);
    errorDial->show();
    printf("Uncoded Error\n");
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, "About EasyNPC", "Created by Benngy\n2021\nBuilt using:\nQTCreator,  SQLite3");
}

void MainWindow::onQuit()
{
    if( saveClasses() == -1 )
    {
        // throw save error
        onCodedError(-2);
    }
    if( saveRaces() == -1 )
    {
        onCodedError(-2);
    }
    if( saveGens() == -1 )
    {
        onCodedError(-2);
    }
}
