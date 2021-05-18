#include "errorlog.h"

bool checkLogDir()
{
    QString os = QSysInfo::productType();
    QString location;
    if( os.contains("osx") || os.contains("mac") )
    {
        QDir check = QDir::home();
        if(!check.cd("Library"))
        {
            return false;
        } else if(!check.cd("Application Support"))
        {
            return false;
        } else if(!check.cd("EasyNPC"))
        {
            return false;
        }
        return true;
    }
    else
    {
        os = "Windows OS";
        location = "Bruh";
    }
    return false;
}


void logError(int Code, QString toLog, QDir logLoc)
{
    QString date = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    QString errCode = QString::number(Code);

    QFile logFile(logLoc.filePath(logfileName));
    logFile.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream out(&logFile);
    out << date << "\tCode " << errCode << "\n\t" << toLog << Qt::endl;

    copydataFile();
}

void firstRunSetup()
{
    QString os = QSysInfo::productType();
    if( os.contains("osx") || os.contains("mac") )
    {
        createLogDirMac();
    }
    else
    {
        createLogDirWin();
    }
}

QDir getlogDir()
{
    QString os = QSysInfo::productType();
    if( os.contains("osx") || os.contains("mac") )
    {
        QDir logLoc = QDir::home();
        logLoc.cd("Library");
        logLoc.cd("Application Support");
        logLoc.cd("EasyNPC");
        return logLoc;
    }
    return QDir::home();
}

void copydataFile()
{
    // Data.db stored in "/Applications/EasyNPC/Contents/MacOS"
    /*QDir dataLoc = QDir::current();
    QTextStream out(stdout);

    QString dataFile = dataLoc.path();
    dataFile.append("/data.db");
    out << dataFile<< Qt::endl;


    QString logLoc = getlogDir().path();
    QString copyLoc = logLoc;
    copyLoc.append("/data.db");
    out << copyLoc << Qt::endl;

    if( QFile::exists(copyLoc) )
    {
        out << "data File exists" << Qt::endl;
        QFile::remove(copyLoc);
    }

    if( !QFile::copy("data.db", "~\\Desktop\\data.db") )
    {
        out << "Could not copy file" << Qt::endl;
    }*/
    QString os = QSysInfo::productType();
    if( os.contains("osx") || os.contains("mac") )
    {
        system(MSHELLSCRIPT);
    }
    else
    {
        // system(WSHELLSCRIPT)
    }
}

void createLogDirMac()
{
    QDir logLoc = QDir::home();
    if(!logLoc.cd("Library"))
    {
        // ErrorCode
    }
    else if(!logLoc.cd("Application Support"))
    {
        // ErrorCode
    }
    else
    {
        logLoc.mkdir("EasyNPC");
    }
}

void createLogDirWin()
{
    //
}
