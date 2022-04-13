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
    RecentView = new MainView(this);
    connect(RecentView, &MainView::errorCaught, this, &MainWindow::onCodedError);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(RecentView);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete RecentView;

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
    refreshRaces = new QAction("Restore Base Races", this);
    connect(refreshRaces, SIGNAL(triggered()), this, SLOT(onRRefresh()));

    refreshClasses = new QAction("Restore Base Classes", this);
    connect(refreshClasses, SIGNAL(triggered()), this, SLOT(onCRefresh()));

    reset = new QAction("Reset program", this);
    connect(reset, SIGNAL(triggered()), this, SLOT(onReset()));

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
    fileMenu->addAction(refreshRaces);
    fileMenu->addAction(refreshClasses);
    fileMenu->addAction(reset);

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

    RecentView->display_char(test.getGenID());
}

void MainWindow::on_NewClass()
{
    RecentView->display_class();
}

void MainWindow::on_NewRace()
{
    RecentView->display_race();
}

void MainWindow::on_Characters_clicked()
{
    RecentView->show_chars();
}

void MainWindow::on_Classes_clicked()
{
    RecentView->show_class();
}

void MainWindow::on_Races_clicked()
{
    RecentView->show_race();
}

void MainWindow::onCRefresh()
{
    // restore base classes
    //generateBaseClasses();
    printf("Will add functionality after testing");
}

void MainWindow::onRRefresh()
{
    // restore base races
    // generateBaseRaces();
    printf("Will add functionality after testing");
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

void MainWindow::onReset()
{
    // remove data.db file
    deleteDb();
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, "About EasyNPC", "Created by Benngy\n2021\nBuilt using:\nQTCreator,  SQLite3");
}

void MainWindow::onQuit()
{
    ClassSaver classSaver = ClassSaver();
    if( classSaver.saveAttributes() == -1)
    {
        onCodedError(-2);
    }
    RaceSaver raceSaver = RaceSaver();
    if( raceSaver.saveAttributes() == -1)
    {
        onCodedError(-2);
    }
    /*if( saveClasses() == -1 )
    {
        // throw save error
        onCodedError(-2);
    }*/
    /*if( saveRaces() == -1 )
    {
        onCodedError(-2);
    }*/
    if( saveGens() == -1 )
    {
        onCodedError(-2);
    }
}
