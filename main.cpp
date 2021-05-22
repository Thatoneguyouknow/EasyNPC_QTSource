#include "mainwindow.h"
#include <QApplication>
#include <QFileInfo>
#include <QMessageBox>

#include <stdio.h>
#include <unistd.h>

#include "generator.h"
#include "Helper_Functions/database.h"

void setSeed()
{
    unsigned int seed = (unsigned int)time(NULL);
    srand(seed);
    //std::cout << "Seed: " << seed << "\n";
}

bool fileExists(QString file)
{
    QDir databaseDir = getlogDir();
    QString database = databaseDir.filePath(file);
    QFileInfo check_file(database);
    if( check_file.exists() && check_file.isFile() )
    {
        return true;
    }
    return false;
}

void displayError()
{
    QMessageBox errorMsg;
    errorMsg.setText("A fatal error has occured. Please report this bug at:\nEasyNPC@protonmail.com");
    errorMsg.exec();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    firstRunSetup();
    setSeed();

    createMap();

    QTextStream debug(stdout);

    if( !fileExists("data.db"))
    {
        debug << "Generating base objs: " << Qt::endl;
        generateBaseClasses();
        generateBaseRaces();
        if( createTables() == -1 )
        {
            displayError();
            return 0;
        }
    }
    else
    {
        if( readGenerators() == -1 )
        {
            displayError();
            return 0;
        }
        else if( readClasses() == -1 )
        {
            displayError();
            return 0;
        }
        else if( readRaces() == -1 )
        {
            displayError();
            return 0;
        }
    }

    MainWindow mainWindow;
    mainWindow.show();


    // On exit, have everything saved
    QObject::connect(&a, SIGNAL(aboutToQuit()), &mainWindow, SLOT(onQuit()));

    return a.exec();
}
