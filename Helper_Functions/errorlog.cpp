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
        QString logPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir check = QDir(logPath);
        if( !check.exists() )
        {
            return false;
        }
        return true;
    }
    return false;
}


void logError(int Code, QString toLog)
{
    QString date = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    QString errCode = QString::number(Code);
    QDir logLoc = getlogDir();

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
    else if( os.contains("windows") )
    {
        createLogDirWin();
    }
    else
    {
        // Throw unsupported OS error
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
    else //if it is not mac or windows, unsupported OS error would have been thrown at first startup, thus it must be windows
    {
        QString logPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir logLoc = QDir(logPath);
        return logLoc;
    }
    return QDir::current();
}

void copydataFile()
{
    QString os = QSysInfo::productType();
    if( os.contains("osx") || os.contains("mac") )
    {
        system(MSHELLSCRIPT);
    }
    // On Windows, data.db does not need to be copied to another location
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
    // logdir is C:\Users\$User\AppData\Roaming\$AppName
    QString logPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir logLoc = QDir(logPath);

    if( !logLoc.cdUp() )
    {
        // ErrorCode
    }
    else
    {
        logLoc.mkdir("EasyNPC");
    }

    /*QFile test(logLoc.filePath("hello.txt"));
    test.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream out(&test);

    QString os = QSysInfo::productType();
    out << "OS: " << os << Qt::endl;

    QString root = QDir::rootPath();
    out << "Root: " << root << Qt::endl;

    QString testus = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    out << "Write loc: " << testus << Qt::endl;

    QString home = QDir::homePath();
    out << "Home path: " << home << Qt::endl;

    QString pwd = QDir::currentPath();
    out << "Current path: " << pwd << Qt::endl;*/
}

