#ifndef ERRORLOG_H
#define ERRORLOG_H

#include <QFile>
#include <QString>
#include <QSysInfo>
#include <QDateTime>
#include <QTextStream>
#include <QDir>
#include <QFileInfoList>
#include <unistd.h>

#define MSHELLSCRIPT "\
#/bin/bash \n\
cp data.db ~/Library/Application\\ Support/EasyNPC"

#define WSHELLSCRIPT

const QString logfileName = "errors.log";
const QString dbFileName = "data.db";

void logError(int Code, QString toLog, QDir logLoc);
void firstRunSetup();
bool checkLogDir();
void createLogDirMac();
void createLogDirWin();
void copydataFile();
QDir getlogDir();

#endif // ERRORLOG_H
