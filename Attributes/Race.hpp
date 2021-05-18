//
//  Race.hpp
//  Dnd
//
//  Created by Benjamin Peterson on 1/21/21.
//

#ifndef Race_hpp
#define Race_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <iostream>
#include <sqlite3.h>
#include "Stats.hpp"
#include "Helper_Functions/Database.hpp"

using namespace std;

const int NOTYPE = 112;

class Race
{
public:
    Race(bool empty=true);
    Race(string name, int asiStatPrim, int asiStatSec, int asiValPrim, int asiValSec, int maxAge, int minAge, int type=NOTYPE);
    ~Race();
    Race(const Race &toCopy);
    Race& operator=(const Race& other)
    {
        if( this != &other )
        {
            raceIdentifier = other.raceIdentifier;
            raceName = other.raceName;
            asiStatPrimary = other.asiStatPrimary;
            asiStatSecondary = other.asiStatSecondary;
            asiValPrimary = other.asiValPrimary;
            asiValSecondary = other.asiValSecondary;
            ageMax = other.ageMax;
            ageMin = other.ageMin;
            nameType = other.nameType;
        }
        return *this;
    }

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
int saveRaces();
int saveRace(Race toSave);
int sqlToRace(void *data, int argc, char **argv, char **azColName);
int readRaces();
void removeRace(int toRemove);
void removeAllRaces();
const bool SET = true;

static const int rCreateErr = 1115;
static const int rDbErr = 1201;
static const int raceIdMismatch = 1205;
static const int raceOpenErr = 1206;
static const int raceFailRead = 1207;
static const int raceFailPrep = 1208;
static const int raceFailBind = 1209;
#endif /* Race_hpp */

