#include "errorlog.h"

bool checkLogDir()
{
#ifdef QT_DEBUG
    QDir check = QDir::current();
    return check.exists();
#elif __APPLE__
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
#elif defined(WIN32) or defined (WIN64)
    QString logPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir check = QDir(logPath);
    return check.exists();
#endif
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
#ifdef QT_DEBUG
    qDebug() << QDir::current();
    return QDir::current();
#elif __APPLE__
    QDir logLoc = QDir::home();
    logLoc.cd("Library");
    logLoc.cd("Application Support");
    logLoc.cd("EasyNPC");
    return logLoc;
#elif defined (WIN32) or defined(WIN64)
    QString logPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir logLoc = QDir(logPath);
    return logLoc;
#else
    return QDir::current();
#endif
}

void copydataFile()
{
    #if __APPLE__
        system(MSHELLSCRIPT);
    #endif
    // On Windows, data.db does not need to be copied to another location
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

