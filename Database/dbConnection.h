#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QStandardPaths>

static const QString CONNECTION_NAME = "test";

static bool createConnection()
{
#ifdef QT_DEBUG
    QDir dbDir = QDir::current();
#else
    QDir dbDir = QDir::current();
#endif
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbDir.filePath("EasyNPCData.db"));
    if(!db.open())
    {
        qDebug() << "Database would not open " << db.lastError().text();
        return false;
    }

    // Create tables
    QSqlQuery query;
    if( !query.exec("CREATE TABLE IF NOT EXISTS CLASS( "\
            "ID INT PRIMARY KEY     NOT NULL," \
            "NAME           TEXT    NOT NULL," \
            "HITDIE         INT     NOT NULL," \
            "P1STAT         INT     NOT NULL," \
            "P2STAT         INT     NOT NULL," \
            "P3STAT         INT     NOT NULL," \
            "P4STAT         INT     NOT NULL," \
            "P5STAT         INT     NOT NULL," \
            "P6STAT         INT     NOT NULL," \
            "USERMADE       INT     NOT NULL);") )
    {
        qDebug() << "Could not create class table" << query.lastError().text();
        db.close();
        return false;
    }
    if( !query.exec("CREATE TABLE IF NOT EXISTS RACE( " \
            "ID INT PRIMARY KEY     NOT NULL," \
            "NAME           TEXT    NOT NULL," \
            "ASIPSTAT       INT     NOT NULL," \
            "ASISSTAT       INT     NOT NULL," \
            "ASIPVAL        INT     NOT NULL," \
            "ASISVAL        INT     NOT NULL," \
            "AGEMIN         INT     NOT NULL," \
            "AGEMAX         INT     NOT NULL," \
            "NAMETYPE       INT     NOT NULL);") )
    {
        qDebug() << "Could not create race table" << query.lastError().text();
        db.close();
        return false;
    }
    if( !query.exec("CREATE TABLE IF NOT EXISTS NPC( " \
            "ID INT PRIMARY KEY     NOT NULL," \
            "NAME           TEXT    NOT NULL," \
            "RACEID         INT     NOT NULL," \
            "CLASSID        INT     NOT NULL," \
            "ALIGN          INT     NOT NULL," \
            "PERPOS         TEXT    NOT NULL," \
            "PERNEU         TEXT    NOT NULL," \
            "PERNEG         TEXT    NOT NULL," \
            "LEVEL          INT     NOT NULL," \
            "HP             INT     NOT NULL," \
            "STR            INT     NOT NULL," \
            "DEX            INT     NOT NULL," \
            "CON            INT     NOT NULL," \
            "INT            INT     NOT NULL," \
            "WIS            INT     NOT NULL," \
            "CHAR           INT     NOT NULL);") )
    {
        qDebug() << "Could not create npc table" << query.lastError().text();
        db.close();
        return false;
    }
    db.close();
    return true;
}

static void closeConnection()
{
    QSqlDatabase db = QSqlDatabase::database(CONNECTION_NAME);
    db.close();
}

#endif // DBCONNECTION_H
