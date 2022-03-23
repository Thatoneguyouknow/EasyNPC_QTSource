#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include "sqlite3.h"

#include "Helper_Functions/errorlog.h"

#include <QString>

using namespace std;

int callback(void *data, int argc, char **argv, char **azColName);
int createTables();
void deleteDb();

static const int dbOpenErr = 1201;
static const int clCreateErr = 1202;
static const int raCreateErr = 1203;
static const int gCreateErr = 1204;

#endif // DATABASE_H
