//
//  Database.cpp
//  Dnd
//
//  Created by Benjamin Peterson on 2/9/21.
//

#include "Database.hpp"

int callback(void *data, int argc, char **argv, char **azColName)
{
   fprintf(stderr, "%s: ", (const char*)data);
   
   for(int i = 0; i<argc; i++)
   {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}

int createTables()
{
    //const char *dbPath = database.data();
    // open database connection
    sqlite3 *db;
    int success = sqlite3_open("data.db", &db);
    if( success )
    {
        QString error = "Cannot open database: ";
        error.append(QString::fromStdString(sqlite3_errmsg(db)));
        logError(dbOpenErr, error, getlogDir());
        //printf("Cannot open database %s\n", sqlite3_errmsg(db));
        return -1;
    }
    
    int returnCode;
    char *zErrMsg = 0;
    
    // create Class Table
    const char* sql = "CREATE TABLE CLASS( " \
                "ID INT PRIMARY KEY     NOT NULL," \
                "NAME           TEXT    NOT NULL," \
                "HITDIE         INT     NOT NULL," \
                "P1STAT         INT     NOT NULL," \
                "P2STAT         INT     NOT NULL," \
                "P3STAT         INT     NOT NULL," \
                "P4STAT         INT     NOT NULL," \
                "P5STAT         INT     NOT NULL," \
                "P6STAT         INT     NOT NULL," \
                "USERMADE       INT     NOT NULL);";
    
    returnCode = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    
    if( returnCode != SQLITE_OK )
    {
        QString error = "SQL create Class Table Error: ";
        error.append(QString::fromStdString(zErrMsg));
        logError(clCreateErr, error, getlogDir());
        //printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }
    
    // create Race Table
    sql = "CREATE TABLE IF NOT EXISTS RACE( " \
    "ID INT PRIMARY KEY     NOT NULL," \
    "NAME           TEXT    NOT NULL," \
    "ASIPSTAT       INT     NOT NULL," \
    "ASISSTAT       INT     NOT NULL," \
    "ASIPVAL        INT     NOT NULL," \
    "ASISVAL        INT     NOT NULL," \
    "AGEMIN         INT     NOT NULL," \
    "AGEMAX         INT     NOT NULL," \
    "NAMETYPE       INT     NOT NULL);";
    returnCode = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( returnCode != SQLITE_OK )
    {
        // ErrorCode 1203
        QString error = "SQL create Race Table Error: ";
        error.append(QString::fromStdString(zErrMsg));
        logError(raCreateErr, error, getlogDir());
        //printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }
    
    // create Weapon Table
    /*
    sql = "CREATE TABLE WEAPON( " \
    "ID INT PRIMARY KEY     NOT NULL," \
    "NAME           TEXT    NOT NULL," \
    "DAMAGE         INT     NOT NULL," \
    "DMGTYPE        INT     NOT NULL," \
    "CATEGORY       INT     NOT NULL," \
    "ISMELEE        INT     NOT NULL," \
    "PROPERTIES     INT             ," \
    "AMMO           INT             ," \
    "RANGE          INT             ," \
    "SPECIAL        TEXT             );";
    returnCode = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( returnCode != SQLITE_OK )
    {
        printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else
    {
        printf("Weapon Table created successfully\n");
    }*/
    
    // create NPC Table
    sql = "CREATE TABLE IF NOT EXISTS NPC( " \
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
    "CHAR           INT     NOT NULL);";
    returnCode = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( returnCode != SQLITE_OK )
    {
        QString error = "SQL create NPC Table Error: ";
        error.append(QString::fromStdString(zErrMsg));
        logError(gCreateErr, error, getlogDir());
        //printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }
    
    // close database connection
    sqlite3_close(db);
    return 0;
}
