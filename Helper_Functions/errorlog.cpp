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

void createLogDir()
{
#if __APPLE__
    QDir logLoc = QDir::home();
    if (!logLoc.cd("Library"))
    {
        // Error
    }
    else if( !logLoc.cd("Application Support"))
    {
        // Error
    }
    else {
        logLoc.mkdir("EasyNPC")
    }
#elif defined(WIN32) or defined(WIN64)
    QString logPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir logLoc = QDir(logPath);
    if( !logLoc.cdUp())
    {
        //Error
    }
    else
    {
        logLoc.mkdir("EasyNPC");
    }
#endif
}

