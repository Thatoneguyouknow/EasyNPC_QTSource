#include "mainwindow.h"
#include <QApplication>
#include <QFileInfo>
#include <QMessageBox>
#include <QtDebug>

#include <stdio.h>

#include "generator.h"
#include "Helper_Functions/database.h"

#if __APPLE__
#include <unistd.h>
#elif defined(WIN32)
#endif

void setSeed()
{
    unsigned int seed = (unsigned int)time(NULL);
    srand(seed);
}

bool fileExists(QString file)
{
    QDir databaseDir = getlogDir();
    QString database = databaseDir.filePath(file);
    QFileInfo check_file(database);
    return check_file.exists() && check_file.isFile();
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

    createLogDir();
    setSeed();

    createMap();

    QTextStream debug(stdout);

    if( !fileExists("data.db"))
    {
        debug << "Generating base classes: " << Qt::endl;
        generateBaseClasses();
        debug << "Generating base races: " << Qt::endl;
        generateBaseRaces();
        if( createTables() == -1 )
        {
            debug << "Could not generate base objects" << Qt::endl;
            displayError();
            return 0;
        }
    }
    else
    {
        if( readGenerators() == -1 )
        {
            debug << "Could not read generators" << Qt::endl;
            displayError();
            return 0;
        }
        else if( readClasses() == -1 )
        {
            debug << "Could not read classes" << Qt::endl;
            displayError();
            return 0;
        }
        else if( readRaces() == -1 )
        {
            debug << "Could not read races" << Qt::endl;
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
