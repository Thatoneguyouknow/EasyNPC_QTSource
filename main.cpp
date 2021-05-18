#include "mainwindow.h"
#include <QApplication>
#include <QFileInfo>
#include <stdio.h>
#include "Generator.hpp"
#include "Helper_Functions/Database.hpp"
#include <QMessageBox>
#include <unistd.h>

void setSeed()
{
    unsigned int seed = (unsigned int)time(NULL);
    srand(seed);
    std::cout << "Seed: " << seed << "\n";
}

bool fileExists(QString file)
{
    QString appPath = QCoreApplication::applicationDirPath();
    appPath.append("/");
    appPath.append(file);
    database = appPath.toLocal8Bit();
    QFileInfo check_file(appPath);
    if(check_file.exists() && check_file.isFile())
    {
        return true;
    }
    return false;
}

void displayError()
{
    QMessageBox errorMsg;
    errorMsg.setText("A fatal error has occured.  Please report this bug at:\nEasyNPC@protonmail.com");
    errorMsg.exec();
}

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    //QString date = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    //QString errCode = QString::number(Code);

    QDir::setCurrent(QCoreApplication::applicationDirPath());

    //QFile logFile(getlogDir().filePath("setup.txt"));
    //logFile.open(QIODevice::WriteOnly | QIODevice::Append);

    //QTextStream out(&logFile);

   // out << "Working Dir: " << QDir::currentPath() << Qt::endl;
    //out << "Core App Path: " << QCoreApplication::applicationDirPath() << Qt::endl;

    // back-end: C++
    setSeed();

    // check if ~/Library/Application Support/EasyNPC exists, if not, create
   // out << "Checking log dir" << Qt::endl;
    if( !checkLogDir() )
    {
       // out << "Creating log dir" << Qt::endl;
        firstRunSetup();
    }

    // if database exists, dont generate base objects
 //   out << "Checking if database exists" << Qt::endl;
    if( !fileExists("data.db") )
    {
       // out << "Generating base objects" << Qt::endl;
        generateBaseRaces();
        generateBaseClasses();
        //generateBaseWeapons();
        if( createTables() == -1 )
        {
          //  out << "Failed: Create tables" << Qt::endl;
            displayError();
            return 0;
        }
    }
    else
    {
        if( readGenerators() == -1 )
        {
         //   out << "Failed: Read Gens" << Qt::endl;
            displayError();
            return 0;
        } else if( readClasses() == -1 )
        {
         //   out << "Failed: Read Classes" << Qt::endl;
            displayError();
            return 0;
        } else if( readRaces() == -1 )
        {
          //  out << "Failed: Read Races" << Qt::endl;
            displayError();
            return 0;
        }
    }

    // back-end: SQL
   // out << "Creating map" << Qt::endl;
    createMap();

    MainWindow mainWindow;
    mainWindow.show();

    // On exit, have everything saved
    QObject::connect(&app, SIGNAL(aboutToQuit()), &mainWindow, SLOT(onQuit()));

    return app.exec();
}


