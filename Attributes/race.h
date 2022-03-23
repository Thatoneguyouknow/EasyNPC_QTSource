#ifndef RACE_H
#define RACE_H

#include <stdio.h>
#include <string>
#include <array>
#include <map>
#include <iostream>

#include <QString>

#include "stats.h"
#include "Helper_Functions/sqlite3.h"
#include "Helper_Functions/errorlog.h"

using namespace std;

const int NOTYPE = 112;

class Race
{
public:
    Race();
    Race(string name, int asiStatPrim, int asiStatSec, int asiValPrim, int asiValSec, int maxAge, int minAge, int type=NOTYPE);
    ~Race();

    // getters and setters
    string getsetName(bool setFlag = false, string toSet = "");
    int getsetPrimStat(bool setFlag = false, int toSet = 0);
    int getsetSecStat(bool setFlag = false, int toSet = 0);
    int getsetPrimVal(bool setFlag = false, int toSet = 0);
    int getsetSecVal(bool setFlag = false, int toSet = 0);
    int getsetMaxAge(bool setFlag = false, int toSet = 0);
    int getsetMinAge(bool setFlag = false, int toSet = 0);
    int getsetNameType(bool setFlag = false, int toSet = 0);
    int getIdentifier();

private:
    int raceIdentifier;
    string raceName;
    int asiStatPrimary;
    int asiStatSecondary;
    int asiValPrimary;
    int asiValSecondary;
    int ageMax;
    int ageMin;
    int nameType;
};

extern map<int, Race> availableRaces;
extern int nextRaceID;

void generateBaseRaces();

const bool SET = true;

int saveRaces();
int saveRace(Race toSave);
int sqlToRace(void *data, int argc, char **argv, char **azColName);
int readRaces();
void removeRace(int toRemove);
void removeAllRaces();

static const int rCreateErr = 1115;
static const int rDbErr = 1201;
static const int raceIdMismatch = 1205;
static const int raceOpenErr = 1206;
static const int raceFailRead = 1207;
static const int raceFailPrep = 1208;
static const int raceFailBind = 1209;
#endif // RACE_H
