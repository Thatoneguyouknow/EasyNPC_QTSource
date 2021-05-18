//
//  Database.hpp
//  Dnd
//
//  Created by Benjamin Peterson on 2/9/21.
//

#ifndef Database_hpp
#define Database_hpp

#include <stdio.h>
#include <sqlite3.h>
#include <QtSql>
#include "Helper_Functions/errorlog.h"

int callback(void *data, int argc, char **argv, char **azColName);
int createTables();

static const int dbOpenErr = 1201;
static const int clCreateErr = 1202;
static const int raCreateErr = 1203;
static const int gCreateErr = 1204;

static QByteArray database;

#endif /* Database_hpp */
