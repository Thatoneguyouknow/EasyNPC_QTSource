#ifndef CLASS_H
#define CLASS_H

#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <array>

#include <QString>

#include "stats.h"
#include "Helper_Functions/sqlite3.h"
#include "Helper_Functions/errorlog.h"

using namespace std;

class Class
{
public:
    Class();
    Class(string name, int hitdie, array<int, 6> priority, int userMade);
    ~Class();

    string getsetName(bool setFlag=false, string toSet="");
    int getsetHitDie(bool setFlag=false, int toSet=0);
    array<int, 6> getsetPriority(bool setFlag=false, array<int, 6> *toSet=nullptr);
    int getsetUser(bool setFlag=false, int toSet=0);
    int getClassID();

private:
    int classID;
    string name;
    int userCreated;
    int hitDie;
    array<int, 6> statPriority;
};

extern map<int, Class> availableClasses;
extern int nextClassID;

void generateBaseClasses();

//SQL Functions
int saveClasses();
int saveClass(Class toSave);
int sqlToClass(void* data, int argc, char** argv, char** azColName);
int readClasses();
void removeClass(int toRemove);
void removeAllClasses();

static const int cCreateErr = 1116;
static const int cDbErr = 1201;
static const int claIdMismatch = 1210;
static const int claOpenErr = 1211;
static const int claFailRead = 1212;
static const int claFailPrep = 1213;
static const int claFailBind = 1214;

#endif // CLASS_H
